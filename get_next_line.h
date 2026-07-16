#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*get_next_line(int fd);
char	*clean(char *stash);
char	*build_line(char *stash);
char	*read_fd(int fd, char *stash);
int	check_new_line(char *stash);

#endif