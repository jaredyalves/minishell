#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

t_cmd	*backcmd(t_cmd *subcmd)
{
	t_backcmd	*cmd;

	cmd = (t_backcmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
		panic("malloc");
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_BACKGROUND;
	cmd->cmd = subcmd;
	return ((t_cmd *)cmd);
}

// vim: ts=4 sts=4 sw=4 noet
