#include "lexer.h"
#include <stdlib.h>
#include <string.h>

// FIXME: Can't use memset(), replace with a ft function
t_cmd	*backcmd(t_cmd *subcmd)
{
	t_backcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = BACK;
	cmd->cmd = subcmd;
	return ((t_cmd *)cmd);
}

// vim: ts=4 sts=4 sw=4 noet
