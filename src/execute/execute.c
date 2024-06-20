#include "minishell.h"

#include <sys/wait.h>

void	execute_execute(t_execute *ecmd)
{
	if (ecmd)
	{
		if (is_builtin(ecmd))
		{
			if (get_sh()->subshell == 0)
				execute_builtin(ecmd);
			else if (fork1() == 0)
				execute_builtin(ecmd);
		}
		else
		{
			if (fork1() == 0)
				execute_external(ecmd);
			if (get_sh()->subshell == 0)
				wait(0);
		}
	}
}
