#include "minishell.h"

int execute_heredoc(t_ms* ms, t_herecmd* cmd)
{
	int p[2];
	char buf[1024];
	char* line;

	ft_bzero(buf, sizeof(buf));
	line = readline("> ");
	while (!ft_strncmp(line, cmd->delim, ft_strlen(cmd->delim)) == 0)
	{
		ft_strlcat(buf, line, sizeof(buf));
		free(line);
		ft_strlcat(buf, "\n", sizeof(buf));
		line = readline("> ");
	}
	free(line);
	if (pipe1(p) == -1)
		return (1);
	if (fork1() == 0)
	{
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		return (execute(ms, cmd->command));
	}
	close(p[0]);
	write(p[1], buf, sizeof(buf));
	close(p[1]);
	wait(0);
	return (0);
}
