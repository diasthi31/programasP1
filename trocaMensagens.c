#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int ehPrimo(int numero) {
	if (numero < 2) return 0;
	for (int i = 2; i <= sqrt(numero); i++) {
		if (numero % i == 0) return 0;
	}
	return 1;
}

int main(int argc, char *argv[]) {
	int idProcesso, qtdProcessos, tamanhoVetor, contador = 0;

	tamanhoVetor = atoi(argv[2]);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &idProcesso);
	MPI_Comm_size(MPI_COMM_WORLD, &qtdProcessos);

	int numeros[tamanhoVetor];
	for (int i = 0; i < tamanhoVetor; i++) {
		numeros[i] = i + 1;
	}

	int tamanhoDividido = tamanhoVetor / qtdProcessos;
	int numerosDivididos[tamanhoDividido];

	MPI_Scatter(numeros, tamanhoDividido, MPI_INT, numerosDivididos, tamanhoDividido, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < tamanhoDividido; i++) {
		if (ehPrimo(numerosDivididos[i])) {
			contador++;
		}
	}

	int totalPrimos = 0;
	MPI_Reduce(&contador, &totalPrimos, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	MPI_Finalize();
	return 0;
}
