#include "minishell.h"

#include <stdlib.h>
#include <sys/wait.h>

static void	execute_sequence(t_list *lcmd)
{
	if (fork1() == 0)
		execute_command(lcmd->left);
	wait(0);
	execute_command(lcmd->right);
}

static void	execute_background(t_list *lcmd)
{
	if (fork1() == 0)
		execute_command(lcmd->left);
	execute_command(lcmd->right);
}

static void	execute_and_if(t_list *lcmd)
{
	int	wait_status;

	if (fork1() == 0)
		execute_command(lcmd->left);
	waitpid(0, &wait_status, 0);
	if (WIFEXITED(wait_status) && WEXITSTATUS(wait_status) == 0)
		execute_command(lcmd->right);
}

static void	execute_or_if(t_list *lcmd)
{
	int	wait_status;

	if (fork1() == 0)
		execute_command(lcmd->left);
	waitpid(0, &wait_status, 0);
	if (WIFEXITED(wait_status) && WEXITSTATUS(wait_status) != 0)
		execute_command(lcmd->right);
}

void	execute_list(t_list *lcmd)
{
	if (lcmd)
	{
		if (lcmd->subtype == SEQUENCE)
			execute_sequence(lcmd);
		if (lcmd->subtype == BACKGROUND)
			execute_background(lcmd);
		if (lcmd->subtype == AND_IF)
			execute_and_if(lcmd);
		if (lcmd->subtype == OR_IF)
			execute_or_if(lcmd);
	}
	sh_deinit(EXIT_SUCCESS);
}
