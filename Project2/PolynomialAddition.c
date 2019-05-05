#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101 /* size of terms array */
#define COMPARE(x, y) ( ((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1 )

typedef struct {
	float coef;
	int expon;
} term;
term terms[MAX_TERMS];

int avail = 0;
int start[2] = { 0, }, finish[2] = { 0, };

/* add a new term to the polynomial */
void attach(float coefficient, int exponent);
/* add A(x) and B(x) to obtain D(x) */
void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD);
/* print the polynomial in term array 'temrs' between [start, finish] */
void printPolynomial(int start, int finish);
/* attach the num polynomial to the array 'terms' and check exception */
void inputPolynomial(int num);

int main() {
	int startD=0;
	int finishD=0;
	printf("Input first polynomial.\n");
	inputPolynomial(0);
	printf("Input second polynomial.\n");
	inputPolynomial(1);
	padd(start[0], finish[0], start[1], finish[1], &startD, &finishD);
	printPolynomial(startD, finishD);
	return 0;
}

void attach(float coefficient, int exponent)
{
	if (avail >= MAX_TERMS)
	{
		fprintf(stderr, "Too many terms in the polynomial\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD)
{
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

void printPolynomial(int start, int finish) {
	for (int i = start; i <= finish; i++) {
		printf("%.3f", terms[i].coef);
		if (terms[i].expon != 0) {
			printf("x^%d", terms[i].expon);
		}
		if (i != finish)
			printf(" + ");
	}
}

void inputPolynomial(int num) {
	start[num] = avail;
	finish[num] = start[num];
	for (int i = 0;; i++) {
		float tempcoef = 0;
		float tempexpon = 0;
		/* check exception that tempcoef is not a float type */
		if (scanf("%f", &tempcoef) != 1) {
			printf("Input data in the correct format.");
			exit(EXIT_FAILURE);
		}
		/*
		while ((c = getchar()) == (char)32) {
			printf("space\n");
		}
		if (c == '\n') {
			printf("Input both coefficient and exponent.");
			exit(EXIT_FAILURE);
		}*/
		/**
		* ���� �ϰ� ������
		* ����� �Է¹޴´�
		* ��� ������ enter�� ���´�
		* enter�� �Էµ� ���� Ȯ�εǸ�
		* ���ܷ� ó���Ѵ�.

		* ���� ��Ȳ
		* enter�Է��� Ȯ���� ��
		* enter�� �ƴ϶� ����� �� ������ ���ٸ�
		* �� �����͸� ������ ����� ����.
		**/
		/* check exception that tempexpon is not a float type */
		if (scanf("%f", &tempexpon) != 1) {
			printf("Input data in the correct format.");
			exit(EXIT_FAILURE);
		}
		/* check exception that tempexpon is not 0 or natural number */
		if (tempexpon < 0 || (int)(tempexpon * 10) - ((int)tempexpon * 10)) {
			printf("The cofficient of term is not 0 or natural number.");
			exit(EXIT_FAILURE);
		}
		attach(tempcoef, (int)tempexpon);
		if (i != 0) finish[num]++;
		if (getchar() == '\n') break;
	}
}