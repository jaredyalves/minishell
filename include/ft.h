#ifndef FT_H
# define FT_H

#include <stddef.h>

char	**ft_split(char *str, char chr);
int		  ft_dprintf(int fd, const char *format, ...);
size_t	  ft_strlen(const char *s);
void	 *ft_memset(void *s, int c, size_t n);

#endif

// vim: ts=4 sts=4 sw=4 noet
