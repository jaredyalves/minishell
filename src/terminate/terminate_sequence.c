#include "minishell.h"

void terminate_sequence(t_listcmd *lcmd)
{
	terminate_line(lcmd->left);
	terminate_line(lcmd->right);
}
