#include "libft.h"
#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>

static char	*expand_variable(char **arg)
{
	char	env_name[1024];
	char	*env_value;
	char	*current;

	ft_bzero(env_name, sizeof(env_name));
	if (*arg && (ft_isalnum(**arg) || **arg == '_'))
	{
		current = env_name;
		while (*arg && (ft_isalnum(**arg) || **arg == '_'))
			*current++ = *(*arg)++;
		*current = '\0';
		env_value = ft_getenv(env_name);
		if (env_value)
			return (env_value);
		return ("");
	}
	return ("$");
}

static char	*expand_variables(char *arg)
{
	char	expanded[1024];
	char	*current;

	ft_bzero(expanded, sizeof(expanded));
	while (arg && *arg)
	{
		current = expanded + ft_strlen(expanded);
		while (*arg && *arg != '$')
			*current++ = *arg++;
		*current = '\0';
		if (*arg == '$')
		{
			arg++;
			ft_strlcat(expanded, expand_variable(&arg), sizeof(expanded));
		}
	}
	return (ft_strdup(expanded));
}

static char	*remove_quotes(const char *arg)
{
	char	*no_quotes;
	char	*dest;
	char	quote;

	no_quotes = (char *)malloc(ft_strlen(arg) + 1);
	if (no_quotes == NULL)
		panic("malloc");
	dest = no_quotes;
	quote = 0;
	while (*arg)
	{
		if (*arg == '\\' && (*(arg + 1) == '"' || *(arg + 1) == '\''))
			*dest++ = *++arg;
		else if (!quote && (*arg == '"' || *arg == '\''))
			quote = *arg++;
		else if (*arg == quote)
		{
			quote = 0;
			arg++;
		}
		else
			*dest++ = *arg++;
	}
	*dest = '\0';
	return (no_quotes);
}

char	*expand_argument(char *q, char *eq)
{
	char	*no_quotes;
	char	*expanded;
	char	c;

	c = *eq;
	*eq = 0;
	no_quotes = remove_quotes(q);
	if (*q == '\'')
		return (no_quotes);
	if (ft_strchr(q, '$'))
	{
		free(no_quotes);
		expanded = expand_variables(q);
		no_quotes = remove_quotes(expanded);
		free(expanded);
		return (no_quotes);
	}
	*eq = c;
	return (no_quotes);
}
