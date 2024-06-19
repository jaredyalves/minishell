#include "minishell.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

static void	heredoc_eof(char *word)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file ", STDERR_FILENO);
	ft_putstr_fd("(wanted `", STDERR_FILENO);
	ft_putstr_fd(word, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static t_cmd	*parse_heredoc(t_cmd *subcmd, char *q, char *eq)
{
	t_redirection	*rcmd;
	char			*word;
	char			*line;
	char			*line_expanded;

	rcmd = (t_redirection *)redirection(HEREDOC, subcmd, 0, 0);
	word = expand_argument(q, eq);
	while (1)
	{
		line = readline("> ");
		line_expanded = expand_argument(line, line + ft_strlen(line));
		free(line);
		if (!line_expanded)
		{
			heredoc_eof(word);
			break ;
		}
		if (ft_strncmp(word, line_expanded, ft_strlen(word) + 1) == 0)
			break ;
		rcmd->buffer = concat_strings(rcmd->buffer, line_expanded);
		rcmd->buffer = ft_strjoin(rcmd->buffer, "\n");
	}
	free(line_expanded);
	return (free(word), (t_cmd *)rcmd);
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
