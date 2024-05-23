#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/history.h>
#include <readline/readline.h>

char *get_line(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("> ");
	if (line && *line)
		add_history(line);
	return (line);
}

// FIXME: Can't use fprintf(), replace with a ft function
void	panic(char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(EXIT_FAILURE);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		panic("minishell: fork error");
	return (pid);
}

// vim: ts=4 sts=4 sw=4 noet
