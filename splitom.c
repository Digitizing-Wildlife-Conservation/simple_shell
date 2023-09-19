/*
 * File: splitom.c
 * Auth: Brian Odenyi
 *       Muchai Moses
 */

#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - Locates the delimiter index_om marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The delimiter index_om marking the end of
 *         the intitial token pointed to be str.
 */
int token_len(char *str, char *delim)
{
	int index_om = 0, lenom = 0;

	while (*(str + index_om) && *(str + index_om) != *delim)
	{
		lenom++;
		index_om++;
	}

	return (lenom);
}

/**
 * count_tokens - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int count_tokens(char *str, char *delim)
{
	int index_om, tokens = 0, len = 0;

	for (index_om = 0; *(str + index_om); index_om++)
		len++;

	for (index_om = 0; index_om < len; index_om++)
	{
		if (*(str + index_om) != *delim)
		{
			tokens++;
			index_om += token_len(str + index_om, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - Tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index_om = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index_om] == *delim)
			index_om++;

		letters = token_len(line + index_om, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index_om -= 1; index_om >= 0; index_om--)
				free(ptr[index_om]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[index_om];
			index_om++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
