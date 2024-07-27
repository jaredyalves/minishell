#include "minishell.h"

static int	check_quotes(char *cls, char *cle)
{
	int	single_quotes;
	int	double_quotes;
	int	inside_single_quotes;
	int	inside_double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	inside_single_quotes = 0;
	inside_double_quotes = 0;
	while (cls < cle)
	{
		if (*cls == '\'' && !inside_double_quotes)
		{
			inside_single_quotes = !inside_single_quotes;
			single_quotes++;
		}
		else if (*cls == '\"' && !inside_single_quotes)
		{
			inside_double_quotes = !inside_double_quotes;
			double_quotes++;
		}
		cls++;
	}
	return (single_quotes % 2 == 0 && double_quotes % 2 == 0);
}

void	parse_cmdline(t_ms *ms)
{
	char	*cmdline_start;
	char	*cmdline_end;

	cmdline_start = ms->cmdline;
	cmdline_end = cmdline_start + ms_strlen(cmdline_start);
	if (check_quotes(cmdline_start, cmdline_end) == 0)
		return (unclosed_quotes());
	parse_line(ms, &cmdline_start, cmdline_end);
}
