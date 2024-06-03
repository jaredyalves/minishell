#include "minishell.h"

int	execute(t_cmd *command)
{
	if (command == NULL)
		return (1);
	if (command->type == TYPE_EXECUTE)
	{
		if (is_builtin((t_execcmd *)command))
			return (execute_builtin((t_execcmd *)command));
		return (execute_external((t_execcmd *)command));
	}
	if (command->type == TYPE_REDIRECT)
		return (runredi((t_redicmd *)command));
	if (command->type == TYPE_BACKGROUND)
		return (runback((t_backcmd *)command));
	if (command->type == TYPE_LOGICAL)
	{
		if (((t_logicmd *)command)->sub_type == TYPE_PIPE)
			return (runpipe((t_logicmd *)command));
		if (((t_logicmd *)command)->sub_type == TYPE_SEQUENCE)
			return (runlist((t_logicmd *)command));
		if (((t_logicmd *)command)->sub_type == TYPE_AND)
			return (runand((t_logicmd *)command));
		if (((t_logicmd *)command)->sub_type == TYPE_OR)
			return (runor((t_logicmd *)command));
	}
	return (1);
}
