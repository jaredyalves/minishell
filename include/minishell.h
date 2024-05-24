#ifndef MINISHELL_H
# define MINISHELL_H

#include "lexer.h"

char   *get_line(char *line);
void	panic(char *str, t_cmd *cmd);
int		fork1(void);

#endif
