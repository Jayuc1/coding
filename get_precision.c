#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * Paramemetrs:
 * @format: Function parameter 1
 * @i: Function parameter 2
 * @list: Function parameter 3
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int cur = *i + 1;
	int precision = -1;

	if (format[cur] != '.')
		return (precision);
	precision = 0;
	for (cur += 1; format[cur] != '\0'; cur++)
	{
		if (is_digit(format[cur]))
		{
			precision *= 10;
			precision += format[curr_i] - '0';
		}
		else if (format[cur] == '*')
		{
			cur++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = cur - 1;
	return (precision);
}
