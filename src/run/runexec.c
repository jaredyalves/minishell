#include "ft.h"
#include "lexer.h"
#include <stdio.h>
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

// FIXME: Can't use fprintf(), replace with a ft function
void	runexec(t_execcmd *ecmd, char **envp)
{
	if (ecmd->argv[0] == 0)
		return ;
	if (ecmd->argv[0][0] == '/' || (ecmd->argv[0][0] == '.'
			&& ecmd->argv[0][1] == '/'))
		execve(ecmd->argv[0], ecmd->argv, envp);
	else
		search_in_path(ecmd->argv[0], ecmd->argv, envp);
	fprintf(stderr, "minishell: %s: command not found\n", ecmd->argv[0]);
}

// vim: ts=4 sts=4 sw=4 noet
