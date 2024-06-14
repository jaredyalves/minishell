#include "minishell.h"

int	execute(t_sh *ms, t_cmd *cmd)
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
		if (cmd->type == TYPE_HEREDOC)
			return (execute_heredoc(ms, (t_herecmd *)cmd));
		if (cmd->type == TYPE_BACKGROUND)
			return (execute_background(ms, (t_backcmd *)cmd));
		if (cmd->type == TYPE_LOGICAL)
			return (execute_logical(ms, (t_logicmd *)cmd));
	}
	return (1);
}
