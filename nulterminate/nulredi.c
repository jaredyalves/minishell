#include "../lexer/lexer.h"
#include "nulterminate.h"

void	nulredi(t_redicmd *rcmd)
{
	nulterminate(rcmd->cmd);
	*rcmd->efile = 0;
}

// vim: ts=4 sts=4 sw=4 noet
