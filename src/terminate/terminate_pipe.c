#include "lexer.h"
#include "parser.h"

void terminate_pipe(t_pipecmd *pcmd)
{
	terminate_line(pcmd->left);
	terminate_line(pcmd->right);
}

// vim: ts=4 sts=4 sw=4 noet
