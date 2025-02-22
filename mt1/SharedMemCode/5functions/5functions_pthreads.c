#include <stdio.h>
#include <pthread.h>

// Funciones A B C D E

void* functionA(void* arg) {
	printf("Soy la funcion A\n");
	return NULL;
}

void* functionB(void* arg) {
	printf("Soy la funcion B\n");
	return NULL;
}

void* functionC(void* arg) {
	printf("Soy la funcion C\n");
	return NULL;
}

void* functionD(void* arg) {
	printf("Soy la funcion D\n");
	return NULL;
}

void functionE() {
	printf("Soy la funcion E\n");
}

int main(){
	pthread_t tA, tB, tC, tD;

	pthread_create(&tA, NULL, functionA, NULL);

	pthread_create(&tB, NULL, functionB, NULL);
	pthread_create(&tC, NULL, functionC, NULL);
	pthread_join(tB, NULL);
	pthread_join(tC, NULL);

	pthread_create(&tD, NULL, functionD, NULL);
	pthread_join(tA, NULL);
	pthread_join(tD, NULL);

	functionE();

	pthread_exit(NULL);
	return 0;
}

