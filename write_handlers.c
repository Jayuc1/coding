#include "main.h"

/**
 * handle_write_char - Prints a string
 * Parameters:
 * @c: Function parameter 1
 * @buffer: Function parameter 2
 * @flags: Function parameter 3
 * @width: Function parameter 4
 * @precision: Function parameter 5
 * @size: Function parameter 6
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size)
{
	/* char is stored at left and paddind at buffer's right */
	int k = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';
	buffer[k++] = c;
	buffer[k] = '\0';
	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (k = 0; k < width - 1; k++)
			buffer[BUFF_SIZE - k - 2] = padd;
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - k - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - k - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}

/**
 * write_number - Prints a string
 * Parameters:
 * @is_negative: Function parameter 1
 * @ind: Function parameter 2
 * @buffer: Function parameter 3
 * @flags: Function parameter 4
 * @width: Function parameter 5
 * @precision: Function parameter 6
 * @size: Function parameter 7
 * Return: Number of chars printed
 */
int write_number(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', ch = 0;


        UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		ch = '-';
	else if (flags & F_PLUS)
		ch = '+';
	else if (flags & F_SPACE)
		ch = ' ';
	return (write_num(ind, buffer, flags, width, precision,
				length, padd, ch));
}

/**
 * write_num - Write a number using a bufffer
 * Parameters:
 * @ind: Function parameter 1
 * @buffer: Function parameter 2
 * @flags: Function parameter 3
 * @width: Function parameter 4
 * @prec: Function parameter 5
 * @length: Function parameter 6
 * @padd: Function parameter 7
 * @extra_c: Function parameter 8
 * Return: Number of printed chars
 */
int write_num(int ind, char buffer[],
		int flags, int width, int prec,
		int len, char padd, char extra_c)
{
	int k, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < len)
		padd = ' ';
	while (prec > len)
		buffer[--ind] = '0', len++;
	if (extra_c != 0)
		len++;
	if (width > len)
	{
		for (k = 1; k < width - len + 1; k++)
			buffer[k] = padd;
		buffer[k] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], len) + write(1, &buffer[1], k - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], k - 1) + write(1, &buffer[ind], len));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], k - padd_start) +
					write(1, &buffer[ind], len - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * Parameters:
 * @is_negative: Function parameter 1
 * @ind: Function parameter 2
 * @buffer: Function parameter 3
 * @flags: Function parameter 4
 * @width: Function parameter 5
 * @precision: Function parameter 6
 * @size: Function parameter 7
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int len = BUFF_SIZE - ind - 1, k = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */
	if (precision > 0 && precision < len)
		padd = ' ';
	while (precision > len)
	{
		buffer[--ind] = '0';
		len++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (width > len)
	{
		for (k = 0; k < width - len; k++)
			buffer[k] = padd;
		buffer[k] = '\0';
		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], len) + write(1, &buffer[0], k));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], k) + write(1, &buffer[ind], len));
		}
	}
	return (write(1, &buffer[ind], len));
}

/**
 * write_pointer - Write a memory address
 * Parameters:
 * @buffer: Function parameter 1
 * @ind: Function parameter 2
 * @length: Function parameter 3
 * @width: Function parameter 4
 * @flags: Function parameter 5
 * @padd: Function parameter 6
 * @extra_c: Function parameter 7
 * @padd_start: Function parameter 8
 * Return: Number of written chars
 */
int write_pointer(char buffer[], int ind, int length,
		int width, int flags, char padd, char extra_c, int padd_start)
{
	int k;

	if (width > len)
	{
		for (i = 3; k < width - len + 3; k++)
			buffer[k] = padd;
		buffer[k] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], len) + write(1, &buffer[3], k - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], k - 3) + write(1, &buffer[ind], len));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], k - padd_start) +
					write(1, &buffer[ind], len - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
