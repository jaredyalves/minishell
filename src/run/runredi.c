#include "minishell.h"

int runredi(t_redicmd *rcmd, char **envp)
{
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode, 0664) < 0)
		panic(rcmd->file, (t_cmd *)rcmd);
	return (runcmd(rcmd->cmd, envp));
}
