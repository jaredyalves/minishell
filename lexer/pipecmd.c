#include "lexer.h"
#include <stdlib.h>
#include <string.h>

// FIXME: Can't use memset(), replace with a ft function
t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

// vim: ts=4 sts=4 sw=4 noet
