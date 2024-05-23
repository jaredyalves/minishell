#ifndef NULTERMINATE_H
# define NULTERMINATE_H

# include "../lexer/lexer.h"

void	nulexec(t_execcmd *ecmd);
void	nulredi(t_redicmd *rcmd);
void	nulpipe(t_pipecmd *pcmd);
void	nullist(t_listcmd *lcmd);
void	nulback(t_backcmd *bcmd);

t_cmd	*nulterminate(t_cmd *cmd);

#endif

// vim: ts=4 sts=4 sw=4 noet
