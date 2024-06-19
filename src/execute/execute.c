#include "minishell.h"

void	execute_execute(t_execute *ecmd)
{
	if (ecmd)
	{
		if (is_builtin(ecmd))
			execute_builtin(ecmd);
		execute_external(ecmd);
	}
	sh_deinit(2);
}
