#include "lexer.h"
#include "nulterminate.h"

void	nullist(t_listcmd *lcmd)
{
	nulterminate(lcmd->left);
	nulterminate(lcmd->right);
}

// vim: ts=4 sts=4 sw=4 noet
