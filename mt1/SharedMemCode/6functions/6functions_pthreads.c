#include <stdio.h>
#include <time.h>
#include <pthread.h>

// Estructura de datos para la info de tiempo

typedef struct {
    const char* funcName;         // Name of the function (for logging).
    struct timespec creationTime; // Time when pthread_create was called.
} ThreadInfo;

// Funcion auxiliar de calculo de tiempo

void print_wait_time(const char* funcName, struct timespec creationTime) {
    struct timespec startTime;
    clock_gettime(CLOCK_MONOTONIC, &startTime);
    double waitTime = (startTime.tv_sec - creationTime.tv_sec) +
                      (startTime.tv_nsec - creationTime.tv_nsec) / 1e9;
    printf("\n %s ha esperado %.6f segundos para ejecutarse \n", funcName, waitTime);
}

// Funciones A B C D E F

void* functionA(void* arg) {
	ThreadInfo* info = (ThreadInfo*) arg;
    print_wait_time(info->funcName, info->creationTime);
	printf("Soy la funcion A\n");
	return NULL;
}

void* functionB(void* arg) {
	ThreadInfo* info = (ThreadInfo*) arg;
    print_wait_time(info->funcName, info->creationTime);
	printf("Soy la funcion B\n");
	return NULL;
}

void* functionC(void* arg) {
	ThreadInfo* info = (ThreadInfo*) arg;
    print_wait_time(info->funcName, info->creationTime);
	printf("Soy la funcion C\n");
	return NULL;
}

void* functionD(void* arg) {
	ThreadInfo* info = (ThreadInfo*) arg;
    print_wait_time(info->funcName, info->creationTime);
	printf("Soy la funcion D\n");
	return NULL;
}

void functionE() {
	printf("Soy la funcion E\n");
}

void* functionF(void* arg) {
	ThreadInfo* info = (ThreadInfo*) arg;
    print_wait_time(info->funcName, info->creationTime);
	printf("Soy la funcion F\n");
	return NULL;
}

int main(){
	pthread_t tA, tB, tC, tD, tF;
	ThreadInfo infoA = { "A", {0} };
    ThreadInfo infoB = { "B", {0} };
    ThreadInfo infoC = { "C", {0} };
    ThreadInfo infoD = { "D", {0} };
	ThreadInfo infoF = { "F", {0} };

	clock_gettime(CLOCK_MONOTONIC, &infoA.creationTime);
	pthread_create(&tA, NULL, functionA, &infoA);
	clock_gettime(CLOCK_MONOTONIC, &infoB.creationTime);
	pthread_create(&tB, NULL, functionB, &infoB);
	clock_gettime(CLOCK_MONOTONIC, &infoC.creationTime);
	pthread_create(&tC, NULL, functionC, &infoC);
	pthread_join(tA, NULL);
	pthread_join(tB, NULL);
	pthread_join(tC, NULL);

	clock_gettime(CLOCK_MONOTONIC, &infoD.creationTime);
	pthread_create(&tD, NULL, functionD, &infoD);
	clock_gettime(CLOCK_MONOTONIC, &infoF.creationTime);
	pthread_create(&tF, NULL, functionF, &infoF);
	pthread_join(tD, NULL);
	pthread_join(tF, NULL);

	functionE();

	pthread_exit(NULL);
	return 0;
}
