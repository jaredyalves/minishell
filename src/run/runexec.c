#include "ft.h"
#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// FIXME: Can't use strcpy(), replace with a ft function
// FIXME: Can't use strcat(), replace with a ft function
void	search_in_path(char *program, char **argv, char **envp)
{
	int		i;
	char	*path;
	char	**tokens;
	char	executable[1024];

	i = 0;
	path = getenv("PATH");
	tokens = ft_split(path, ':');
	while (tokens[i] != 0)
	{
		strcpy(executable, tokens[i]);
		strcat(executable, "/");
		strcat(executable, program);
		if (access(executable, X_OK) == 0)
			execve(executable, argv, envp);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int runexec(t_execcmd *ecmd, char **envp)
{
	char *program;

	program = ecmd->argv[0];
	if (program == NULL)
		return (0);
	if (ft_strchr(program, '/'))
		execve(program, ecmd->argv, envp);
	else
		search_in_path(program, ecmd->argv, envp);
	ft_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", program);
	return (-1);
}

// vim: ts=4 sts=4 sw=4 noet
