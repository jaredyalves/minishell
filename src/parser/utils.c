#include "parser.h"
#include <string.h>

// FIXME: Can't use strchr(), replace with a ft function
void	skip_whitespace(char **ps, char *es)
{
	char	*s;

	s = *ps;
	while (s < es && strchr(WHITESPACE, *s))
		s++;
	*ps = s;
}

// FIXME: Can't use strchr(), replace with a ft function
void	process_token(char **ps, char *es, int *ret)
{
	char	*s;

	s = *ps;
	if (*s == '|' || *s == '(' || *s == ')' || *s == ';' || *s == '&'
		|| *s == '<')
		s++;
	else if (*s == '>')
	{
		s++;
		if (*s == '>')
		{
			*ret = '+';
			s++;
		}
	}
	else if (*s != 0)
	{
		*ret = 'a';
		while (s < es && !strchr(WHITESPACE, *s) && !strchr(WHITESPACE, *s))
			s++;
	}
	*ps = s;
}

int	get_token(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	skip_whitespace(&s, es);
	if (q)
		*q = s;
	ret = *s;
	process_token(&s, es, &ret);
	if (eq)
		*eq = s;
	skip_whitespace(&s, es);
	*ps = s;
	return (ret);
}

// FIXME: Can't use strchr(), replace with a ft function
int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	skip_whitespace(&s, es);
	*ps = s;
	return (*s && strchr(toks, *s));
}

// vim: ts=4 sts=4 sw=4 noet
