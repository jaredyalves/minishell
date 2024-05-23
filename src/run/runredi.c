#include "ft.h"
#include "lexer.h"
#include "run.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	runredi(t_redicmd *rcmd, char **envp)
{
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode, 0664) < 0)
	{
		freecmd((t_cmd *)rcmd);
		ft_dprintf(STDERR_FILENO, "minishell: %s: no file\n", rcmd->file);
		exit(EXIT_FAILURE);
	}
	runcmd(rcmd->cmd, envp);
}

// vim: ts=4 sts=4 sw=4 noet
