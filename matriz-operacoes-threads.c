#include "matriz-operacoes-threads.h"

/*Multiplicação paralela*/
void *multiply(void *arg){
	//ikj
	int i, j, k, init, slice, end;
	param_t *args = (param_t *) arg;


	slice = args->N / args->threads;
    
     
	init = args->tid * slice;
	if(args->tid == args->threads - 1)
		end = args->N;
	else
		end = init + slice;

		for(i = init; i < end; i++){
				for(j = 0; j < args->N; j++){
                    mat_cThread[i][j] = 0;                  
                   for(k = 0; k < args->N; k++){
					    mat_cThread[i][j] += mat_a[i][k] * mat_b[k][j];
                    }	            
                }
        }

	pthread_exit(NULL);				 
   
}

/*Multiplicação paralela em Blocos*/
void *multiplyBlock(void *arg){
	//ikj
	int i, j, k, init, slice, end, x, y, z;
	param_t *args = (param_t *) arg;
    int TILE;


    if(args->N % 16 != 0){
		TILE = 16;
	}
	if((args->N == 500 && args->threads == 16) || (args->N == 100 && args->threads == 4)){
		TILE = 5;
	}
	if(args->N == 1000 && args->threads == 4){
		TILE = 10;
	}
	if(args->N == 100 && args->threads == 8){
		TILE = 4;
	}
	if((args->N == 500 && args->threads < 8) || (args->N == 1000 && args->threads == 8)){
		TILE = 125;
	}
	if((args->threads == 16 || args->threads ==  2) || (args->N == 500 && args->threads == 8)){
    	TILE = 2;
    }
    
    printf("TILE %d\n", TILE);
	slice = args->N / args->threads;
    
     
	init = args->tid * slice;
	if(args->tid == args->threads - 1)
		end = args->N;
  	else
		end = init + slice;


	for(i = init; i < end; i += (TILE)){
        for(j = 0; j < args->N; j += (TILE)){
            for(k = 0; k < args->N; k += (TILE)){
                for(x = i; x < i + (TILE); x++){
                    for(y = j; y < j + (TILE); y++){
		                for(z = k; z < k + (TILE); z++){
		                    mat_cThreadBlock[x][y] += mat_a[x][z] * mat_b[z][y];
                        }
                    }
                }    
            }
        }
    }
        	pthread_exit(NULL);				 
   
}

