#include "ft.h"
#include "minishell.h"

#include <fcntl.h>

t_cmd	*execute_command(void)
{
	t_execcmd	*cmd;

	cmd = (t_execcmd *)ft_calloc(1, sizeof(*cmd));
	if (cmd == NULL)
		panic("ft_calloc");
	cmd->type = TYPE_EXECUTE;
	return ((t_cmd *)cmd);
}

t_cmd	*redirect_command(t_cmd *sub, char *file, char *end_file, int mode)
{
	t_redicmd	*cmd;

	cmd = (t_redicmd *)ft_calloc(1, sizeof(*cmd));
	if (cmd == NULL)
		panic("ft_calloc");
	cmd->type = TYPE_REDIRECT;
	cmd->command = sub;
	cmd->file = file;
	cmd->end_file = end_file;
	cmd->mode = mode;
	if ((mode & O_ACCMODE) == O_RDONLY)
		cmd->fd = 0;
	if ((mode & O_ACCMODE) == O_WRONLY)
		cmd->fd = 1;
	return ((t_cmd *)cmd);
}

t_cmd	*heredoc_command(t_cmd *sub)
{
	t_herecmd	*cmd;

	cmd = (t_herecmd *)ft_calloc(1, sizeof(*cmd));
	if (cmd == NULL)
		panic("ft_calloc");
	cmd->type = TYPE_HEREDOC;
	cmd->command = sub;
	return ((t_cmd *)cmd);
}

t_cmd	*background_command(t_cmd *sub)
{
	t_backcmd	*cmd;

	cmd = (t_backcmd *)ft_calloc(1, sizeof(*cmd));
	if (cmd == NULL)
		panic("ft_calloc");
	cmd->type = TYPE_BACKGROUND;
	cmd->command = sub;
	return ((t_cmd *)cmd);
}

t_cmd	*logical_command(t_type type, t_cmd *left, t_cmd *right)
{
	t_logicmd	*cmd;

	cmd = (t_logicmd *)ft_calloc(1, sizeof(*cmd));
	if (cmd == NULL)
		panic("ft_calloc");
	cmd->type = TYPE_LOGICAL;
	cmd->sub = type;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
