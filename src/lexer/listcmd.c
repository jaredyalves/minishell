#include "ft.h"
#include "lexer.h"
#include <stdlib.h>

t_cmd	*listcmd(t_cmd *left, t_cmd *right)
{
	t_listcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_SEQUENCE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

// vim: ts=4 sts=4 sw=4 noet
