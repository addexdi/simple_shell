#include <stdio.h>
#include <stdlib.h>

/**
 * main - returns the length of a string
 * Return: 0
 */

int main(void)
{
	double num1;
	double num2;
	char op;

	printf("Enter a number: ");
	scanf("%lf", &num1);
	printf("Enter operator: ");
	scanf(" %c", &op);
	printf("Enter a number: ");
	scanf("%lf", &num2);

	if (op == '+')
	{
		printf("%f", num1 + num2);
	}
	else if (op == '-')
	{
		printf("%f", num1 - num2);
	}
	else if (op == '/')
	{
		printf("%f", num1 / num2);
	}
	else if (op == '*')
	{
		printf("%f", num1 * num2);
	}
	else
	{
		printf("Invalid ");
	}
	printf("\n");

	return (0);
}

