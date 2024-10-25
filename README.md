#Trabalho SO2
##Programas para:#
###
Calcular a quantidade de números primos dentro de um vetor 100 ou 1000 posições, utilizando entre 1 e 4 processos/treads.
1. Utilizando memória compartilhada entre processos; 
2. Utilizando troca de mensagens entre processos;
3. Utilizando threads.
###

##Instalação MPI para compilar programa 2:#
###sudo apt install mpich##

##Para compilar e rodar cada programa:#
###
Programa 1: 
gcc memoriaCompartilhada.c -o memoriaCompartilhada -lm
time ./memoriaCompartilhada <qtd de Processos> <tamanho do vetor>

Programa 2: 
mpicc -o trocaMensagens trocaMensagens.c -lm
time ./trocaMensagens 4 1000

Programa 3: 
gcc -o threads threads.c -lpthread -lm
time ./threads 4 1000
###
