#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

# define WHITESPACE " \t\r\n\v"
# define SYMBOLS "<|>&;()"

void	skip_whitespace(char **ps, char *es);
void	process_token(char **ps, char *es, int *ret);
int		get_token(char **ps, char *es, char **q, char **eq);
int		peek(char **ps, char *es, char *toks);

t_cmd	*parseline(char **ps, char *es);
t_cmd	*parsepipe(char **ps, char *es);
t_cmd	*parseexec(char **ps, char *es);
t_cmd	*parseredir(t_cmd *cmd, char **ps, char *es);
t_cmd	*parseblock(char **ps, char *es);

t_cmd	*parsecmd(char *s);

#endif

// vim: ts=4 sts=4 sw=4 noet
