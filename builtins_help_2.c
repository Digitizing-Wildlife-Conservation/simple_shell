#include "shell.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 * help_env - Displays information on the shellby builtin command 'env'.
 */
void help_env(void)
{
	char *msg_om = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg_om, _strlen(msg_om));
}

/**
 * help_setenv - Displays information on the shellby builtin command 'setenv'.
 */
void help_setenv(void)
{
	char *msg_om = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg_om, _strlen(msg_om));
	msg_om = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg_om, _strlen(msg_om));
	msg_om = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg_om, _strlen(msg_om));
}

/**
 * help_unsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void help_unsetenv(void)
{
	char *msg_om = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg_om, _strlen(msg_om));
	msg_om = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg_om, _strlen(msg_om));
	msg_om = "message to stderr.\n";
	write(STDOUT_FILENO, msg_om, _strlen(msg_om));
}
