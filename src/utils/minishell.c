#include "minishell.h"

t_ms	*ms_init(const int argc, const char **argv, char **envp)
{
	t_ms	*ms;
	char	**p;

	(void)argc;
	(void)argv;
	ms = (t_ms *)malloc(sizeof(*ms));
	ft_memset(ms, 0, sizeof(*ms));
	p = ms->env;
	while (*envp)
		*p++ = *envp++;
	setup_signal_handlers();
	return (ms);
}

int	ms_exit(t_ms **ms)
{
	const int	status = (*ms)->exit_status;

	if ((*ms)->str)
		free_str(&(*ms)->str);
	if ((*ms)->cmd)
		free_cmd(&(*ms)->cmd);
	free(*ms);
	*ms = NULL;
	rl_clear_history();
	return (status);
}
