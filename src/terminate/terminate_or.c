#include "lexer.h"
#include "parser.h"

void terminate_or(t_orcmd *ocmd)
{
	terminate_line(ocmd->left);
	terminate_line(ocmd->right);
}

// vim: ts=4 sts=4 sw=4 noet
