# Trabalho SO2

## Programas para calcular a quantidade de números primos dentro de um vetor de 100 ou 1000 posições, utilizando entre 1 e 4 processos/threads:
1. **Utilizando memória compartilhada entre processos**  
2. **Utilizando troca de mensagens entre processos**  
3. **Utilizando threads**  

## Instalação do MPI para compilar o programa 2:
```bash
sudo apt install mpich
```

## Para compilar e rodar cada programa:
- **Programa 1:**
  ```bash
  gcc memoriaCompartilhada.c -o memoriaCompartilhada -lm
  time ./memoriaCompartilhada <qtd de Processos> <tamanho do vetor>
  ```

- **Programa 2:**
  ```bash
  mpicc -o trocaMensagens trocaMensagens.c -lm
  time ./trocaMensagens <qtd de Processos> <tamanho do vetor>
  ```

- **Programa 3:**
  ```bash
  gcc -o threads threads.c -lpthread -lm
  time ./threads <qtd de Threads> <tamanho do vetor>
  ```
