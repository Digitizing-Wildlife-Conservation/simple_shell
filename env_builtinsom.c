/*
 * File: env_builtinsom.c
 * Auth: Brian Odenyi
 *       Muchai Moses
 */

#include "shell.h"

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int index_om;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index_om = 0; environ[index_om]; index_om++)
	{
		write(STDOUT_FILENO, environ[index_om], _strlen(environ[index_om]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellby_setenv - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var_om = NULL, **new_environment, *new_val_om;
	size_t size;
	int index_om;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_val_om = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_val_om)
		return (create_error(args, -1));
	_strcpy(new_val_om, args[0]);
	_strcat(new_val_om, "=");
	_strcat(new_val_om, args[1]);

	env_var_om = _getenv(args[0]);
	if (env_var_om)
	{
		free(*env_var_om);
		*env_var_om = new_val_om;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environment = malloc(sizeof(char *) * (size + 2));
	if (!new_environment)
	{
		free(new_val_om);
		return (create_error(args, -1));
	}

	for (index_om = 0; environ[index_om]; index_om++)
		new_environment[index_om] = environ[index_om];

	free(environ);
	environ = new_environment;
	environ[index_om] = new_val_om;
	environ[index_om + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var_om, **new_environment;
	size_t size;
	int index_om, index_om2;

	if (!args[0])
		return (create_error(args, -1));
	env_var_om = _getenv(args[0]);
	if (!env_var_om)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environment = malloc(sizeof(char *) * size);
	if (!new_environment)
		return (create_error(args, -1));

	for (index_om = 0, index_om2 = 0; environ[index_om]; index_om++)
	{
		if (*env_var_om == environ[index_om])
		{
			free(*env_var_om);
			continue;
		}
		new_environment[index_om2] = environ[index_om];
		index_om2++;
	}
	free(environ);
	environ = new_environment;
	environ[size - 1] = NULL;

	return (0);
}
