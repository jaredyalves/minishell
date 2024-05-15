#include "lexer.h"
#include <stdlib.h>
#include <string.h>

// FIXME: Can't use memset(), replace with a ft function
t_cmd	*listcmd(t_cmd *left, t_cmd *right)
{
	t_listcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = LIST;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

// vim: ts=4 sts=4 sw=4 noet
