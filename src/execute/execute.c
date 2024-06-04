#include "minishell.h"

int	execute(t_ms *ms, t_cmd *cmd)
{
	if (ms && cmd)
	{
		if (cmd->type == TYPE_EXECUTE)
		{
			if (is_builtin(ms, (t_execcmd *)cmd))
				return (execute_builtin(ms, (t_execcmd *)cmd));
			return (execute_external(ms, (t_execcmd *)cmd));
		}
		if (cmd->type == TYPE_REDIRECT)
			return (execute_redirect(ms, (t_redicmd *)cmd));
		if (cmd->type == TYPE_BACKGROUND)
			return (execute_background(ms, (t_backcmd *)cmd));
		if (cmd->type == TYPE_LOGICAL)
		{
			if (((t_logicmd *)cmd)->sub == TYPE_PIPE)
				return (execute_pipe(ms, (t_logicmd *)cmd));
			if (((t_logicmd *)cmd)->sub == TYPE_SEQUENCE)
				return (execute_sequence(ms, (t_logicmd *)cmd));
			if (((t_logicmd *)cmd)->sub == TYPE_AND)
				return (execute_andif(ms, (t_logicmd *)cmd));
			if (((t_logicmd *)cmd)->sub == TYPE_OR)
				return (execute_orif(ms, (t_logicmd *)cmd));
		}
	}
	return (1);
}
