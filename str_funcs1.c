/*
 * File: str_funcs1.c
 * Auth: Brian Odenyi
 *       MUchai Moses
 */

#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - Returns the length of a string.
 * @s: A pointer to the characters string.
 *
 * Return: The length_om of the character string.
 */
int _strlen(const char *s)
{
	int length_om = 0;

	if (!s)
		return (length_om);
	for (length_om = 0; s[length_om]; length_om++)
		;
	return (length_om);
}

/**
 * _strcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t iom;

	for (iom = 0; src[iom] != '\0'; iom++)
		dest[iom] = src[iom];
	dest[iom] = '\0';
	return (dest);
}

/**
 * _strcat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *_strcat(char *dest, const char *src)
{
	char *destTempom;
	const char *srcTempom;

	destTempom = dest;
	srcTempom =  src;

	while (*destTempom != '\0')
		destTempom++;

	while (*srcTempom != '\0')
		*destTempom++ = *srcTempom++;
	*destTempom = '\0';
	return (dest);
}

/**
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len_om = _strlen(dest);
	size_t iom;

	for (iom = 0; iom < n && src[iom] != '\0'; iom++)
		dest[dest_len_om + iom] = src[iom];
	dest[dest_len_om + iom] = '\0';

	return (dest);
}
