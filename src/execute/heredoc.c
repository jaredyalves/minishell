#include "libft.h"
#include "minishell.h"

#include <unistd.h>
#include <sys/wait.h>

int execute_heredoc(t_sh *ms, t_herecmd *cmd)
{
	int p[2];

	if (pipe1(p) == -1)
		return (1);
	if (fork1() == 0)
	{
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
		return (execute_command(ms, cmd->command));
	}
	close(p[0]);
	write(p[1], cmd->buffer, ft_strlen(cmd->buffer));
	close(p[1]);
	wait(0);
	return (0);
}
