#include "minishell.h"

#include <stdlib.h>

void	execute_command(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->type == EXECUTE)
			execute_execute((t_execute *)cmd);
		if (cmd->type == REDIRECTION)
			execute_redirection((t_redirection *)cmd);
		if (cmd->type == LIST)
			execute_list((t_list *)cmd);
		if (cmd->type == PIPELINE)
			execute_pipeline((t_pipeline *)cmd);
	}
	sh_deinit(EXIT_SUCCESS);
}
