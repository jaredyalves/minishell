#include "libft.h"
#include "minishell.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

static t_cmd	*parse_heredoc(t_cmd *subcmd, char *q, char *eq)
{
	t_redirection	*rcmd;
	char			*word;
	char			*line;

	rcmd = (t_redirection *)redirection(HEREDOC, subcmd, 0, 0);
	word = expand_argument(q, eq);
	line = readline("> ");
	rcmd->buffer = ft_strdup("");
	while (!ft_strncmp(word, line, ft_strlen(word) + 1) == 0)
	{
		rcmd->buffer = ft_strjoin(rcmd->buffer, line);
		rcmd->buffer = ft_strjoin(rcmd->buffer, "\n");
		free(line);
		line = readline("> ");
	}
	free(line);
	free(word);
	return ((t_cmd *)rcmd);
}

t_cmd	*handle_redirection(t_cmd *cmd, int token, char *q, char *eq)
{
	t_redirection	*rcmd;

	if (token == - '<')
		return (parse_heredoc(cmd, q, eq));
	if (token == '<')
		cmd = redirection(REDIRECT, cmd, O_RDONLY, 0);
	if (token == '>')
		cmd = redirection(REDIRECT, cmd, O_WRONLY | O_CREAT | O_TRUNC, 1);
	if (token == - '>')
		cmd = redirection(REDIRECT, cmd, O_WRONLY | O_CREAT | O_APPEND, 1);
	rcmd = (t_redirection *)cmd;
	rcmd->buffer = expand_argument(q, eq);
	return (cmd);
}

t_cmd	*parse_redirection(t_cmd *cmd, char **ps, char *es)
{
	char	*eq;
	char	*q;
	int		token;
	int		next_token;

	while (peek(ps, es, "<>", "<>"))
	{
		if (peek_next(ps, es, TOKENS, TOKENS))
			return (free_command(&cmd));
		token = get_token(ps, es, 0, 0);
		next_token = get_token(ps, es, &q, &eq);
		if (next_token != 'a')
			return (free_command(&cmd));
		cmd = handle_redirection(cmd, token, q, eq);
	}
	return (cmd);
}
