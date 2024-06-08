#include "ft.h"
#include "minishell.h"

void	parse_quote(char **ps, const char *es)
{
	char	*s;
	int		quote;

	s = *ps;
	quote = *s++;
	while (s < es && *s != quote)
		s++;
	if (s < es)
		s++;
	*ps = s;
}

int	parse_token(char **ps, const char *es)
{
	char	*s;
	int		token;

	s = *ps;
	token = 0;
	if (s < es && ft_strchr(SYMBOLS, *s))
	{
		token = *s++;
		if (*s != '(' && *s != ')' && s < es && *s == *(s - 1))
			token = -*s++;
	}
	else if (s < es)
	{
		token = 'a';
		while (s < es && ft_strchr(WHITESPACE, *s) == NULL
			&& ft_strchr(SYMBOLS, *s) == NULL)
		{
			if (*s == '\'' || *s == '"')
				parse_quote(&s, es);
			else
				s++;
		}
	}
	*ps = s;
	return (token);
}

int	get_token(char **ps, const char *es, char **q, char **eq)
{
	char	*s;
	int		token;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	if (q)
		*q = s;
	token = parse_token(&s, es);
	if (eq)
		*eq = s;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	*ps = s;
	return (token);
}

int	peek(char **ps, const char *es, const char *stoks, const char *dtoks)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(WHITESPACE, *s))
		s++;
	*ps = s;
	if (*s && *s != *(s + 1))
		return (ft_strchr(stoks, *s) != NULL);
	if (*s && *s == *(s + 1))
		return (ft_strchr(dtoks, *s) != NULL);
	return (0);
}
