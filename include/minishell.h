/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamonte <joamonte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 08:39:06 by jcapistr          #+#    #+#             */
/*   Updated: 2024/06/21 16:44:01 by joamonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <linux/limits.h>

# define BLANKS " \t"
# define TOKENS "<|>()&;"

typedef enum e_type
{
	EXECUTE,
	REDIRECTION,
	LIST,
	PIPELINE,
}				t_type;

typedef enum e_subtype
{
	REDIRECT,
	HEREDOC,
	PIPE,
	SEQUENCE,
	BACKGROUND,
	AND_IF,
	OR_IF,
}				t_subtype;

typedef struct s_cmd
{
	t_type		type;
}				t_cmd;

typedef struct s_execute
{
	int			type;
	int			argc;
	char		*argv[ARG_MAX + 1];
}				t_execute;

typedef struct s_redirection
{
	t_type		type;
	t_subtype	subtype;
	t_cmd		*cmd;
	char		*buffer;
	int			mode;
	int			fd;
}				t_redirection;

typedef struct s_list
{
	t_type		type;
	t_subtype	subtype;
	t_cmd		*left;
	t_cmd		*right;
}				t_list;

typedef struct s_pipeline
{
	t_type		type;
	t_subtype	subtype;
	t_cmd		*left;
	t_cmd		*right;
}				t_pipeline;

typedef struct s_sh
{
	int			init;
	char		*env[ARG_MAX + 1];
	char		*str;
	t_cmd		*cmd;
	int			exit_status;
	int			subshell;
}				t_sh;

t_sh			*get_sh(void);
void			sh_init(int argc, char *argv[], char *envp[]);
void			sh_deinit(int status) __attribute__((noreturn));

t_cmd			*execute(void);
t_cmd			*redirection(t_subtype subtype, t_cmd *subcmd, int m, int fd);
t_cmd			*list(t_subtype subtype, t_cmd *left, t_cmd *right);
t_cmd			*pipeline(t_subtype subtype, t_cmd *left, t_cmd *right);

t_cmd			*parse_block(char **ps, char *es);
t_cmd			*parse_command(char *s);
t_cmd			*parse_execute(char **ps, char *es);
t_cmd			*parse_list1(char **ps, char *es);
t_cmd			*parse_list2(char **ps, char *es);
t_cmd			*parse_pipeline(char **ps, char *es);
t_cmd			*parse_redirection(t_cmd *cmd, char **ps, char *es);

char			*expand_argument(char *q, char *eq);
char			*concat_strings(char *arg, char *str);

int				get_token(char **ps, char *es, char **q, char **eq);
int				peek(char **ps, char *es, char *s_tokens, char *d_tokens);
int				peek_next(char **ps, char *es, char *s_tokens, char *d_tokens);

int				is_builtin(t_execute *ecmd);
void			execute_builtin(t_execute *ecmd);
void			execute_command(t_cmd *cmd);
void			execute_execute(t_execute *ecmd);
void			execute_external(t_execute *ecmd);
void			execute_list(t_list *lcmd);
void			execute_pipeline(t_pipeline *pcmd);
void			execute_redirection(t_redirection *rcmd);

pid_t			fork1(void);
int				pipe1(int *pipes);
t_cmd			*free_command(t_cmd **cmd);
char			*get_line(char *prompt);
void			get_str(void);
void			handle_signals(void);
void			panic(char *error) __attribute__((noreturn));

int				ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_getenv(char *name);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
char			*ft_itoa(int n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

int				ft_cd(char **args);
int				ft_echo(char **args);
int				ft_env(char **args);
int				ft_exit(char **args);
int				ft_export(char **args);
int				ft_pwd(char **args);
int				ft_unset(char **args);

#endif
