#include "ft.h"
#include "lexer.h"
#include "run.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

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

void panic(char *str, t_cmd *cmd)
{
	if (str != NULL && errno != 0)
		ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", str, strerror(errno));
	else if (str != NULL && errno == 0)
		ft_dprintf(STDERR_FILENO, "minishell: %s\n", str);
	else if (str == NULL && errno != 0)
		ft_dprintf(STDERR_FILENO, "minishell: %s\n", strerror(errno));
	else
		ft_dprintf(STDERR_FILENO, "minishell: unexpected error\n");
	if (cmd != NULL)
		freecmd(cmd);
	exit(EXIT_FAILURE);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		panic("fork", NULL);
	return (pid);
}

// vim: ts=4 sts=4 sw=4 noet
