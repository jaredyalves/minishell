#include "lexer.h"
#include "nulterminate.h"

t_cmd	*nulterminate(t_cmd *cmd)
{
	if (cmd == 0)
		return (0);
	if (cmd->type == EXEC)
		nulexec((t_execcmd *)cmd);
	else if (cmd->type == REDI)
		nulredi((t_redicmd *)cmd);
	else if (cmd->type == PIPE)
		nulpipe((t_pipecmd *)cmd);
	else if (cmd->type == LIST)
		nullist((t_listcmd *)cmd);
	else if (cmd->type == BACK)
		nulback((t_backcmd *)cmd);
	return (cmd);
}

// vim: ts=4 sts=4 sw=4 noet
