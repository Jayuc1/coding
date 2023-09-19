#include "main.h"

/**
 * print_char - Prints a char
 * Parameters:
 * @types: Function parameter 1
 * @buffer: Function parameter 2
 * @flags: Function parameter 3
 * @width: Function parameter 4
 * @precision: Function parameter 5
 * @size: Function parameter 6
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);
	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**

 * print_string - Prints a string
 * Parameters:
 * @types: Function parameter 1
 * @buffer: Function parameter 2
 * @flags: Function parameter 3
 * @width: Function parameter 4
 * @precision: Function parameter 5
 * @size: Function parameter 6
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int k;

	int len = 0;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[len] != '\0')
		len++;
	if (precision >= 0 && precision < len)
		leng = precision;
	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (k = width - len; k > 0; k--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (k = width - len; k > 0; k--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}
	return (write(1, str, len));
}

/**
 * print_percent - Prints a percent sign
 * Parameters:
 * @types: Function parameter 1
 * @buffer: Function parameter 2
 * @flags: Function parameter 3
 * @width: Function parameter 4
 * @precision: Function parameter 5
 * @size: Function parameter 6
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - Print int
 * Parameters:
 * @types: Function parameter 1
 * @buffer: Function parameter 2
 * @flags: Function parameter 3
 * @width: Function parameter 4
 * @precision: Function parameter 5
 * @size: Function parameter 6
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int k = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);
	if (n == 0)
		buffer[k--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;
	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[k--] = (num % 10) + '0';
		num /= 10;
	}
	k++;
	return (write_number(is_negative, k, buffer, flags, width, precision, size));
}

/**
 * print_binary - Prints an unsigned number
 * Parameters:
 * @types: Function parameter 1
 * @buffer: Function parameter 2
 * @flags: Function parameter 3
 * @width: Function parameter 4
 * @precision: Function parameter 5
 * @size: Function parameter 6
 * Return: Number of chars printed
 */
int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned int n, m, k, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (k = 1; k < 32; k++)
	{
		m /= 2;
		a[k] = (n / m) % 2;
	}
	for (k = 0, sum = 0, count = 0; k < 32; k++)
	{
		sum += a[k];
		if (sum || k == 31)
		{
			char z = '0' + a[k];
			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
