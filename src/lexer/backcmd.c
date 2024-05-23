#include "ft.h"
#include "lexer.h"
#include <stdlib.h>

// FIXME: Can't use memset(), replace with a ft function
t_cmd	*backcmd(t_cmd *subcmd)
{
	t_backcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_BACKGROUND;
	cmd->cmd = subcmd;
	return ((t_cmd *)cmd);
}

// vim: ts=4 sts=4 sw=4 noet
