#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	sh_init(argc, argv, envp);
	while (sh_keep_running())
		;
	sh_deinit();
}
