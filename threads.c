#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int contadorGlobal = 0;  
pthread_mutex_t mutex;   // Mutex para proteger o contador global

int ehPrimo(int numero) {
    if (numero < 2) return 0;
    for (int i = 2; i <= sqrt(numero); i++) {
        if (numero % i == 0) return 0;
    }
    return 1;
}

void *contarPrimos(void *arg) {
    int id = *(int *)arg;
    int qtdThreads = ((int *)arg)[1];
    int tamanhoVetor = ((int *)arg)[2];

    int tamanhoDIvidido = tamanhoVetor / qtdThreads;
    int inicio = id * tamanhoDIvidido;
    int fim = (id == qtdThreads - 1) ? tamanhoVetor : inicio + tamanhoDIvidido;

    int contadorLocal = 0;
    for (int i = inicio; i < fim; i++) {
        if (ehPrimo(i + 1)) { 
            contadorLocal++;
        }
    }

    pthread_mutex_lock(&mutex);
    contadorGlobal += contadorLocal;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[]) {
    int qtdThreads = atoi(argv[1]);
    int tamanhoVetor = atoi(argv[2]);

    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[qtdThreads];
    int args[qtdThreads][3];

    for (int i = 0; i < qtdThreads; i++) {
        args[i][0] = i; 
        args[i][1] = qtdThreads;
        args[i][2] = tamanhoVetor;
        pthread_create(&threads[i], NULL, contarPrimos, (void *)args[i]);
    }

    for (int i = 0; i < qtdThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}