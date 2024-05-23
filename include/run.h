#ifndef RUN_H
# define RUN_H

# include "lexer.h"

void	runexec(t_execcmd *ecmd, char **envp);
void	runredi(t_redicmd *rcmd, char **envp);
void	runpipe(t_pipecmd *pcmd, char **envp);
void	runlist(t_listcmd *lcmd, char **envp);
void	runback(t_backcmd *bcmd, char **envp);

void	freecmd(t_cmd *cmd);
void	runcmd(t_cmd *cmd, char **envp);

#endif

// vim: ts=4 sts=4 sw=4 noet
