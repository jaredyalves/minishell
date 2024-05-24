#include "minishell.h"

t_cmd *and_command(t_cmd *left, t_cmd *right)
{
	t_andcmd *cmd;

	cmd = (t_andcmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
		panic("malloc", NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_AND;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
