#include <fcntl.h>

#include "minishell.h"

t_cmd	*parse_redirection(t_cmd *cmd, char **ps, const char *es)
{
	char	*eq;
	char	*q;
	int		token;

	while (peek(ps, es, "<>", "<>"))
	{
		token = get_token(ps, es, NULL, NULL);
		if (get_token(ps, es, &q, &eq) != 'a')
			return (free_cmd(&cmd), NULL);
		if (token == - '>')
			cmd = redirect_command(cmd, q, eq, O_WRONLY | O_CREAT | O_APPEND);
		else if (token == '>')
			cmd = redirect_command(cmd, q, eq, O_WRONLY | O_CREAT | O_TRUNC);
		else if (token == '<')
			cmd = redirect_command(cmd, q, eq, O_RDONLY);
		else if (token == - '<')
			cmd = heredoc_command(cmd, q, eq);
	}
	return (cmd);
}
