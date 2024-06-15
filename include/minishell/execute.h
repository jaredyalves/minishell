#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell/parse.h"

int		is_builtin(t_execute *ecmd);

void	execute_command(t_cmd *cmd) __attribute__((noreturn));
void	execute_execute(t_execute *ecmd) __attribute__((noreturn));
void	execute_builtin(t_execute *ecmd) __attribute__((noreturn));
void	execute_external(t_execute *ecmd) __attribute__((noreturn));
void	execute_redirection(t_redirection *rcmd) __attribute__((noreturn));
void	execute_list(t_list *lcmd) __attribute__((noreturn));
void	execute_pipeline(t_pipeline *pcmd) __attribute__((noreturn));

#endif
