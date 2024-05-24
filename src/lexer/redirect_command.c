#include "minishell.h"

t_cmd	*redirect_command(t_cmd *command, char *file, char *end_file, int mode)
{
	t_redicmd	*cmd;

	cmd = (t_redicmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
		panic("malloc", NULL);
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_REDIRECT;
	cmd->cmd = command;
	cmd->file = file;
	cmd->efile = end_file;
	cmd->mode = mode;
	if ((mode & O_ACCMODE) == O_RDONLY)
		cmd->fd = 0;
	else if ((mode & O_ACCMODE) == O_WRONLY)
		cmd->fd = 1;
	else
		cmd->fd = -1;
	return ((t_cmd *)cmd);
}
