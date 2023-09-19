/*
 * File: environom.c
 * Auth: Brian Odenyi
 *       Muchai Moses
 */

#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **new_environ_om;
	size_t size;
	int index_om;

	for (size = 0; environ[size]; size++)
		;

	new_environ_om = malloc(sizeof(char *) * (size + 1));
	if (!new_environ_om)
		return (NULL);

	for (index_om = 0; environ[index_om]; index_om++)
	{
		new_environ_om[index_om] = malloc(_strlen(environ[index_om]) + 1);

		if (!new_environ_om[index_om])
		{
			for (index_om--; index_om >= 0; index_om--)
				free(new_environ_om[index_om]);
			free(new_environ_om);
			return (NULL);
		}
		_strcpy(new_environ_om[index_om], environ[index_om]);
	}
	new_environ_om[index_om] = NULL;

	return (new_environ_om);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int indexom;

	for (indexom = 0; environ[indexom]; indexom++)
		free(environ[indexom]);
	free(environ);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenv(const char *var)
{
	int indexom, len_om;

	len_om = _strlen(var);
	for (indexom = 0; environ[indexom]; indexom++)
	{
		if (_strncmp(var, environ[indexom], len_om) == 0)
			return (&environ[indexom]);
	}

	return (NULL);
}
