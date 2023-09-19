/*
 * File: err_msgsom1.c
 * Auth: Brian Odenyi
 *       Moses Muchai
 */

#include "shell.h"

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
/**
 * error_env - Creates an error message for shellby_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_env(char **args)
{
	char *error, *hist_str_om;
	int len_om;

	hist_str_om = _itoa(hist);
	if (!hist_str_om)
		return (NULL);

	args--;
	len_om = _strlen(name) + _strlen(hist_str_om) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len_om + 1));
	if (!error)
	{
		free(hist_str_om);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str_om);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_str_om);
	return (error);
}

/**
 * error_1 - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1(char **args)
{
	char *error;
	int len_om;

	len_om = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len_om + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error_2_exit - Creates an error message for shellby_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_exit(char **args)
{
	char *errorom, *hist_str_om;
	int len_om;

	hist_str_om = _itoa(hist);
	if (!hist_str_om)
		return (NULL);

	len_om = _strlen(name) + _strlen(hist_str_om) + _strlen(args[0]) + 27;
	errorom = malloc(sizeof(char) * (len_om + 1));
	if (!errorom)
	{
		free(hist_str_om);
		return (NULL);
	}

	_strcpy(errorom, name);
	_strcat(errorom, ": ");
	_strcat(errorom, hist_str_om);
	_strcat(errorom, ": exit: Illegal number: ");
	_strcat(errorom, args[0]);
	_strcat(errorom, "\n");

	free(hist_str_om);
	return (errorom);
}

/**
 * error_2_cd - Creates an error message for shellby_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_cd(char **args)
{
	char *errorom, *hist_str_om;
	int len_om;

	hist_str_om = _itoa(hist);
	if (!hist_str_om)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len_om = _strlen(name) + _strlen(hist_str_om) + _strlen(args[0]) + 24;
	errorom = malloc(sizeof(char) * (len_om + 1));
	if (!errorom)
	{
		free(hist_str_om);
		return (NULL);
	}

	_strcpy(errorom, name);
	_strcat(errorom, ": ");
	_strcat(errorom, hist_str_om);
	if (args[0][0] == '-')
		_strcat(errorom, ": cd: Illegal option ");
	else
		_strcat(errorom, ": cd: can't cd to ");
	_strcat(errorom, args[0]);
	_strcat(errorom, "\n");

	free(hist_str_om);
	return (errorom);
}

/**
 * error_2_syntax - Creates an error message for syntax erroroms.
 * @args: An array of arguments passed to the command.
 *
 * Return: The errorom string.
 */
char *error_2_syntax(char **args)
{
	char *errorom, *hist_str_om;
	int len_om;

	hist_str_om = _itoa(hist);
	if (!hist_str_om)
		return (NULL);

	len_om = _strlen(name) + _strlen(hist_str_om) + _strlen(args[0]) + 33;
	errorom = malloc(sizeof(char) * (len_om + 1));
	if (!errorom)
	{
		free(hist_str_om);
		return (NULL);
	}

	_strcpy(errorom, name);
	_strcat(errorom, ": ");
	_strcat(errorom, hist_str_om);
	_strcat(errorom, ": Syntax errorom: \"");
	_strcat(errorom, args[0]);
	_strcat(errorom, "\" unexpected\n");

	free(hist_str_om);
	return (errorom);
}
