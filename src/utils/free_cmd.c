#include <stdlib.h>

#include "minishell.h"

static void	free_redirect(t_redicmd *cmd)
{
	if (cmd)
	{
		free_cmd(&cmd->command);
		free(cmd);
	}
}

static void	free_heredoc(t_herecmd *cmd)
{
	if (cmd)
	{
		free_cmd(&cmd->command);
		free(cmd);
	}
}

static void	free_background(t_backcmd *cmd)
{
	if (cmd)
	{
		free_cmd(&cmd->command);
		free(cmd);
	}
}

static void	free_logical(t_logicmd *cmd)
{
	if (cmd)
	{
		free_cmd(&cmd->left);
		free_cmd(&cmd->right);
		free(cmd);
	}
}

void	free_cmd(t_cmd **cmd)
{
	if (cmd && *cmd)
	{
		if ((*cmd)->type == TYPE_EXECUTE)
			free((t_execcmd *)*cmd);
		else if ((*cmd)->type == TYPE_REDIRECT)
			free_redirect((t_redicmd *)*cmd);
		else if ((*cmd)->type == TYPE_HEREDOC)
			free_heredoc((t_herecmd *)*cmd);
		else if ((*cmd)->type == TYPE_BACKGROUND)
			free_background((t_backcmd *)*cmd);
		else if ((*cmd)->type == TYPE_LOGICAL)
			free_logical((t_logicmd *)*cmd);
		*cmd = NULL;
	}
}
