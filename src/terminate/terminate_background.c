#include "lexer.h"
#include "parser.h"

void terminate_background(t_backcmd *bcmd)
{
	terminate_line(bcmd->cmd);
}
