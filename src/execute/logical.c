#include "minishell.h"

int	execute_logical(t_ms *ms, t_logicmd *cmd)
{
	if (ms && cmd)
	{
		if (cmd->sub == TYPE_PIPE)
			return (execute_pipe(ms, cmd));
		if (cmd->sub == TYPE_SEQUENCE)
			return (execute_sequence(ms, cmd));
		if (cmd->sub == TYPE_AND)
			return (execute_andif(ms, cmd));
		if (cmd->sub == TYPE_OR)
			return (execute_orif(ms, cmd));
	}
	return (1);
}

int	execute_pipe(t_ms *ms, t_logicmd *cmd)
{
	int	p[2];

	if (pipe1(p) == -1)
		return (1);
	if (fork1() == 0)
	{
		dup2(p[1], 1);
		close(p[0]);
		close(p[1]);
		return (execute(ms, cmd->left));
	}
	if (fork() == 0)
	{
		dup2(p[0], 0);
		close(p[0]);
		close(p[1]);
		return (execute(ms, cmd->right));
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	wait(0);
	return (-1);
}

int	execute_sequence(t_ms *ms, t_logicmd *cmd)
{
	if (fork1() == 0)
		return (execute(ms, cmd->left));
	wait(0);
	return (execute(ms, cmd->right));
}

int	execute_andif(t_ms *ms, t_logicmd *cmd)
{
	int	status;

	if (fork1() == 0)
		return (execute(ms, cmd->left));
	waitpid(0, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		return (execute(ms, cmd->right));
	return (0);
}

int	execute_orif(t_ms *ms, t_logicmd *cmd)
{
	int	status;

	if (fork1() == 0)
		return (execute(ms, cmd->left));
	waitpid(0, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (execute(ms, cmd->right));
	return (0);
}
