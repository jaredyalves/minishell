#include <stdlib.h>

#include "ft.h"
#include "minishell.h"

t_ms	*ms_init(const int argc, const char *argv[], char *envp[])
{
	t_ms	*ms;
	size_t	envp_count;
	size_t	i;

	(void)argc;
	(void)argv;
	ms = ft_calloc(1, sizeof(*ms));
	if (ms == NULL)
		return (NULL);
	envp_count = 0;
	while (envp[envp_count] != NULL)
		envp_count++;
	i = -1;
	while (++i < envp_count)
		ms->env[i] = envp[i];
	ms->env[i] = NULL;
	setup_signal_handlers();
	return (ms);
}
