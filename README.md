# Descrição

> Este programa em sua execução realiza operacoes basicas e a multiplicao de estruturas matriciais de quatro diferentes maneiras: convencional, em blocos, multi-thread convencional e multi-thread em blocos. 

> Estão presentes nos códigos funções para alocação de memória, geração e preenchimento de todas as posições das matrizes, liberação da memória, etc.


## Compilação

 __Importante!__

__Este código e demais arquivos auxiliares foram desenvolvidos e executados em sistema operacional linux__

> Para compilar os códigos é necessário executar o arquivo "Makefile", neste arquivo estão todas as flags e comandos necessários para a compilação da aplicação e bibliotecas auxiliares. Para executar este arquivo é necessário navegar através do terminal no sistema operacional linux até o diretório onde se encontram os arquivos ".c", ".h", além do "Makefile" (exemplo: $ cd /home/MM_Mthread).

> Estando dentro do diretório correto basta executar o *Makefile*.

> $ make

> Após execução deste comando os códigos seram compilados e gerados os executáveis e binarios.

	
## Excecução

### Execução isolada
> O arquivo *Makefile* é responsável pela compilação e geração dos executáveis da aplicação.

> Após compilação para gerar os arquivos de entrada basta executar o comando abaixo:

> $./geraMatriz2 128 128

> O primeiro parâmetro corresponde ao executável gerado na compilação, ja o segundo e o terceiro parâmetros correspondem as dimensões da matriz N x M (128 x 128).

> O nome do arquivo segue o padrao adotado pelo professor da disciplina.

> São necessários dois arquivos de entrada para execução da aplicação principal *main_matriz.c*.

> O arquivo gerado pela aplicação *geraMatriz2.c* possui por padrão o nome 128x128-mat.map, onde 128x128 são as dimensões NxM.

> Para executar a aplicação principal é preciso gerar um arquivo com as dimensões NxM, onde N e M devem ser iguais (matrizes quadradas).

> Pode ser utilizado como entrada o mesmo arquivo nos dois últimos parâmetros (exemplo: *NxN-mat.map*), ou renomear o arquivo manualmente, e gerar um novo arquivo com as mesmas dimensões do primeiro para garantir a compatibilidade dos arquivos de entrada. 

### Execuções em série

> Foi criado um script para facilitar as execuções, nele são criados arquivos para utilizar nas execuções onde o primeiro arquivo é criado, renomeado e outro arquivo gerado em seguida.

> Para executar o script basta digita navegar via até o diretório onde os arquivos se encontram e executar o comando:

> $ bash script.sh

> Serão executadas 4 variações dos testes e os resultados estarão impressos em arquivos de texto com nome indicando a dimensão das matrizes quadradas e o número de threads.

### Restrições

 __Importante__

 __Para que a aplicação execute de maneira correta são necessários que as seguintes restrições descritas abaixo sejam respeitdas:__

 __Este programa foi testado apenas para multiplicação de matrizes quadradas de mesmo tamanho ex: 100x100 * 100x100, 1000x1000 * 1000x1000,__

 __A versão da multiplicação em blocos foi testada para matrizes quadradas de mesmo tamanho onde N é multiplo de 2 ex: 128x128 * 128x128, 256x256 * 256x256, 512x512 * 512x512, e N divido pelo número de blocos deve ter resto da divisão igual a zero!!! ex: N (dimensão da matriz N*N) = 512, DB (dimensão dos blocos) = 16: 512/16 = 32, logo (N/DB % 2 == 0)__

 __Para definir a dimensão dos blocos da versão sequencial basta alterar o valor armazenado na variável nBlocos no código fonte do arquivo main_matriz.c__

 __Para definir A dimensão dos blocos da versão paralela basta alterar o valor armazenado na variável TILE no código fonte do arquivo matriz-operacoes-threads.c__

 __Para ambas versões devem ser respeitadas as restrições apresentadas acima__

 __Foram adicionados alguns condicionais no código na definição das dimensões dos blcoso para garantir a execução da aplicação, mas estes valores podem não ser os melhores para diversos casos__

 __Foram definidas na main 30 execuções para cada versão da multiplicação de matrizes, para modificar é necessário alterar nos comandos de repetição *for* o número de repetições, além disso para que a média seja calculada de forma correta é necessário que o número que divide o conteúdo das variáveis que armazenam as médias seja igual ao número de repetições das funções de multiplicação.__

> Supondo que as restrições expostas acima foram respeitados

> Para executar a aplicação principal é necessário que os códigos tenham sido compilados anteriormente através da execução do arquivo "Makefile". Uma vez compilados os códigos das aplicaçoes, e gerados os arquivos de entrada basta executar o seguinte comando:

> $ ./main_matriz 128x128-mat.map 128x128-mat1.map 2

> O primeiro parâmetro corresponde ao executável gerado na compilação atraves do arquivo Makefile, o segundo e o terceiro parametros corresponde aos arquivos de entrada onde as matrizes estao armazenadas, já o último parâmetro correspode ao número de threads que a aplicação executará. 


> O código do arquivo "main_matriz.c" foi desenvolvido utilizando como base o código dado pelo professor. 


## Remoção dos arquivos

> Para remover os arquivos criados basta executar o comando abaixo

> $ make clean 


## Contato

> Quaisquer dúvidas ou problemas favor entrar em contato pelo endereço escobarvasques@gmail.com.

## Autor

> Gabriel Escobar.

##DATA
> 10/05/2019.
