#include "lexer.h"
#include "parser.h"

void terminate_background(t_backcmd *bcmd)
{
	terminate_line(bcmd->cmd);
}

// vim: ts=4 sts=4 sw=4 noet
