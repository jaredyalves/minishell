#include "minishell.h"

static void	terminate_execute(const t_execcmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->argc)
		*cmd->end_argv[i] = '\0';
}

void	terminate(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->type == TYPE_EXECUTE)
			terminate_execute((t_execcmd *)cmd);
		else if (cmd->type == TYPE_REDIRECT)
		{
			terminate(((t_redicmd *)cmd)->command);
			*((t_redicmd *)cmd)->end_file = '\0';
		}
		else if (cmd->type == TYPE_HEREDOC)
		{
			terminate(((t_herecmd *)cmd)->command);
			*((t_herecmd *)cmd)->end_delim = '\0';
		}
		else if (cmd->type == TYPE_BACKGROUND)
			terminate(((t_backcmd *)cmd)->command);
		else if (cmd->type == TYPE_LOGICAL)
		{
			terminate(((t_logicmd *)cmd)->left);
			terminate(((t_logicmd *)cmd)->right);
		}
	}
}
