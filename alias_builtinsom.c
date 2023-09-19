/*
 * File: builtin.c
 * Auth: Brian Odenyi
 *       Muchai Moses
 */

#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *tempom = aliases;
	int iom, retom = 0;
	char *value;

	if (!args[0])
	{
		while (tempom)
		{
			print_alias(tempom);
			tempom = tempom->next;
		}
		return (retom);
	}
	for (iom = 0; args[iom]; iom++)
	{
		tempom = aliases;
		value = _strchr(args[iom], '=');
		if (!value)
		{
			while (tempom)
			{
				if (_strcmp(args[iom], tempom->name) == 0)
				{
					print_alias(tempom);
					break;
				}
				tempom = tempom->next;
			}
			if (!tempom)
				retom = create_error(args + iom, 1);
		}
		else
			set_alias(args[iom], value);
	}
	return (retom);
}

/**
 * set_alias - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @var_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void set_alias(char *var_name, char *value)
{
	alias_t *tempom = aliases;
	int len, jom, kom;
	char *new_valom;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_valom = malloc(sizeof(char) * (len + 1));
	if (!new_valom)
		return;
	for (jom = 0, kom = 0; value[jom]; jom++)
	{
		if (value[jom] != '\'' && value[jom] != '"')
			new_valom[kom++] = value[jom];
	}
	new_valom[kom] = '\0';
	while (tempom)
	{
		if (_strcmp(var_name, tempom->name) == 0)
		{
			free(tempom->value);
			tempom->value = new_valom;
			break;
		}
		tempom = tempom->next;
	}
	if (!tempom)
		add_alias_end(&aliases, var_name, new_valom);
}

/**
 * print_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_stringom;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_stringom = malloc(sizeof(char) * (len + 1));
	if (!alias_stringom)
		return;
	_strcpy(alias_stringom, alias->name);
	_strcat(alias_stringom, "='");
	_strcat(alias_stringom, alias->value);
	_strcat(alias_stringom, "'\n");

	write(STDOUT_FILENO, alias_stringom, len);
	free(alias_stringom);
}
/**
 * replace_aliases - Goes through the arguments and replace any matching alias
 * with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *tempom;
	int iom;
	char *new_valom;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (iom = 0; args[iom]; iom++)
	{
		tempom = aliases;
		while (tempom)
		{
			if (_strcmp(args[iom], tempom->name) == 0)
			{
				new_valom = malloc(sizeof(char) * (_strlen(tempom->value) + 1));
				if (!new_valom)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_valom, tempom->value);
				free(args[iom]);
				args[iom] = new_valom;
				iom--;
				break;
			}
			tempom = tempom->next;
		}
	}

	return (args);
}

