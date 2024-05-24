#include "ft.h"
#include "parser.h"

t_token double_token(char **ps)
{
	if (**ps == '<' && *(*ps + 1) == '<')
		return ((*ps) += 2, TOKEN_DOUBLE_LESS);
	if (**ps == '|' && *(*ps + 1) == '|')
		return ((*ps) += 2, TOKEN_DOUBLE_PIPE);
	if (**ps == '>' && *(*ps + 1) == '>')
		return ((*ps) += 2, TOKEN_DOUBLE_GREATER);
	if (**ps == '&' && *(*ps + 1) == '&')
		return ((*ps) += 2, TOKEN_DOUBLE_AMPERSAND);
	return (TOKEN_NULL);
}

t_token single_token(char **ps)
{
	if (**ps == '<')
		return ((*ps)++, TOKEN_SINGLE_LESS);
	if (**ps == '|')
		return ((*ps)++, TOKEN_SINGLE_PIPE);
	if (**ps == '>')
		return ((*ps)++, TOKEN_SINGLE_GREATER);
	if (**ps == '&')
		return ((*ps)++, TOKEN_SINGLE_AMPERSAND);
	if (**ps == ';')
		return ((*ps)++, TOKEN_SINGLE_SEMICOLON);
	if (**ps == '(')
		return ((*ps)++, TOKEN_LEFT_PARENTHESES);
	if (**ps == ')')
		return ((*ps)++, TOKEN_RIGHT_PARENTHESES);
	return (TOKEN_NULL);
}

t_token parse_token(char **ps, const char *es)
{
	char   *s;
	t_token token;

	s = *ps;
	if (*s == '\0')
		return (TOKEN_NULL);
	token = double_token(&s);
	if (token == TOKEN_NULL)
		token = single_token(&s);
	if (token == TOKEN_NULL)
	{
		token = TOKEN_NO_SPECIAL;
		while (s < es && !ft_strchr(WHITESPACE, *s) && !ft_strchr(SYMBOLS, *s))
			s++;
	}
	*ps = s;
	return (token);
}

// vim: ts=4 sts=4 sw=4 noet
