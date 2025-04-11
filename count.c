#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double value(double* tab, int n, double x);//zwraca wartosc wielomianu w danym punkcie
//przyjmuje argumenty: tablica wspolczynnikow, stopien wielomianu, punkt do obliczenia
double value1(double* tab1, int n1, double* tab2, int n2, double x);
double value_r(double x, int ch_c);

double value(double* tab, int n, double x) {
	double output = tab[0];
	double x_n = x;
	for (int i = 1; i < n; ++i) {
		output = output + x_n * tab[i];
		x_n = x_n * x;
	}
	return output;
}

double value1(double* tab1, int n1, double* tab2, int n2, double x) {
	return value(tab1, n1, x) / value(tab2, n2, x);
}

double value_r(double x, int ch_c) {
	switch (ch_c) {
	case 3:
		return sin(log(fabs(x)));
		break;
	case 4:
		return x * cos(pow(x, 2));
		break;
	case 5:
		return exp(cos(pow(x, 2)));
		break;
	case 6:
		return cosh(exp(sin(x)));
		break;
	default:
		break;
	}
}