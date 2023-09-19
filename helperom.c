/*
 * File: helperom.c
 * Auth: Brian Odenyi
 *       Moses Muchai
 */

#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void free_args(char **args, char **front)
{
	size_t iom;

	for (iom = 0; args[iom] || args[iom + 1]; iom++)
		free(args[iom]);

	free(front);
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t iom = 0;
	char *buffer;
	ssize_t fileom;

	fileom = open("/proc/self/stat", O_RDONLY);
	if (fileom == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(fileom);
		return (NULL);
	}
	read(fileom, buffer, 120);
	while (buffer[iom] != ' ')
		iom++;
	buffer[iom] = '\0';

	close(fileom);
	return (buffer);
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *beginning, int len)
{
	char **var_addrom;
	char *replacementom = NULL, *temp_om, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addrom = _getenv(var);
	free(var);
	if (var_addrom)
	{
		temp_om = *var_addrom;
		while (*temp_om != '=')
			temp_om++;
		temp_om++;
		replacementom = malloc(_strlen(temp_om) + 1);
		if (replacementom)
			_strcpy(replacementom, temp_om);
	}

	return (replacementom);
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int jom, kom = 0, len;
	char *replacementom = NULL, *old_line_om = NULL, *new_line_om;

	old_line_om = *line;
	for (jom = 0; old_line_om[jom]; jom++)
	{
		if (old_line_om[jom] == '$' && old_line_om[jom + 1] &&
				old_line_om[jom + 1] != ' ')
		{
			if (old_line_om[jom + 1] == '$')
			{
				replacementom = get_pid();
				kom = jom + 2;
			}
			else if (old_line_om[jom + 1] == '?')
			{
				replacementom = _itoa(*exe_ret);
				kom = jom + 2;
			}
			else if (old_line_om[jom + 1])
			{
				/* extract the variable name to search for */
				for (kom = jom + 1; old_line_om[kom] &&
						old_line_om[kom] != '$' &&
						old_line_om[kom] != ' '; kom++)
					;
				len = kom - (jom + 1);
				replacementom = get_env_value(&old_line_om[jom + 1], len);
			}
			new_line_om = malloc(jom + _strlen(replacementom)
					  + _strlen(&old_line_om[kom]) + 1);
			if (!line)
				return;
			new_line_om[0] = '\0';
			_strncat(new_line_om, old_line_om, jom);
			if (replacementom)
			{
				_strcat(new_line_om, replacementom);
				free(replacementom);
				replacementom = NULL;
			}
			_strcat(new_line_om, &old_line_om[kom]);
			free(old_line_om);
			*line = new_line_om;
			old_line_om = new_line_om;
			jom = -1;
		}
	}
}
