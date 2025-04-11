#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include"count.h" //funkcja value
#include"helpers.h"
//funkcja fabs = abs dla double/float
//value(double* tab, int n, double x)

double rectangle(double a, double b, double* tab1, int n1, double* tab2, int n2, int num, int ch_c);
double trapez(double a, double b, double* tab1, int n1, double* tab2, int n2, int num, int ch_c);
double montecarlo(double a, double b, double* tab1, int n1, double* tab2, int n2, int num, int ch_c);

double rectangle(double a, double b, double* tab1, int n1, double* tab2, int n2, int num, int ch_c) {
	double step = (double)(b - a) / num;
	double wynik = 0.0;
	if (ch_c == 1) {
		for (int i = 0; i < num; ++i) {
			wynik += fabs(value(tab1, n1, a + (i + 1) * step));
		}
	}
	if (ch_c == 2) {
		for (int i = 0; i < num; ++i) {
			wynik += fabs(value1(tab1, n1, tab2, n2, a + (i + 1) * step));
		}
	}
	else {
		for (int i = 0; i < num; ++i) {
			wynik += fabs(value_r(a + (i + 1) * step, ch_c));
		}
	}
	wynik = wynik * step;
	return wynik;
}

double trapez(double a, double b, double* tab1, int n1, double* tab2, int n2, int num, int ch_c) {
	double step = (b - a) / num;
	double wynik = 0.0;

	if (ch_c == 1) {
		for (int i = 0; i < num; ++i) {
			wynik += fabs((float)0.5 * step * (value(tab1, n1, a + i * step) + value(tab1, n1, a + (i + 1) * step)));
		}
	}
	if (ch_c == 2) {
		for (int i = 0; i < num; ++i) {
			wynik += fabs((float)0.5 * step * (value1(tab1, n1, tab2, n2, a + i * step) + value1(tab1, n1, tab2, n2, a + (i + 1) * step)));
		}
	}
	else {
		for (int i = 0; i < num; ++i) {
			wynik += fabs((float)0.5 * step * (value_r(a + i * step, ch_c) + value_r(a + (i + 1) * step, ch_c)));
		}
	}
	return wynik;
}
double montecarlo(double a, double b, double* tab1, int n1, double* tab2, int n2, int num, int ch_c) {
	srand((unsigned int)time(NULL));
	double maxval = 0;
	maxx(a, b, tab1, n1, tab2, n2, &maxval, ch_c);

	int points = 0;
	
	for (int i = 0; i < num; ++i) {
		double x = a + ((double)rand() / RAND_MAX) * (b - a);
		double y = 0 + ((double)rand() / RAND_MAX) * maxval;
		double v = 0;
		if (ch_c == 1) {
			v = fabs(value(tab1, n1, x));
		}
		if (ch_c == 2) {
			v = fabs(value1(tab1, n1, tab2, n2, x));
		}
		else {
			v = fabs(value_r(x, ch_c));
		}
		if (y <= v) {
			++points;
		}
	}
	double pole = 0.0;
	pole = (b - a) * maxval;
	return (double)points / num * pole;
}
