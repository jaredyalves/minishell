#include "minishell.h"

t_ms	*ms_init(const int argc, const char *argv[], char *envp[])
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
