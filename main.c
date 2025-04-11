#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include"filemng.h" //writetofile - wtf()
#include"helpers.h" //input(), cont()
#include"methods.h"
#include"count.h"

double abinput(double a);//wprowadzanie wartoúci typu double - tak bylo latwiej

double abinput(double a) {
	while (scanf_s("%lf", &a) < 1) {
		printf("B≥πd. Wprowadü ponownie: ");
	}
	return a;
}

int main() {
	setlocale(LC_ALL, "");
	double a=0.0, b=0.0;
	int ch_m=0, ch_c=0,n=0;
	double eps=0.0;
	double wynik=0.0;
	const char* metoda;
	int mode=0;
	int yes = 0;

	printf("Wybierz jakπ funkcjÍ chcesz ca≥kowaÊ:\n");
	printf("1. Wielomian\n");
	printf("2. Funkcja wymierna\n");
	printf("3. sin(ln|x|)\n"); //sin(log(fabs(x)))
	printf("4. x*cos(x^2))\n"); //x*cos(pow(x,2))
	printf("5. e^(sin(x^2))\n"); //exp(sin(pow(x,2))
	printf("6. cosh(e^sinx))\n"); //cosh(exp(sin(x)))
	while (scanf_s("%d", &ch_c) < 1 || ch_c>6 || ch_c<1) {
		printf("B≥πd. Wprowadü ponownie: ");
	}
	if (ch_c > 2) { printf("\n"); }
	//wywo≥anie wyboru parametrow wybranej funkcji
	double* coefs1=0, * coefs2 = NULL;
	int n1=0, n2=0;
	switch (ch_c) {
		case 1:
			printf("Wybierz stopieÒ wielomianu\n");
			n1 = deg();
			coefs1 = (double*)malloc(n1 * sizeof(coefs1));
			if (coefs1 == NULL) {
				printf("Blad alokacji pamieci!");
				return;
			}
			else {
				coefs1 = wielomian(coefs1, n1);
			}
			break;

		case 2:
			printf("Wybierz stopieÒ wielomianu w liczniku\n");
			n1 = deg();
			printf("Wybierz stopieÒ wielomianu w mianowniku\n");
			n2 = deg();

			coefs1 = (double*)malloc(n1 * sizeof(coefs1));
			coefs2 = (double*)malloc(n2 * sizeof(coefs2));
			if (coefs1 == NULL || coefs2 == NULL) {
				printf("Blad alokacji pamieci!");
				return;
			}
			else {
				printf("WybÛr wspÛ≥czynnikÛw licznika:\n");
				coefs1 = wielomian(coefs1, n1);
				printf("WybÛr wspÛ≥czynnikÛw mianownika:\n");
				coefs2 = wielomian(coefs2, n2);
			}
			break;
		default:
			break;
	}
	if (ch_c > 2) { printf("\n"); }

	//wprowadzenie granic calkowania - sprawdzenie czy funkcja wymierna jest ciπgla
	if (ch_c != 2) {
		printf("Wprowadz lewπ granicÍ ca≥kowania (a): ");
		a = abinput(a);
		printf("Wprowadz prawπ granicÍ ca≥kowania (b): ");
		b = abinput(b);
	}
	else {
		int ciagla=1;
		while (ciagla == 1) {
			printf("Wprowadz lewa granice calkowania (a): ");
			a = abinput(a);
			printf("Wprowadz prawπ granicÍ ca≥kowania (b): ");
			b = abinput(b);
			ciagla = cont(a, b, coefs2, n2);
			//printf("ciagla = %d\n", ciagla);
			if (ciagla == 1) {
				printf("Funkcja nieciπg≥a na zadanym przedziale, wprowadü inne granice\n");
			}
		}
	}

	printf("Wybierz metodÍ ca≥kowania:\n");
	printf("1. Metoda prostokπtow\n");
	printf("2. Metoda trapezÛw\n");
	printf("3. Metoda Monte Carlo\n");
	while (scanf_s("%d", &ch_m) < 1) {
		printf("B≥πd. Wprowadü ponownie: ");
	}

	if (ch_c > 2) { printf("\n"); }

	printf("Chcesz uøyÊ okreúlonej liczby interwa≥Ûw, czy podajesz dok≥adnoúÊ\n");
	printf("1. Okreúlona liczba interwa≥Ûw\n");
	printf("2. PodajÍ dok≥adnoúÊ\n");
	while (scanf_s("%d", &mode) < 1) {
		printf("B≥πd. Wprowadü ponownie: ");
	}

	if (ch_c > 2) { printf("\n"); }

	if (mode == 1) {
		printf("Wprowadü liczbÍ interwa≥Ûw (n): ");
		while (scanf_s("%d", &n) < 1) {
			printf("B≥πd. Wprowadü ponownie: ");
		}

		switch (ch_m) {
		case 1:
			metoda = "Metoda prostokπtÛw";
			wynik = rectangle(a, b, coefs1, n1, coefs2, n2, n, ch_c);
			break;
		case 2:
			metoda = "Metoda trapezÛw";
			wynik = trapez(a, b, coefs1, n1, coefs2, n2, n, ch_c);
			break;
		case 3:
			metoda = "Metoda Monte Carlo";
			wynik = montecarlo(a, b, coefs1, n1, coefs2, n2, n, ch_c);
			break;
		default:
			return 1;
		}
	}
	else {
		printf("Wprowadü dok≥adnoúÊ (eps): ");
		while (scanf_s("%lf", &eps) < 1 || eps<0) {
			printf("B≥πd. Wprowadü ponownie: ");
		}
		n = 1;
		double prev;
		//printf("%lf\n", eps);
		
		switch (ch_m) {
		case 1:
			metoda = "Metoda prostokπtÛw";
			do {
				prev = wynik;
				wynik = rectangle(a, b, coefs1, n1, coefs2, n2, n, ch_c);
				n *= 2;
			} while (fabs(wynik - prev) > eps);
			break;

		case 2:
			metoda = "Metoda trapezÛw";
			do {
				prev = wynik;
				wynik = trapez(a, b, coefs1, n1, coefs2, n2, n, ch_c);
				n *= 2;
			} while (fabs(wynik - prev) > eps);
			break;

		case 3:
			metoda = "Metoda Monte Carlo";
			n = 1U << 14;
			do {
				prev = wynik;
				wynik = montecarlo(a, b, coefs1, n1, coefs2, n2, n, ch_c);
				n<<1;
			} while (fabs(wynik - prev) > eps);
			break;

		default:
			//printf("èle wprowadzony wybÛr\n");
			return 1;
		}
	}
	printf("\n");

	printf("Wynik: %lf\n", wynik); //wypisanie wyniku na ekran
	wtf("wynik.txt", wynik, metoda); //wypisanie wyniku do pliku wywolujac funkcje write_to_file z pliku filemng.c
	
	printf("Czy chcesz porÛwnaÊ otrzymany wynik z wynikami moøliwymi do otrzymania innymi metodami?\n");
	printf("Tak: 1\nNie: dowolny klawisz\n");
	while (scanf_s("%d", &yes) < 1) {
		printf("B≥πd. Wprowadü ponownie: ");
	}

	if (yes) {
		switch (ch_m) {
		case 1:
			printf("Metoda trapezow: %lf\n", trapez(a, b, coefs1, n1, coefs2, n2, n, ch_c));
			printf("Metoda Monte Carlo: %lf\n", montecarlo(a, b, coefs1, n1, coefs2, n2, n, ch_c));
			break;
		case 2:
			printf("Metoda prostokatow: %lf\n", rectangle(a, b, coefs1, n1, coefs2, n2, n, ch_c));
			printf("Metoda Monte Carlo: %lf\n", montecarlo(a, b, coefs1, n1, coefs2, n2, n, ch_c));
			break;
		case 3:
			printf("Metoda trapezow: %lf\n", trapez(a, b, coefs1, n1, coefs2, n2, n, ch_c));
			printf("Metoda prostokatow: %lf\n", rectangle(a, b, coefs1, n1, coefs2, n2, n, ch_c));
			break;
		default:
			break;
		}
	}
}