#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100 /* size of terms array */

typedef struct {
	float coef;
	int expon;
} polynomial;
polynomial terms[MAX_TERMS];
int avail = 0;
int startA = 0, finishA = 0, startB = 0, finishB = 0;

void attach(float coefficient, int exponent);

#define COMPARE(x, y) ( ((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1 )
void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD)
{ /* add A(x) and B(x) to obtain D(x) */
	float coefficient;
	*startD = avail;
	while (startA <= finishA && startB <= finishB)
		switch (COMPARE(terms[startA].expon, terms[startB].expon))
		{
		case -1: /* a expon < b expon */
			attach(terms[startB].coef, terms[startB].expon);
			startB++;
				break;
		case 0: /* equal exponents */
			coefficient = terms[startA].coef + terms[startB].coef;
			if (coefficient)
				attach(coefficient, terms[startA].expon);
			startA++;
			startB++;
			break;
		case 1: /* a expon > b expon */
			attach(terms[startA].coef, terms[startA].expon);
			startA++;
		} /* end of switch */
	/* add in remaining terms of A(x) */
	for (; startA <= finishA; startA++)
	{
		attach(terms[startA].coef, terms[startA].expon);
	}
	/* add in remaining terms of B(x) */
	for (; startB <= finishB; startB++)
	{
		attach(terms[startB].coef, terms[startB].expon);
	}
	*finishD = avail - 1;
}

void attach(float coefficient, int exponent)
{
	/* add a new term to the polynomial */
	if (avail >= MAX_TERMS)
	{
		fprintf(stderr, "Too many terms in the polynomial\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}
int main() {
	printf("Input first polynomial.\n");
	for (int i = 0;; i++) {
		float tempexpon = 0;
		if (scanf("%f", &terms[i].coef) != 1) {
			printf("Input data in the correct format.");
			exit(EXIT_FAILURE);
		}
		int a = scanf("%f", &tempexpon);
		if (a!= 1){
			printf("Input data in the correct format.");
			exit(EXIT_FAILURE);
		}
		if (tempexpon < 0 || (int)(tempexpon * 10) - ((int)tempexpon * 10)) {
			printf("The cofficient of term is not natrual number.");
			exit(EXIT_FAILURE);
		}
		terms[i].expon = (int)tempexpon;
		if(i!=0) finishA++;
		if (getchar() == '\n') break;
	}
	for (int i = startA; i <= finishA; i++) {
		printf("%.3f", terms[i].coef);
		if (terms[i].expon != 0) {
			printf("x^%d", terms[i].expon);
		}
		if (i != finishA)
			printf(" + ");
	}
	return 0;
}