#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#	ifndef BUFFER_SIZE
#	define BUFFER_SIZE 42
#	endif

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*clean_old(char *static_var);
char	*build_line(char *str);
int		check_new_line(char *str);

# endif