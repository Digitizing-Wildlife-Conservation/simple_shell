/*
 * File: err_msgsom2.c
 * Auth: Brian Odenyi
 *       Muchai Moses
 */

#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_126(char **args)
{
	char *error_om, *hist_str_om;
	int len;

	hist_str_om = _itoa(hist);
	if (!hist_str_om)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str_om) + _strlen(args[0]) + 24;
	error_om = malloc(sizeof(char) * (len + 1));
	if (!error_om)
	{
		free(hist_str_om);
		return (NULL);
	}

	_strcpy(error_om, name);
	_strcat(error_om, ": ");
	_strcat(error_om, hist_str_om);
	_strcat(error_om, ": ");
	_strcat(error_om, args[0]);
	_strcat(error_om, ": Permission denied\n");

	free(hist_str_om);
	return (error_om);
}

/**
 * error_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_127(char **args)
{
	char *error_om, *hist_str_om;
	int len;

	hist_str_om = _itoa(hist);
	if (!hist_str_om)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str_om) + _strlen(args[0]) + 16;
	error_om = malloc(sizeof(char) * (len + 1));
	if (!error_om)
	{
		free(hist_str_om);
		return (NULL);
	}

	_strcpy(error_om, name);
	_strcat(error_om, ": ");
	_strcat(error_om, hist_str_om);
	_strcat(error_om, ": ");
	_strcat(error_om, args[0]);
	_strcat(error_om, ": not found\n");

	free(hist_str_om);
	return (error_om);
}
