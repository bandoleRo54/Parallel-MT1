#include <stdio.h>
#include <time.h>
#include <omp.h>

// Funcion auxiliar de calculo de tiempo

void print_wait_time(const char* funcName, struct timespec creationTime) {
    struct timespec startTime;
    clock_gettime(CLOCK_MONOTONIC, &startTime);
    double waitTime = (startTime.tv_sec - creationTime.tv_sec) +
                      (startTime.tv_nsec - creationTime.tv_nsec) / 1e9;
    printf("\n %s ha esperado %.6f segundos para ejecutarse \n", funcName, waitTime);
}

// Funciones A B C D E F
void functionA() { printf("Soy la funcion A\n"); }
void functionB() { printf("Soy la funcion B\n"); }
void functionC() { printf("Soy la funcion C\n"); }
void functionD() { printf("Soy la funcion D\n"); }
void functionE() { printf("Soy la funcion E\n"); }
void functionF() { printf("Soy la funcion F\n"); }

int main(){
	#pragma omp parallel
	{
		#pragma omp single 
		{
			struct timespec spawnTimeA, spawnTimeB, spawnTimeC;
			clock_gettime(CLOCK_MONOTONIC, &spawnTimeA);
			#pragma omp task firstprivate(spawnTimeA)
			{ print_wait_time("A", spawnTimeA); functionA(); } 
			clock_gettime(CLOCK_MONOTONIC, &spawnTimeB);
			#pragma omp task firstprivate(spawnTimeB)
			{ print_wait_time("B", spawnTimeB); functionB(); } 
			clock_gettime(CLOCK_MONOTONIC, &spawnTimeC);
			#pragma omp task firstprivate(spawnTimeC)
			{ print_wait_time("B", spawnTimeC); functionC(); }
			#pragma omp taskwait

			struct timespec spawnTimeD, spawnTimeF;
			clock_gettime(CLOCK_MONOTONIC, &spawnTimeD);
			#pragma omp task firstprivate(spawnTimeD)
			{ functionD(); }
			clock_gettime(CLOCK_MONOTONIC, &spawnTimeF);
			#pragma omp task firstprivate(spawnTimeF)
			{ functionF(); }
			#pragma omp taskwait

			struct timespec spawnTimeE;
            clock_gettime(CLOCK_MONOTONIC, &spawnTimeE);
            print_wait_time("E", spawnTimeE);
			functionE();
		}
	}
	return 0;
}
