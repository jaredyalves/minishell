#include "../lexer/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// FIXME: Can't use strcpy(), replace with a ft function
// FIXME: Can't use strcat(), replace with a ft function
// FIXME: Can't use strtok(), replace with a ft function
void	search_in_path(char *program, char **argv, char **envp)
{
	char	*path;
	char	*token;
	char	executable[1024];

	path = getenv("PATH");
	token = strtok(path, ":");
	while (token)
	{
		strcpy(executable, token);
		strcat(executable, "/");
		strcat(executable, program);
		if (access(executable, X_OK) == 0)
			execve(executable, argv, envp);
		token = strtok(0, ":");
	}
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
