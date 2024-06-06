#include "minishell.h"

static void	skip_whitespace(char **ps, const char *es)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(" \t", *s))
		s++;
	*ps = s;
}

static char	*parse_quote(char **ps, const char *es)
{
	char	*s;
	char	quote;

	s = *ps;
	quote = *s;
	s++;
	while (s < es && *s != quote)
	{
		if (quote == '\"' && *s == '\\' && s + 1 < es)
			s++;
		s++;
	}
	if (s < es && *s == quote)
		s++;
	return (s);
}

static t_token	parse_token(char **ps, const char *es)
{
	const char	*tokens[] = {"(", ")", "&&", "&", ">>", ">", "<<", "<", "||",
		"|", ";"};
	char		*s;
	size_t		i;
	size_t		token_len;

	i = 0;
	s = *ps;
	if (*s == '"' || *s == '\'')
		return (*ps = parse_quote(&s, es), TOKEN_QUOTE);
	while (i < (sizeof(tokens) / sizeof(char *)))
	{
		token_len = ft_strlen(tokens[i]);
		if (s + token_len <= es && ft_strncmp(s, tokens[i], token_len) == 0)
			return (*ps = s + token_len, i);
		i++;
	}
	if (s < es && !ft_strchr(" \t", *s))
	{
		while (s < es && !ft_strchr(" \t", *s) && !ft_strchr("()&><|;\"'", *s))
			s++;
		return (*ps = s, TOKEN_WORD);
	}
	return (TOKEN_NULL);
}

int	find_token(char **ps, const char *es, const t_token *to_search)
{
	char	*s;
	t_token	token;

	s = *ps;
	skip_whitespace(&s, es);
	token = parse_token(&s, es);
	while (*to_search != TOKEN_NULL)
	{
		if (token == *to_search)
			return (1);
		to_search++;
	}
	return (0);
}

t_token	get_token(char **ps, const char *es, char **q, char **eq)
{
	char	*s;
	t_token	token;

	s = *ps;
	skip_whitespace(&s, es);
	if (q)
		*q = s;
	token = parse_token(&s, es);
	if (eq)
		*eq = s;
	skip_whitespace(&s, es);
	*ps = s;
	return (token);
}

t_token	peek_token(char **ps, const char *es, int skip)
{
	char	*s;
	t_token	token;

	s = *ps;
	skip_whitespace(&s, es);
	token = parse_token(&s, es);
	while (skip-- > 0)
	{
		skip_whitespace(&s, es);
		token = parse_token(&s, es);
	}
	return (token);
}
