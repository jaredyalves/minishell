#include "minishell.h"

void	free_execute(t_execcmd *execute_command)
{
	free(execute_command);
}

void	free_redirect(t_redicmd *redirect_command)
{
	free_command(&(redirect_command->command));
	free(redirect_command);
}

void	free_background(t_backcmd *background_command)
{
	free_command(&(background_command->command));
	free(background_command);
}

void	free_logical(t_logicmd *logical_command)
{
	free_command(&(logical_command->left));
	free_command(&(logical_command->right));
	free(logical_command);
}

void	free_command(t_cmd **p_command)
{
	if (!p_command || !*p_command)
		return ;
	if ((*p_command)->type == TYPE_EXECUTE)
		free_execute((t_execcmd *)(*p_command));
	else if ((*p_command)->type == TYPE_REDIRECT)
		free_redirect((t_redicmd *)(*p_command));
	else if ((*p_command)->type == TYPE_BACKGROUND)
		free_background((t_backcmd *)(*p_command));
	else if ((*p_command)->type == TYPE_LOGICAL)
		free_logical((t_logicmd *)(*p_command));
	*p_command = NULL;
}
