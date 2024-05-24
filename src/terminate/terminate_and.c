#include "lexer.h"
#include "parser.h"

void terminate_and(t_andcmd *acmd)
{
	terminate_line(acmd->left);
	terminate_line(acmd->right);
}

// vim: ts=4 sts=4 sw=4 noet
