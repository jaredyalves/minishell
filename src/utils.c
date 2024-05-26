#include "minishell.h"

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
		free_command(cmd);
	exit(EXIT_FAILURE);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: fork: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int pipe1(int *pipes)
{
	int status;

	status = pipe(pipes);
	if (status == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: pipe: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (status);
}
