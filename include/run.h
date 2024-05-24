#ifndef RUN_H
# define RUN_H

# include "lexer.h"

int		runexec(t_execcmd *ecmd, char **envp);
int		runredi(t_redicmd *rcmd, char **envp);
int		runpipe(t_pipecmd *pcmd, char **envp);
int		runlist(t_listcmd *lcmd, char **envp);
int		runback(t_backcmd *bcmd, char **envp);

void	freecmd(t_cmd *cmd);
int		runcmd(t_cmd *cmd, char **envp);

#endif

// vim: ts=4 sts=4 sw=4 noet
