#include "minishell.h"

static void skip_whitespace(char **ps, const char *es)
{
	char *s;

	if (*ps == NULL || es == NULL)
		return;
	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	*ps = s;
}

t_token get_token(char **ps, char *es, char **q, char **eq)
{
	t_token token;

	skip_whitespace(ps, es);
	if (q)
		*q = *ps;
	token = parse_token(ps, es);
	if (token == TOKEN_DOUBLE_QUOTE || token == TOKEN_SINGLE_QUOTE)
	{
		if (q)
			*q = *ps;
		if (token == TOKEN_DOUBLE_QUOTE)
			while (*ps < es && !ft_strchr("\"", **ps))
				(*ps)++;
		if (token == TOKEN_SINGLE_QUOTE)
			while (*ps < es && !ft_strchr("'", **ps))
				(*ps)++;
	}
	if (eq)
		*eq = *ps;
	if (*ps < es
		&& (token == TOKEN_DOUBLE_QUOTE || token == TOKEN_SINGLE_QUOTE))
		(*ps)++;
	skip_whitespace(ps, es);
	return (token);
}

int peek(char **ps, char *es, char *tokens)
{
	char *s;

	s = *ps;
	skip_whitespace(&s, es);
	*ps = s;
	return (*s && ft_strchr(tokens, *s));
}
