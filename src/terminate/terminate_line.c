#include "lexer.h"
#include "parser.h"
#include <stdlib.h>

t_cmd *terminate_line(t_cmd *cmd)
{
	if (cmd == NULL)
		return (NULL);
	if (cmd->type == TYPE_EXECUTE)
		terminate_execute((t_execcmd *)cmd);
	else if (cmd->type == TYPE_REDIRECT)
		terminate_redirect((t_redicmd *)cmd);
	else if (cmd->type == TYPE_PIPE)
		terminate_pipe((t_pipecmd *)cmd);
	else if (cmd->type == TYPE_SEQUENCE)
		terminate_sequence((t_listcmd *)cmd);
	else if (cmd->type == TYPE_BACKGROUND)
		terminate_background((t_backcmd *)cmd);
	return (cmd);
}

// vim: ts=4 sts=4 sw=4 noet