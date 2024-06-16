#include "minishell.h"

#include <unistd.h>
#include <sys/wait.h>

static void	execute_pipe(t_pipeline *pcmd)
{
	int		p[2];
	t_sh	*sh;

	pipe1(p);
	sh = get_sh();
	if (fork1() == 0)
	{
		dup2(p[1], 1);
		close(p[0]);
		close(p[1]);
		execute_command(pcmd->left);
	}
	if (fork() == 0)
	{
		dup2(p[0], 0);
		close(p[0]);
		close(p[1]);
		execute_command(pcmd->right);
	}
	close(p[0]);
	close(p[1]);
	wait(0);
	waitpid(0, &sh->wait_status, 0);
	if (WIFEXITED(sh->wait_status))
		sh_deinit(WEXITSTATUS(sh->wait_status));
}

void	execute_pipeline(t_pipeline *pcmd)
{
	if (pcmd)
	{
		if (pcmd->subtype == PIPE)
			execute_pipe(pcmd);
	}
	sh_deinit(2);
}
