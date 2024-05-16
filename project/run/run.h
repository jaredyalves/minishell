#ifndef RUN_H
# define RUN_H

# include "../lexer/lexer.h"

void	runexec(t_execcmd *ecmd);
void	runredi(t_redicmd *rcmd);
void	runpipe(t_pipecmd *pcmd);
void	runlist(t_listcmd *lcmd);
void	runback(t_backcmd *bcmd);

void	freecmd(t_cmd *cmd);
void	runcmd(t_cmd *cmd);

#endif

// vim: ts=4 sts=4 sw=4 noet
