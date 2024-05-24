#include "minishell.h"

t_cmd	*pipe_command(t_cmd *left, t_cmd *right)
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
