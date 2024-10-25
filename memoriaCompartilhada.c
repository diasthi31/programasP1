#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define SEMKEY ftok("/tmp", 'A')

int ehPrimo(int numero) {
  if (numero < 2) return 0;
  for (int i = 2; i <= sqrt(numero); i++) {
    if (numero % i == 0) return 0;
  }
return 1;
}

int main(int argc, char *argv[]) {
  int qtdProcessos = atoi(argv[1]), tamanhoVetor = atoi(argv[2]);
  int shmid = shmget(SEMKEY, (tamanhoVetor + qtdProcessos) * sizeof(int), 0666 | IPC_CREAT); 
  int *memoriaCompartilhada = (int *) shmat(shmid, NULL, 0); 

  for (int i = 1; i <= tamanhoVetor; i++) {
    memoriaCompartilhada[i] = i;
  }

  for (int i = 0; i < qtdProcessos; i++) { 
    pid_t pid = fork();

    if (pid == 0) { 
      int inicio = (i * tamanhoVetor) / qtdProcessos;
      int fim = ((i + 1) * tamanhoVetor) / qtdProcessos;

      int primoLocal = 0;
      for (int j = inicio; j < fim; j++) {
        if (ehPrimo(memoriaCompartilhada[j])) {
            primoLocal++;
        }
      }
      
      memoriaCompartilhada[tamanhoVetor + i] = primoLocal;

      shmdt(memoriaCompartilhada);
      exit(0);
    }
  }

  for (int i = 0; i < qtdProcessos; i++) {
    wait(NULL);
  }

  int totalPrimos = 0;
  for (int i = 0; i < qtdProcessos; i++) {
    totalPrimos += memoriaCompartilhada[tamanhoVetor + i];
  }

  shmdt(memoriaCompartilhada);
  shmctl(shmid, IPC_RMID, NULL);

  return 0;
}