# !/bin/bash

make clean
make

echo "Gerando arquivos"
#-------------------Gerando arquivos para executar---------------------------#
#./gera_matriz2 128 128
#mv 128x128-mat.map 128x128-mat1.map
#./gera_matriz2 128 128
#----------------------------------------------------------------------------#
#./gera_matriz2 256 256
#mv 256x256-mat.map 256x256-mat1.map
#./gera_matriz2 256 256
#----------------------------------------------------------------------------#
#./gera_matriz2 512 512
#mv 512x512-mat.map 512x512-mat1.map
#./gera_matriz2 512 512
#----------------------------------------------------------------------------#
./gera_matriz2 1024 1024
mv 1024x1024-mat.map 1024x1024-mat1.map
./gera_matriz2 1024 1024
echo "Arquivos gerados"
#----------------------------------------------------------------------------#
#-----------------FIM DA GERACAO DE ARQUIVOS---------------------------------#
echo "Iniciando execuções aguarde:"
echo ""
#---------------------INICIO DAS EXECUCOES-----------------------------------#
#-----------------------EXECUCAO 128X128-------------------------------------#
#echo "Executando multiplicações 128x128"
#./main_matriz 128x128-mat.map 128x128-mat1.map 2 >> 128-2threads.txt
#./main_matriz 128x128-mat.map 128x128-mat1.map 4 >> 128-4threads.txt
#./main_matriz 128x128-mat.map 128x128-mat1.map 8 >> 128-8threads.txt
#-----------------------------FIM--------------------------------------------#
#-------------------------EXECUCAO 256X256-----------------------------------#
#echo "Executando multiplicações 256x256"
#./main_matriz 256x256-mat.map 256x256-mat1.map 2 >> 256-2threads.txt	
#./main_matriz 256x256-mat.map 256x256-mat1.map 4 >> 256-4threads.txt
#./main_matriz 256x256-mat.map 256x256-mat1.map 8 >> 256-8threads.txt
#--------------------------------FIM-----------------------------------------#
#-------------------------EXECUCAO 512X512-----------------------------------#
#echo "Executando multiplicações 512x512"
#./main_matriz 512x512-mat.map 512x512-mat1.map 2 >> 512-2threads.txt
#./main_matriz 512x512-mat.map 512x512-mat1.map 4 >> 512-4threads.txt
#./main_matriz 512x512-mat.map 512x512-mat1.map 8 >> 512-8threads.txt
#-------------------------------FIM-----------------------------------------#
#-------------------------EXECUCAO 1024X1024--------------------------------#
echo "Executando multiplicações 1024x1024"
./main_matriz 1024x1024-mat.map 1024x1024-mat1.map 2 >> 1024-2threads.txt
#./main_matriz 1024x1024-mat.map 1024x1024-mat1.map 4 >> 1024-4threads.txt
#./main_matriz 1024x1024-mat.map 1024x1024-mat1.map 8 >> 1024-8threads.txt
#-------------------------------FIM-----------------------------------------#
echo "Fim das execuções"
echo "Resultados encontram-se nos arquivos 128-2threads.txt, 256-2threads.txt, etc."
