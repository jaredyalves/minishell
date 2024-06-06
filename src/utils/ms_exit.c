#include "minishell.h"

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
