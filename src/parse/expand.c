#include "minishell.h"

char	*expand_variables(const char *arg, char **envp)
{
	char	*current;
	char	expanded[MAX_INPUT];
	char	env_name[MAX_INPUT];
	char	*env_value;

	while (arg && *arg)
	{
		current = expanded + ft_strlen(expanded);
		while (*arg && *arg != '$')
			*current++ = *arg++;
		*current = '\0';
		if (*arg == '$')
		{
			arg++;
			current = env_name;
			while (*arg && (ft_isalnum(*arg) || *arg == '_'))
				*current++ = *arg++;
			env_value = ft_getenv(env_name, envp);
			if (env_value)
				ft_strlcat(expanded, env_value, sizeof(expanded));
		}
	}
	return (ft_strdup(expanded));
}

char	*remove_quotes(const char *arg)
{
	char	*no_quotes;
	char	*dst;
	char	quote;

	no_quotes = (char *)malloc(ft_strlen(arg) + 1);
	dst = no_quotes;
	quote = 0;
	while (*arg)
	{
		if (*arg == '\\' && (*(arg + 1) == '"' || *(arg + 1) == '\''))
			*dst++ = *++arg;
		else if (!quote && (*arg == '"' || *arg == '\''))
			quote = *arg++;
		else if (*arg == quote)
		{
			quote = 0;
			arg++;
		}
		else
			*dst++ = *arg++;
	}
	*dst = '\0';
	return (no_quotes);
}

char	*expand_argument(const char *arg, char **envp)
{
	char	*no_quotes;
	char	*expanded;

	no_quotes = remove_quotes(arg);
	if (*arg == '\'')
		return (no_quotes);
	if (ft_strchr(arg, '$'))
	{
		expanded = expand_variables(no_quotes, envp);
		free(no_quotes);
		return (expanded);
	}
	return (no_quotes);
}

char	**expand_arguments(char **args, char **envp)
{
	char	**expanded;
	size_t	size;
	size_t	i;

	size = 0;
	while (args[size])
		size++;
	expanded = (char **)malloc((size + 1) * sizeof(char *));
	if (expanded == NULL)
	{
		perror("minishell: malloc");
		exit(1);
	}
	i = -1;
	while (++i < size)
		expanded[i] = expand_argument(args[i], envp);
	expanded[i] = NULL;
	return (expanded);
}
