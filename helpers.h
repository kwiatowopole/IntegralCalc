#pragma once

int deg(); //podanie stopnia wielomianu
void cinput(double* tab, int n); //wprowadzanie wspolczynnikow
double* wielomian(double* coefs, int n); //wywo�uje cinput i zwraca tablic� wspolczynnikow
int cont(double a, double b, double* coefs, int n); //sprawdza istnienie miejsca zerowego wielomianu (bruteforce)
int signum(double a); //zwraca znak
void maxx(double a, double b, double* coefs1, int n1, double* coefs2, int n2, double* maxval, int ch_c);