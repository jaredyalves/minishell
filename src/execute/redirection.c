#include "libft.h"
#include "minishell.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

static void	execute_heredoc(t_redirection *rcmd)
{
	int		p[2];
	t_sh	*sh;

	pipe1(p);
	sh = get_sh();
	if (fork1() == 0)
	{
		dup2(p[0], 0);
		close(p[0]);
		close(p[1]);
		execute_command(rcmd->cmd);
	}
	close(p[0]);
	ft_putstr_fd(rcmd->buffer, p[1]);
	close(p[1]);
	waitpid(0, &sh->wait_status, 0);
	if (WIFEXITED(sh->wait_status))
		sh_deinit(WEXITSTATUS(sh->wait_status));
}

static void	execute_redirect(t_redirection *rcmd)
{
	close(rcmd->fd);
	if (open(rcmd->buffer, rcmd->mode, 0664) < 0)
		panic(rcmd->buffer);
	execute_command(rcmd->cmd);
}

void	execute_redirection(t_redirection *rcmd)
{
	if (rcmd)
	{
		if (rcmd->subtype == REDIRECT)
			execute_redirect(rcmd);
		if (rcmd->subtype == HEREDOC)
			execute_heredoc(rcmd);
	}
	sh_deinit(2);
}
