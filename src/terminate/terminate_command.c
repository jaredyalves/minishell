#include "minishell.h"

void	terminate_command(t_cmd *command)
{
	if (command->type == TYPE_EXECUTE)
		terminate_execute((t_execcmd *)command);
	else if (command->type == TYPE_REDIRECT)
		terminate_redirect((t_redicmd *)command);
	else if (command->type == TYPE_PIPE)
		terminate_pipe((t_pipecmd *)command);
	else if (command->type == TYPE_SEQUENCE)
		terminate_sequence((t_listcmd *)command);
	else if (command->type == TYPE_BACKGROUND)
		terminate_background((t_backcmd *)command);
	else if (command->type == TYPE_AND)
		terminate_and((t_andcmd *)command);
	else if (command->type == TYPE_OR)
		terminate_or((t_orcmd *)command);
}

void	terminate_execute(t_execcmd *e_command)
{
	int	i;

	i = 0;
	while (i < e_command->argc)
		*e_command->eargv[i++] = '\0';
}

void	terminate_redirect(t_redicmd *r_command)
{
	terminate_command(r_command->cmd);
	*r_command->efile = 0;
}

void	terminate_pipe(t_pipecmd *p_command)
{
	terminate_command(p_command->left);
	terminate_command(p_command->right);
}

void	terminate_sequence(t_listcmd *s_command)
{
	terminate_command(s_command->left);
	terminate_command(s_command->right);
}
