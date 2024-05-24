#include "minishell.h"

t_cmd	*listcmd(t_cmd *left, t_cmd *right)
{
	t_listcmd	*cmd;

	cmd = (t_listcmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
		panic("malloc", NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_SEQUENCE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
