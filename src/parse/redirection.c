#include <fcntl.h>

#include "minishell.h"

static t_cmd	*parse_heredoc(t_cmd *cmd, char *q, char *eq)
{
	t_herecmd	*rcmd;
	char		*line;

	*eq = '\0';
	rcmd = (t_herecmd *)heredoc_command(cmd);
	line = readline("∙ ");
	while (!ft_strncmp(q, line, ft_strlen(q) + 1) == 0)
	{
		ft_strlcat(rcmd->buffer, line, sizeof(rcmd->buffer));
		ft_strlcat(rcmd->buffer, "\n", sizeof(rcmd->buffer));
		free(line);
		line = readline("∙ ");
	}
	free(line);
	return ((t_cmd *)rcmd);
}

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
			cmd = parse_heredoc(cmd, q, eq);
	}
	return (cmd);
}
