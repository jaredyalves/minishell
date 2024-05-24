#include "ft.h"
#include "parser.h"
#include <stddef.h>

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
	char   *s;
	t_token token;

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

int peek(char **ps, char *es, char *tokens)
{
	char *s;

	s = *ps;
	skip_whitespace(&s, es);
	*ps = s;
	return (*s && ft_strchr(tokens, *s));
}
