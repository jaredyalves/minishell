#include "lexer.h"
#include "minishell.h"
#include "run.h"
#include <fcntl.h>
#include <unistd.h>

int runredi(t_redicmd *rcmd, char **envp)
{
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode, 0664) < 0)
		panic(rcmd->file, (t_cmd *)rcmd);
	return (runcmd(rcmd->cmd, envp));
}

// vim: ts=4 sts=4 sw=4 noet
