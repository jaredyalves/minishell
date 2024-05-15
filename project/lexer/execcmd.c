#include "lexer.h"
#include <stdlib.h>
#include <string.h>

// FIXME: Can't use memset(), replace with a ft function
t_cmd	*execcmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

// vim: ts=4 sts=4 sw=4 noet
