#include "lexer.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

// FIXME: Can't use memset(), replace with a ft function
t_cmd	*redicmd(t_cmd *subcmd, char *file, char *efile, int mode)
{
	t_redicmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDI;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	if (mode & O_RDONLY)
		cmd->fd = 0;
	else if (mode & O_WRONLY)
		cmd->fd = 1;
	return ((t_cmd *)cmd);
}

// vim: ts=4 sts=4 sw=4 noet
