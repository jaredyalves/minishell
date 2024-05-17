#include "../lexer/lexer.h"
#include "run.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// FIXME: Can't use fprintf(), replace with a ft function
void	runredi(t_redicmd *rcmd)
{
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode, 0664) < 0)
	{
		fprintf(stderr, "minishell: %s: no such file\n", rcmd->file);
		freecmd((t_cmd *)rcmd);
		exit(EXIT_FAILURE);
	}
	runcmd(rcmd->cmd);
}

// vim: ts=4 sts=4 sw=4 noet
