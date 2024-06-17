#ifndef UTILS_H
# define UTILS_H

void	panic(char *error) __attribute__((noreturn));

int		fork1(void);
void	get_str(void);
int		pipe1(int *pipes);
t_cmd	*free_command(t_cmd **cmd);
void	handle_signals(void);

#endif
