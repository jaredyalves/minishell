#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms	*ms;

	ms = ms_init(argc, argv, envp);
	while (ms->exit == 0)
		ms_run(ms);
	ms_exit(ms);
}
