#include "ft.h"
#include "lexer.h"
#include "minishell.h"
#include <stdlib.h>

t_cmd	*execcmd(void)
{
	t_execcmd	*cmd;

	cmd = (t_execcmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
		panic("malloc", NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_EXECUTE;
	cmd->argc = 0;
	return ((t_cmd *)cmd);
}

// vim: ts=4 sts=4 sw=4 noet
