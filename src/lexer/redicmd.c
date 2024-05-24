#include "minishell.h"

t_cmd	*redicmd(t_cmd *subcmd, char *file, char *efile, int mode)
{
	t_redicmd	*cmd;

	cmd = (t_redicmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
		panic("malloc", NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_REDIRECT;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	if ((mode & O_ACCMODE) == O_RDONLY)
		cmd->fd = 0;
	else if ((mode & O_ACCMODE) == O_WRONLY)
		cmd->fd = 1;
	else
		cmd->fd = -1;
	return ((t_cmd *)cmd);
}
