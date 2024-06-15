#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell/colors.h"
# include "minishell/execute.h"
# include "minishell/ft.h"
# include "minishell/limits.h"
# include "minishell/parse.h"
# include "minishell/utils.h"

typedef struct s_sh
{
	int		init;
	char	*env[ENV_MAX];
	char	*str;
	t_cmd	*cmd;
	int		exit_status;
	int		wait_status;
}			t_sh;

t_sh		*get_sh(void);
void		sh_init(int argc, char *argv[], char *envp[]);
void		sh_deinit(void);

#endif
