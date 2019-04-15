#include <stdio.h>
#define c1 3.1415
#define c2 1.61802

double modulo(double n);
double frac(double n);
double seno(double n);
double pseudorand(double x);

int main(){
	double x = 0.11221776;	
	double num = 4.4534;

	printf("%d", frac(num));




return (0);
}


double modulo(double n){
	if (n < 0 )
		n = -n;
	return (n);
}

double frac(double n){
	int integer;
	double frac;
	integer = n; // verificar isso
	frac = n - integer;
	return (integer);
}

double seno(double n){
	


}

double pseudorand(double x){
	x = frac(c1 * modulo(seno(x)) + c2);
	return (x);
}






