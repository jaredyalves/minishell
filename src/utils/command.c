#include "minishell.h"
#include <stdlib.h>

static void	free_execute(t_execute *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
		free(cmd->argv[i++]);
	free(cmd);
}

static void	free_redirection(t_redirection *cmd)
{
	free_command(&cmd->cmd);
	free(cmd->buffer);
	free(cmd);
}

static void	free_list(t_list *cmd)
{
	free_command(&cmd->left);
	free_command(&cmd->right);
	free(cmd);
}

static void	free_pipeline(t_pipeline *cmd)
{
	free_command(&cmd->left);
	free_command(&cmd->right);
	free(cmd);
}

t_cmd	*free_command(t_cmd **cmd)
{
	if (cmd && *cmd)
	{
		if ((*cmd)->type == EXECUTE)
			free_execute((t_execute *)*cmd);
		else if ((*cmd)->type == REDIRECTION)
			free_redirection((t_redirection *)*cmd);
		else if ((*cmd)->type == LIST)
			free_list((t_list *)*cmd);
		else if ((*cmd)->type == PIPELINE)
			free_pipeline((t_pipeline *)*cmd);
		*cmd = 0;
	}
	return (0);
}
