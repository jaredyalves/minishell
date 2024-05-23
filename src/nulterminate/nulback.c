#include "lexer.h"
#include "nulterminate.h"

void	nulback(t_backcmd *bcmd)
{
	nulterminate(bcmd->cmd);
}

// vim: ts=4 sts=4 sw=4 noet
