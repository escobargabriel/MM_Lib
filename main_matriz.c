/*

Multiplicação de matrizes convencional, em bloco, convencional com POSIX threads e em blocos com POSIX threads.

                                            ATENÇÃO!!!

            Para entender onde e como fazer alterações no código leia o arquivo "README".
Nele constam detalhes de em qual código fonte e quais variáveis são necessárias para fazer a divisão da matriz de blocos.
*/

/*Matrizes Globais*/
int **mat_a;
int **mat_b;
int **mat_cThread; 
int **mat_cThreadBlock; 

    

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolsv2.h"
#include "matriz.h"
#include "matriz-operacoes.h"
#include "matriz-operacoes-threads.h"

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main(int argc, char *argv[]) {

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// DECLARAÇÃO de VARIÁVEIS
	FILE *fmat_a, *fmat_b, *fmat_c, *fmatthread_c, *fmatbloco_c2, *fmatthblockread_c; 
    // *fmatbloco_c
	int nr_line;
	int *vet_line = NULL;
	int N, M, La, Lb;
	double start_time, end_time, total=0;
	//matriz_bloco_t **Vsubmat_a = NULL;
	//matriz_bloco_t **Vsubmat_b = NULL;
	//matriz_bloco_t **Vsubmat_c = NULL;
	//int nro_submatrizes = 2;
	//int **mat_bloco_final = NULL;
    int **mat_bloco2 = NULL;	
    int tid, threads;
	pthread_t *pool;
	param_t *args;

    double mediaSeq = 0.0, mediaThreads = 0.0, mediaBloco2 = 0.0, mediaThreadsBlock = 0.0;
    double speedupThreads = 0.0, speedupBlock = 0.0; 
    //mediaBloco = 0.0
    mat_a = NULL;
    mat_b = NULL;
    int **mat_c = NULL;
    mat_cThread = NULL; 
    mat_cThreadBlock = NULL;
    
    //Numero de blocos    
    //Para garantir funcionamento (N/nBlocos % 2 == 0)
    int nBlocos = 16;


	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	if (argc != 4){
		printf ("ERRO: Numero de parametros \n");
		exit (1);
	}

  // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	fmat_a = fopen(argv[1],"r");
	fmat_b = fopen(argv[2],"r");
	threads = atoi(argv[3]);

	args  = (param_t *)   malloc(threads * sizeof(param_t));
	pool =  (pthread_t *) malloc(threads * sizeof(pthread_t));

  if ((fmat_a == NULL) || (fmat_b == NULL)) {
		printf("Error: Na abertura dos arquivos.\n");
		exit(1);
  }

  // matriz_a N (linha) x La (coluna)
	extrai_parametros_matriz(fmat_a, &N, &La, &vet_line, &nr_line);
	mat_a = alocar_matriz(N, La);
	filein_matriz (mat_a, N, La, fmat_a, vet_line, nr_line);

	// matriz_b Lb (linha) x M (coluna)
	extrai_parametros_matriz(fmat_b, &Lb, &M, &vet_line, &nr_line);
	mat_b = alocar_matriz(Lb, M);
	filein_matriz (mat_b, Lb, M, fmat_b, vet_line, nr_line);

	// matriz_c (resultante) = N (linha) x M(coluna)
	mat_c = alocar_matriz(N, M);
	zerar_matriz(mat_c, N, M);

	if ((mat_c == NULL) || (mat_b == NULL) || (mat_a == NULL)) {
		printf("ERROR: Out of memory\n");
	}
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
    if(La != Lb){
		printf("\nMatrizes imcompativeis!\n");
		printf("Encerrando execucao\n\n");
		exit(1);
	}
	if(N % nBlocos != 0){
        nBlocos = 4;
    }
    if(N == 10){
        nBlocos = 2;
    }



    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Multiplicação IJK
    printf("\n----------------------------------------------------------------------------\n");
    printf("\nIniciando execucao da Multiplicao de matrizes sequencial convencional\n");
    
	zerar_matriz(mat_c, N, M);
    for(int i = 0; i < 5; i++){	
        start_time = wtime();
	    multiplicarIJK(mat_a,mat_b,mat_c, N, N, N);
	    end_time = wtime();
        total = end_time - start_time;
        printf("Execucao %d: %lf\n", i+1, total);
        mediaSeq += (end_time - start_time);     
    }
    mediaSeq = mediaSeq/5;
 
	//printf("\n ##### Multiplicação de Matrizes (IJK) #####\n");
	//printf("\tRuntime: %f\n", end_time - start_time);
	fmat_c= fopen("outIJK.map-result","w");
	fileout_matriz(mat_c, N, M, fmat_c);
	printf("\nFim da execucao da Multiplicao de matrizes sequencial convencional\n");
    printf("\n----------------------------------------------------------------------------\n");
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

	// %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    // Multiplicação em Bloco v2
    /*    
    printf("\n----------------------------------------------------------------------------\n");
    printf("\nIniciando execução da Multiplicação de Matrizes com struct\n");
    for(int i = 0; i < 10; i++){
	start_time = wtime();	
    Vsubmat_a = particionar_matriz (mat_a, N, La, 1, nro_submatrizes);
	Vsubmat_b = particionar_matriz (mat_b, Lb, M, 0, nro_submatrizes);
	Vsubmat_c = constroi_submatriz (N, M, nro_submatrizes);
	mat_bloco_final = alocar_matriz(N, M);
	zerar_matriz(mat_bloco_final, N, M);
    
	multiplicar_submatriz (Vsubmat_a[0], Vsubmat_b[0], Vsubmat_c[0]);
	multiplicar_submatriz (Vsubmat_a[1], Vsubmat_b[1], Vsubmat_c[1]);
	somarIJ(Vsubmat_c[0]->matriz,Vsubmat_c[1]->matriz,mat_bloco_final, N, N, N, N);
    
	end_time = wtime();
    mediaBloco += (end_time - start_time);
    }
    mediaBloco = mediaBloco / 10;

	//printf("\tRuntime: %f\n\n", end_time - start_time);
	fmatbloco_c = fopen("outBlocov2.map-result","w");
	fileout_matriz(mat_bloco_final, N, M, fmatbloco_c);
	
    comparar_matriz (mat_c, mat_bloco_final, N, M);
	//printf("Resultados individuais encontram-se nos arquivos <out*.map-result>.\n");
    printf("\nFim da execucao da Multiplicao de matrizes com struct\n");
    printf("\n----------------------------------------------------------------------------\n");
    */
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    /*     Multiblocks                         */
    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    printf("\n----------------------------------------------------------------------------\n");
    printf("\nIniciando Multiplicação de matrizes em blocos\n");
    for(int i = 0; i < 5; i++){
	    start_time = wtime();
        mat_bloco2 = alocar_matriz(N, M);
    	zerar_matriz(mat_bloco2, N, M);    	
        multiplicaBloco(N, N, mat_a, mat_b, mat_bloco2, nBlocos);
	    end_time = wtime();
        total = end_time - start_time;
        printf("Execucao %d: %lf\n", i+1, total);
        mediaBloco2 += (end_time - start_time);
    }

    mediaBloco2 = mediaBloco2 / 5;

    

	fmatbloco_c2 = fopen("outBloco2.map-result","w");
	fileout_matriz(mat_bloco2, N, M, fmatbloco_c2);
	printf("\ncomparando sequencial com sequencial em blocos.\n");
    comparar_matriz (mat_c, mat_bloco2, N, M);
	//printf("Resultados individuais encontram-se nos arquivos <out*.map-result>.\n");
    printf("\nFim da execucao da Multiplicao de matrizes em blocos\n");
    printf("\n----------------------------------------------------------------------------\n");
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%



    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    /*          MM_thread - exec                       */
    printf("\n----------------------------------------------------------------------------\n");
    printf("\nIniciando execucao multi-thread da multiplicacao de matrizes convencional\n");
    mat_cThread = alocar_matriz(N, M);
	zerar_matriz(mat_cThread, N, M);
    for(int i = 0; i < 5; i++){
    start_time = wtime();
    	for(tid = 0; tid < threads; tid++){
    		args[tid].tid = tid;
    		args[tid].threads = threads;
    		args[tid].N = N;
    		pthread_create(&pool[tid], NULL, multiply, &args[tid]);
    	}
    	for(tid = 0; tid < threads; tid++)
    		pthread_join(pool[tid], NULL);

    end_time = wtime();
    total = end_time - start_time;
    printf("Execucao %d: %lf\n", i+1, total);	
    mediaThreads += (end_time - start_time);     
    }
    mediaThreads = mediaThreads / 5;
    speedupThreads = mediaSeq/mediaThreads;    

   	fmatthread_c = fopen("outThread.map-result","w");
	fileout_matriz(mat_cThread, N, M, fmatthread_c);
    printf("\ncomparando sequencial com sequencial com multi-thread.\n");
   	comparar_matriz (mat_c, mat_cThread, N, M);
	//printf("Resultados individuais encontram-se nos arquivos <out*.map-result>.\n");
    printf("\nFim da execucao da Multiplicao de matrizes multi-thread convencional\n");
    printf("\n----------------------------------------------------------------------------\n");
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%


    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
    /*          MM_thread - execBlock                       */
    printf("\n----------------------------------------------------------------------------\n");    
    printf("\nIniciando execucao multi-thread da multiplicação em blocos\n");
    mat_cThreadBlock = alocar_matriz(N, M);
	zerar_matriz(mat_cThreadBlock, N, M);
    for(int i = 0; i < 5; i++){
    zerar_matriz(mat_cThreadBlock, N, M);
    start_time = wtime();
    	for(tid = 0; tid < threads; tid++){
    		args[tid].tid = tid;
    		args[tid].threads = threads;
    		args[tid].N = N;
    		pthread_create(&pool[tid], NULL, multiplyBlock, &args[tid]);
    	}
    	for(tid = 0; tid < threads; tid++)
    		pthread_join(pool[tid], NULL);

    end_time = wtime();
    total = end_time - start_time;
    printf("Execucao %d: %lf\n", i+1, total);	
    mediaThreadsBlock += (end_time - start_time);     
    }
    mediaThreadsBlock = mediaThreadsBlock / 5;
    speedupBlock = mediaBloco2/mediaThreadsBlock;    

   	fmatthblockread_c = fopen("outThreadBlock.map-result","w");
	fileout_matriz(mat_cThreadBlock, N, M, fmatthblockread_c);
    printf("\ncomparando sequencial em blocos com multi-thread em blocos.\n");
	comparar_matriz (mat_c, mat_cThreadBlock, N, M);
	//printf("Resultados individuais encontram-se nos arquivos <out*.map-result>.\n");
    printf("\nFim da execucao multi-thread da Multiplicao de matrizes em blocos\n");
    printf("\n----------------------------------------------------------------------------\n");
    /*                     END                             */
    // %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%

    printf("\n----------------------------------------------------------------------------\n");
    printf("\n-   Sequenciais:                                                           -");
    printf("\n-   Media Sequencial:                                     %f         -", mediaSeq);
    //printf("\n-   Media Sequencial em Blocos 1 - (Structs):             %f         -", mediaBloco);
    printf("\n-   Media Sequencial em Blocos:                           %f         -", mediaBloco2);
    printf("\n----------------------------------------------------------------------------\n");
    printf("\n-   Paralelos:                                                             -");
    printf("\n-   Media Threads:                                        %f         -", mediaThreads);
    printf("\n-   Media Threads Blocos:                                 %f         -", mediaThreadsBlock);    
    printf("\n-   Speedup Threads:                                      %f         -", speedupThreads);
    printf("\n-   Speedup blocos:                                       %f         -", speedupBlock);
    printf("\n----------------------------------------------------------------------------\n");
  
    // %%%%%%%%%%%%%%%%%%%%%%%% BEGIN %%%%%%%%%%%%%%%%%%%%%%%%
	// LIBERAR MEMÓRIA
	//Vsubmat_a = liberar_submatriz (Vsubmat_a,nro_submatrizes);
	//Vsubmat_b = liberar_submatriz (Vsubmat_b,nro_submatrizes);
	//Vsubmat_c= liberar_submatriz (Vsubmat_c,nro_submatrizes);
	liberar_matriz(mat_a,N,La);
	liberar_matriz(mat_b,Lb,M);
	liberar_matriz(mat_c,N,M);
	//liberar_matriz(mat_bloco_final,N,M);
    liberar_matriz(mat_bloco2,N,M);
    liberar_matriz(mat_cThread,N,M);
	fclose(fmat_a);
	fclose(fmat_b);
    fclose(fmat_c);
    //fclose(fmatbloco_c);
    fclose(fmatbloco_c2);	
    fclose(fmatthread_c);
	// %%%%%%%%%%%%%%%%%%%%%%%% END %%%%%%%%%%%%%%%%%%%%%%%%
    free(args);
    free(pool);
	return 0;
}
