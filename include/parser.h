#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

# define WHITESPACE " \t\r\n\v"
# define SYMBOLS "<|>&;()"

typedef enum e_token
{
	TOKEN_NULL,
	TOKEN_NO_SPECIAL,
	TOKEN_SINGLE_AMPERSAND,
	TOKEN_DOUBLE_AMPERSAND,
	TOKEN_SINGLE_PIPE,
	TOKEN_DOUBLE_PIPE,
	TOKEN_SINGLE_LESS,
	TOKEN_DOUBLE_LESS,
	TOKEN_SINGLE_GREATER,
	TOKEN_DOUBLE_GREATER,
	TOKEN_SINGLE_SEMICOLON,
	TOKEN_LEFT_PARENTHESES,
	TOKEN_RIGHT_PARENTHESES,
} t_token;

t_token parse_token(char **ps, const char *es);
t_token get_token(char **ps, char *es, char **q, char **eq);
int		peek(char **ps, char *es, char *tokens);

t_cmd	*parseline(char **ps, char *es);
t_cmd	*parsepipe(char **ps, char *es);
t_cmd	*parseexec(char **ps, char *es);
t_cmd	*parseredir(t_cmd *cmd, char **ps, char *es);
t_cmd	*parseblock(char **ps, char *es);

void   terminate_execute(t_execcmd *ecmd);
void   terminate_redirect(t_redicmd *rcmd);
void   terminate_pipe(t_pipecmd *pcmd);
void   terminate_sequence(t_listcmd *lcmd);
void   terminate_background(t_backcmd *bcmd);
void   terminate_and(t_andcmd *acmd);
void   terminate_or(t_orcmd *ocmd);
t_cmd *terminate_line(t_cmd *cmd);

t_cmd	*parsecmd(char *s);

#endif

// vim: ts=4 sts=4 sw=4 noet
