#include "minishell.h"

t_cmd *or_command(t_cmd *left, t_cmd *right)
{
	t_orcmd *cmd;

	cmd = (t_orcmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
		panic("malloc", NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_OR;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
