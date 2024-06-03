#include "minishell.h"

void	null_terminate_execute(t_execcmd *execute_command)
{
	int	i;

	i = 0;
	while (i < execute_command->argc)
	{
		*(execute_command->end_argv[i]) = '\0';
		i++;
	}
}

void	null_terminate_redirect(t_redicmd *redirect_command)
{
	null_terminate(redirect_command->command);
	*(redirect_command->end_file) = '\0';
}

void	null_terminate_logical(t_logicmd *logical_command)
{
	null_terminate(logical_command->left);
	null_terminate(logical_command->right);
}

void	null_terminate(t_cmd *command)
{
	if (!command)
		return ;
	if (command->type == TYPE_EXECUTE)
		null_terminate_execute((t_execcmd *)command);
	else if (command->type == TYPE_REDIRECT)
		null_terminate_redirect((t_redicmd *)command);
	else if (command->type == TYPE_BACKGROUND)
		null_terminate(((t_backcmd *)command)->command);
	else if (command->type == TYPE_LOGICAL)
		null_terminate_logical((t_logicmd *)command);
}
