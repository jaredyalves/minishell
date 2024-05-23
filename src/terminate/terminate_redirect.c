#include "lexer.h"
#include "parser.h"

void terminate_redirect(t_redicmd *rcmd)
{
	terminate_line(rcmd->cmd);
	*rcmd->efile = 0;
}

// vim: ts=4 sts=4 sw=4 noet
