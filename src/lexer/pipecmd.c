#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = (t_pipecmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
		panic("malloc", NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

// vim: ts=4 sts=4 sw=4 noet
