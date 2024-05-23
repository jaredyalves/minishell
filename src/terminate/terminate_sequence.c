#include "lexer.h"
#include "parser.h"

void terminate_sequence(t_listcmd *lcmd)
{
	terminate_line(lcmd->left);
	terminate_line(lcmd->right);
}

// vim: ts=4 sts=4 sw=4 noet
