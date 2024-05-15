#include "../lexer/lexer.h"
#include "nulterminate.h"

void	nulpipe(t_pipecmd *pcmd)
{
	nulterminate(pcmd->left);
	nulterminate(pcmd->right);
}

// vim: ts=4 sts=4 sw=4 noet
