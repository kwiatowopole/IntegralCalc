#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include"count.h" //float value(double* tab, int n, double x)

//deklaracje globalne
int deg(); //podanie stopnia wielomianu
void cinput(double* tab, int n); //wprowadzanie wspolczynnikow
double* wielomian(double* coefs, int n); //wywo³uje cinput i zwraca tablicê wspolczynnikow
int cont(double a, double b, double* coefs, int n); //sprawdza istnienie miejsca zerowego wielomianu (bruteforce)
int signum(double a); //zwraca znak
void maxx(double a, double b, double* coefs1, int n1, double* coefs2, int n2, double* maxval, int ch_c);
//input z funkcji main


//cia³a funkcji
int signum(double a) {
	return (a>0)-(a<0);
}

int deg() {
	int n;
	printf("Podaj stopieñ: ");
	while (scanf_s("%d", &n) < 1 || n < 0) {
		printf("Podano bledne dane, podaj ponownie: ");
	}
	return n + 1;
}

void cinput(double* tab, int n) {
	for (int i = 0; i < n; ++i) {
		printf("Wspolczynnik przy potedze %d: ", i);
		while (scanf_s("%lf", &tab[i]) < 1) {
			printf("Wprowadz ponownie: ");
		}
	}
}

double* wielomian(double* coefs, int n) {
	cinput(coefs, n);
	return coefs;
}

//value wyglada tak: value(float* tab, int n, float x)
int cont(double a, double b, double* coefs, int n) {
	float eps = 1e6;
	float step = (float)(b - a) / eps;
	float z = a;
	if (signum(value(coefs, n, a)) != signum(value(coefs, n, b)) || value(coefs, n, a)==0 || value(coefs, n, b)==0) {
		return 1;
	}
	int ref = signum(value(coefs, n, a));
	for (int i=0; i < eps; ++i) {
		z += step;
		if (signum(value(coefs, n, z)) != ref || value(coefs, n, z)==0) { return 1; }
	}
	//printf("dzialam\n");
	return -1;
}

//double minval(double a, double b, double* coefs, int n) {
//	double eps = 1e6;
//	double step = (b - a) / eps;
//	double z = a;
//	double wynik = value(coefs, n, a);
//	for (int i = 0; i < eps; ++i) {
//		z += step;
//		if (value(coefs, n, z) < wynik) {
//			wynik = value(coefs, n, z);
//		}
//	}
//	return wynik;
//}

void maxx(double a, double b, double* coefs1, int n1, double* coefs2, int n2, double *maxval, int ch_c) {
	double eps = 1e6;
	double step = (b - a) / eps;
	
	if (ch_c == 1) {
		*maxval = value(coefs1, n1, a);
		for (double i = a; i <= b; i += step) {
			double v = value(coefs1, n1, i);
			if (v > *maxval) {
				*maxval = v;
			}
		}
	}
	if (ch_c == 2) {
		*maxval = value1(coefs1, n1, coefs2, n2, a);
		for (double i = a; i <= b; i += step) {
			double v = value1(coefs1, n1, coefs2, n2, i);
			if (v > *maxval) {
				*maxval = v;
			}
		}
	}
	else {
		*maxval = value_r(a, ch_c);
		for (double i = a; i <= b; i += step) {
			double v = value_r(i, ch_c);
			if (v > *maxval) {
				*maxval = v;
			}
		}
	}
}