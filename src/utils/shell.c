#include "minishell.h"

t_shell	*get_shell(void)
{
	static t_shell	*shell = NULL;

	if (shell == NULL)
	{
		shell = (t_shell *)malloc(sizeof(*shell));
		if (shell == NULL)
		{
			perror("minishell: malloc");
			exit(1);
		}
		ft_memset(shell, 0, sizeof(*shell));
	}
	return (shell);
}

void	init_shell(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	**ptr;

	(void)argc;
	(void)argv;
	shell = get_shell();
	ptr = shell->environ;
	while (*envp != NULL)
		*ptr++ = *envp++;
	*ptr = NULL;
}

int	cleanup_shell(void)
{
	t_shell	*shell;
	int		exit_status;

	rl_clear_history();
	shell = get_shell();
	exit_status = shell->exit_status;
	if (shell->cmdline)
		free_line(&shell->cmdline);
	if (shell->command)
		free_command(&shell->command);
	free(shell);
	shell = NULL;
	return (exit_status);
}
