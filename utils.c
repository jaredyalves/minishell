#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*gets(char *buf, int max)
{
	int		i;
	int		r;
	char	c;

	i = 0;
	while (i + 1 < max)
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r < 1)
			break ;
		buf[i++] = c;
		if (c == '\n' || c == '\r')
			break ;
	}
	buf[i] = '\0';
	return (buf);
}

// FIXME: Can't use fprintf(), replace with a ft function
void	panic(char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(EXIT_FAILURE);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		panic("minishell: fork error");
	return (pid);
}

// vim: ts=4 sts=4 sw=4 noet
