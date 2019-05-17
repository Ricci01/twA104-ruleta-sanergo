/*Crear el juego de la ruleta simple*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> // libreria basica para entrada y salida  
#include <stdlib.h> // libreria para el uso de rand()  
#include <time.h>   // libreria para el uso de time()
FILE *Casino;        //archivo con saldo del casino

//Pedir el saldo inicial

int saldo_inicial() {
	long saldo;
	printf("\nBienvenido a la ruleta de casino de Javi y Diego\n\n");
	printf("Elija el saldo inicial deseado:");
	scanf_s("%ld", &saldo);
	printf("\n");
	system("cls");
	return saldo;
}
//Leer archivo con saldo inicial del casino Casino.txt

int saldo_casino_total() {
	long saldo_casino;
	Casino = fopen("Casino.txt", "r");
	if (Casino == NULL) {
		printf("\n Error de archivo \n");
	}
	else {
		while (feof(Casino) == 0) {
			fscanf(Casino, "%ld\n", &saldo_casino);
		}
	}
	fclose(Casino);
	return saldo_casino;
}

//Seleccionar el tipo de apuesta PAR, IMPAR, NUMERO 

int tipo_apuesta() {
	int tipo_a;
	printf("\nSeleccione el tipo de apuesta\n");
	printf("Par=1\nImpar=2\nNumero=3\n");
	int tipo_correcto = 0;

	//comprobar si el tipo de apuesta es corrcto

	while (tipo_correcto < 1) {
		scanf_s("%d", &tipo_a);
		if (tipo_a <= 3) {
			tipo_correcto++;
		}
		else {
			printf("Numero incorrecto, Seleccione el tipo de apuesta\n");
		}
	}
	printf("\n\n");
	system("cls");
	return tipo_a;
}
//Determinar el dinero que se quiera apostar

int apuesta() {
	int apuesta;
	printf("Cuanto dinero desea apostar?\n");
	scanf_s("%d", &apuesta);

	//Comprobar que se tiene suficiente dinero
	long saldo = saldo_inicial;
	if (apuesta > saldo) {
		printf("No tiene suficiente dinero\n");
	}
	else {
		printf("Apuesta correcta\n");
	}
	printf("\n\n");
	return apuesta;
}

//Generar número aleatorio

int girar() {
	int aleatorio;
	int hora = time(NULL);
	srand(hora); //srand inicializa el generador de números aleatorios con un valor basado en la hora actual, para que cada vez que se ejecute el programa tengamos números diferentes
	aleatorio = rand() % 37;
	printf("\n\n");
	return aleatorio;
}

//Actualizar el saldo del casino Casino.txt

int saldo_casino_fn(int saldo_casino) {
	Casino = fopen("Casino.txt", "r+");
	if (Casino == NULL) {
		printf("\n Error de archivo \n");
	}
	else {
		fprintf(Casino, "%d\n", saldo_casino);
		printf("%d\n", saldo_casino);
	}
	fclose(Casino);
	return 0;
}

//Comienza el juego

int main(void) {
	int giro;
	int apuesta_tipo;
	int saldo_apostado;
	int de_nuevo = 0;
	int S_N = 1;
	long saldo;
	long casino_saldo;

	casino_saldo = saldo_casino_total();
	saldo = saldo_inicial();

	//Creamos un bucle para jugar tantas veces como uno desee

	while (de_nuevo <= 0) {
		apuesta_tipo = tipo_apuesta();
		saldo_apostado = apuesta();

		//Hay que calcular los saldos tanto del casino como del usuario

		saldo = saldo - saldo_apostado;
		casino_saldo = casino_saldo + saldo_apostado;
		giro = girar();

		//Resultado de la apuesta

		if (apuesta_tipo == 1) {
			printf("El numero de la ruleta es: ");
			printf("\n***********\n*   %d    *\n***********\n\n", giro);
			if (giro % 2 == 0 && giro != 0) {
				printf("Ha ganado\n");
				saldo = saldo + 2 * saldo_apostado;
				casino_saldo = casino_saldo - 2 * saldo_apostado;
				printf("Su nuevo saldo es ");
				printf("%ld\n", saldo);
			}
			else {
					printf("Ha perdido\n");
					printf("Su nuevo saldo es ");
					printf("%ld\n", saldo);
			}
		}
		if (apuesta_tipo == 2) {
			printf("El numero de la ruleta es: ");
			printf("\n***********\n*   %d    *\n***********\n\n", giro);
			if (giro % 2 == 1 && giro != 0) {
				printf("Ha ganado\n");
				saldo = saldo + 2 * saldo_apostado;
				casino_saldo = casino_saldo - 2 * saldo_apostado;
				printf("Su nuevo saldo es ");
				printf("%ld\n", saldo);
			}
			else {
					printf("Ha perdido\n");
					printf("Su nuevo saldo es ");
					printf("%ld\n", saldo);
			}
		}
		if (apuesta_tipo == 3) {
			int numero_apostado;
			printf("Elija el numero de la ruleta al que quiere apostar\n");
			do {
				scanf_s("%d", &numero_apostado);
			} while ((numero_apostado > 36) || (numero_apostado < 0));
			printf("Numero incorrecto, vuelva a intentarlo\n");



			printf("El numero de la ruleta es: \n");
			printf("\n***********\n*   %d    *\n**********\n\n", giro);

			if (giro == numero_apostado && giro != 0) {
				printf("Ha ganado\n");
				saldo = saldo + 36 * saldo_apostado;
				casino_saldo = casino_saldo - 36 * saldo_apostado;
				printf("Su nuevo saldo es ");
				printf("%ld\n", saldo);
			}
			else {
				printf("Ha perdido\n");
				printf("Su nuevo saldo es ");
				printf("%ld\n", saldo);
			}
			
		}
		printf("\n\n");
		saldo_casino_fn(casino_saldo);

		int continuar = 0;

		//Preguntar si se desea seguir jugando

		while (continuar < 1) {
			printf("¿Desea seguir jugando \n Si=1 \n No=2 \n");
			scanf_s("%d", &S_N);
			if (saldo == 0) {
				de_nuevo++;
				printf("Lo sentimos, su saldo se ha agotado\n");
				continuar++;
			}
			if (S_N == 1) {
				printf("Continue\n");
				continuar++;
			}
			if (S_N == 2) {
				de_nuevo++;
				printf("\n");
				continuar++;
			}

			if (S_N != 1 && S_N != 2) {
				printf("Numero incorrecto\n");
			}
		}
		system("cls");
	}
	printf("\n\n");
	return 0;
}
