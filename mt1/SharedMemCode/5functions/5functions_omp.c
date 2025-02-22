#include <stdio.h>
#include <omp.h>

// Funciones A B C D E
void functionA() { printf("Soy la funcion A\n"); }
void functionB() { printf("Soy la funcion B\n"); }
void functionC() { printf("Soy la funcion C\n"); }
void functionD() { printf("Soy la funcion D\n"); }
void functionE() { printf("Soy la funcion E\n"); }

int main(){
	#pragma omp parallel
	{
		#pragma omp single 
		{
			#pragma omp task
			{ functionA(); } 
			#pragma omp task
			{ functionB(); } 
			#pragma omp task
			{ functionC(); }
			#pragma omp taskwait

			#pragma omp task
			{ functionD(); }
			#pragma omp taskwait

			functionE();
		}
	}
	return 0;
}
