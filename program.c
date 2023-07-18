#include <stdio.h>
/**
 * add - funtion that adds two numbers
 * @a: integer parameter
 * @b: integer parameter
 * Return: the result of a + b
 */

int add(int a, int b)
{
	return (a + b);
}

/**
 * main - the program starts here
 *
 * Return: nothing
 */

int main(void)
{
	int a, b;
	int result = add(10, 5);

	printf("a + b = %d\n", result);
	return (0);
}
