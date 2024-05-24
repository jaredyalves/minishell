#include "minishell.h"

static int	count_words(char *str, char chr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == chr)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != chr)
				i++;
		}
	}
	return (count);
}

static char	*put_word(char *word, char *str, int i, int word_len)
{
	int	j;

	j = 0;
	while (word_len > 0)
	{
		word[j] = str[i - word_len];
		j++;
		word_len--;
	}
	word[j] = '\0';
	return (word);
}

static char	**split_words(char *str, char chr, char **buf, int words_count)
{
	int	i;
	int	word;
	int	word_len;

	i = 0;
	word = 0;
	word_len = 0;
	while (word < words_count)
	{
		while (str[i] && str[i] == chr)
			i++;
		while (str[i] && str[i] != chr)
		{
			i++;
			word_len++;
		}
		buf[word] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!buf[word])
			return (0);
		put_word(buf[word], str, i, word_len);
		word_len = 0;
		word++;
	}
	buf[word] = 0;
	return (buf);
}

char	**ft_split(char *str, char chr)
{
	char	**s2;
	int		num_words;

	if (!str)
		return (0);
	num_words = count_words(str, chr);
	s2 = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!s2)
		return (0);
	split_words(str, chr, s2, num_words);
	return (s2);
}
