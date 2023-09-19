#include "shell.h"

int cant_open(char *file_path);
int proc_file_commands(char *file_path, int *exe_ret);

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error_om, *hist_str_om;
	int len_om;

	hist_str_om = _itoa(hist);
	if (!hist_str_om)
		return (127);

	len_om = _strlen(name) + _strlen(hist_str_om) + _strlen(file_path) + 16;
	error_om = malloc(sizeof(char) * (len_om + 1));
	if (!error_om)
	{
		free(hist_str_om);
		return (127);
	}

	_strcpy(error_om, name);
	_strcat(error_om, ": ");
	_strcat(error_om, hist_str_om);
	_strcat(error_om, ": Can't open ");
	_strcat(error_om, file_path);
	_strcat(error_om, "\n");

	free(hist_str_om);
	write(STDERR_FILENO, error_om, len_om);
	free(error_om);
	return (127);
}

/**
 * proc_file_commands - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int proc_file_commands(char *file_path, int *exe_ret)
{
	ssize_t file_om, om_read, i;
	unsigned int line_size_om = 0;
	unsigned int old_size_om = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file_om = open(file_path, O_RDONLY);
	if (file_om == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size_om);
	if (!line)
		return (-1);
	do {
		om_read = read(file_om, buffer, 119);
		if (om_read == 0 && line_size_om == 0)
			return (*exe_ret);
		buffer[om_read] = '\0';
		line_size_om += om_read;
		line = _realloc(line, old_size_om, line_size_om);
		_strcat(line, buffer);
		old_size_om = line_size_om;
	} while (om_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size_om; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size_om && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, line_size_om);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}
