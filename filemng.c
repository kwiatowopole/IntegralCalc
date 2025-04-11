#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//funkcja write to file
void wtf(const char* filename, double result, const char* method) {
    FILE* file;
    if (fopen_s(&file, filename, "a+")!=0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "--------------------------------\n");
    fprintf(file, "Method: %s\nResult: %lf\n", method, result);
    fclose(file);
}