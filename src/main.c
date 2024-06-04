#include "minishell.h"

int	main(const int argc, const char **argv, char **envp)
{
	t_ms	*ms;

	ms = ms_init(argc, argv, envp);
	while (1)
	{
		ms->str = get_str(ms->str);
		if (ms->str == NULL)
			break ;
		ms->cmd = parse(ms->str);
		if (ms->cmd && fork1() == 0)
		{
			ms->exit_status = execute(ms, ms->cmd);
			exit(ms_exit(&ms));
		}
		waitpid(0, &ms->wait_status, 0);
		free_cmd(&ms->cmd);
		free_str(&ms->str);
	}
	exit(ms_exit(&ms));
}
