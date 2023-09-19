/*
 * File: helpersom_2.c
 * Auth: Brian Odenyi
 *       Muchai Moses
 */

#include "shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **line, ssize_t read)
{
	char *old_line_om, *new_line_om;
	char previous_om, current_om, next;
	size_t i, jom;
	ssize_t new_len_om;

	new_len_om = get_new_len(*line);
	if (new_len_om == read - 1)
		return;
	new_line_om = malloc(new_len_om + 1);
	if (!new_line_om)
		return;
	jom = 0;
	old_line_om = *line;
	for (i = 0; old_line_om[i]; i++)
	{
		current_om = old_line_om[i];
		next = old_line_om[i + 1];
		if (i != 0)
		{
			previous_om = old_line_om[i - 1];
			if (current_om == ';')
			{
				if (next == ';' && previous_om != ' ' && previous_om != ';')
				{
					new_line_om[jom++] = ' ';
					new_line_om[jom++] = ';';
					continue;
				}
				else if (previous_om == ';' && next != ' ')
				{
					new_line_om[jom++] = ';';
					new_line_om[jom++] = ' ';
					continue;
				}
				if (previous_om != ' ')
					new_line_om[jom++] = ' ';
				new_line_om[jom++] = ';';
				if (next != ' ')
					new_line_om[jom++] = ' ';
				continue;
			}
			else if (current_om == '&')
			{
				if (next == '&' && previous_om != ' ')
					new_line_om[jom++] = ' ';
				else if (previous_om == '&' && next != ' ')
				{
					new_line_om[jom++] = '&';
					new_line_om[jom++] = ' ';
					continue;
				}
			}
			else if (current_om == '|')
			{
				if (next == '|' && previous_om != ' ')
					new_line_om[jom++]  = ' ';
				else if (previous_om == '|' && next != ' ')
				{
					new_line_om[jom++] = '|';
					new_line_om[jom++] = ' ';
					continue;
				}
			}
		}
		else if (current_om == ';')
		{
			if (i != 0 && old_line_om[i - 1] != ' ')
				new_line_om[jom++] = ' ';
			new_line_om[jom++] = ';';
			if (next != ' ' && next != ';')
				new_line_om[jom++] = ' ';
			continue;
		}
		new_line_om[jom++] = old_line_om[i];
	}
	new_line_om[jom] = '\0';

	free(*line);
	*line = new_line_om;
}

/**
 * get_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t new_len_om = 0;
	char current_om, next_om;

	for (i = 0; line[i]; i++)
	{
		current_om = line[i];
		next_om = line[i + 1];
		if (current_om == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current_om == ';')
			{
				if (next_om == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_len_om += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next_om != ' ')
				{
					new_len_om += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_len_om++;
				if (next_om != ' ')
					new_len_om++;
			}
			else
				logical_ops(&line[i], &new_len_om);
		}
		else if (current_om == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_len_om++;
			if (next_om != ' ' && next_om != ';')
				new_len_om++;
		}
		new_len_om++;
	}
	return (new_len_om);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char previous_om, current_om, next_om;

	previous_om = *(line - 1);
	current_om = *line;
	next_om = *(line + 1);

	if (current_om == '&')
	{
		if (next_om == '&' && previous_om != ' ')
			(*new_len)++;
		else if (previous_om == '&' && next_om != ' ')
			(*new_len)++;
	}
	else if (current_om == '|')
	{
		if (next_om == '|' && previous_om != ' ')
			(*new_len)++;
		else if (previous_om == '|' && next_om != ' ')
			(*new_len)++;
	}
}
