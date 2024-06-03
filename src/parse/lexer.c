#include "minishell.h"

t_cmd	*execute_command(void)
{
	t_execcmd	*cmd;

	cmd = (t_execcmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
	{
		perror("minishell: malloc");
		exit(1);
	}
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_EXECUTE;
	return ((t_cmd *)cmd);
}

t_cmd	*redirect_command(t_cmd *sub, char *file, char *end_file, int mode)
{
	t_redicmd	*cmd;

	cmd = (t_redicmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
	{
		perror("minishell: malloc");
		exit(1);
	}
	ft_memset(cmd, 0, sizeof(*cmd));
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

t_cmd	*background_command(t_cmd *sub)
{
	t_backcmd	*cmd;

	cmd = (t_backcmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
	{
		perror("minishell: malloc");
		exit(1);
	}
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_BACKGROUND;
	cmd->command = sub;
	return ((t_cmd *)cmd);
}

t_cmd	*logical_command(t_type type, t_cmd *left, t_cmd *right)
{
	t_logicmd	*cmd;

	cmd = (t_logicmd *)malloc(sizeof(*cmd));
	if (cmd == NULL)
	{
		perror("minishell: malloc");
		exit(1);
	}
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = TYPE_LOGICAL;
	cmd->sub_type = type;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
