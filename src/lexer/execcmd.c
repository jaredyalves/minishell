#include "ft.h"
#include "lexer.h"
#include <stdlib.h>

t_cmd	*execcmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_EXECUTE;
	return ((t_cmd *)cmd);
}

// vim: ts=4 sts=4 sw=4 noet
