#include "minishell.h"

void terminate_sequence(t_listcmd *lcmd)
{
	terminate_command(lcmd->left);
	terminate_command(lcmd->right);
}
