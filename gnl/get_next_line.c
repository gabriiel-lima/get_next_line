/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garodri2 <garodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:31:23 by garodri2          #+#    #+#             */
/*   Updated: 2026/06/11 14:20:58 by garodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_new_line(char *stash)
{
	int	i;

	i = 0;
	if (!stash)
		return (0);
	while (stash[i] != '\0')
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_fd(int fd, char *stash)
{
	ssize_t		bytes;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (check_new_line(stash) == 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes < 0)
			return (free(buffer), free(stash), stash = NULL, NULL);
		buffer[bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
		// Need check if bytes is -1
	}
	free(buffer);
	return (stash); // abc\ndef
}

char	*build_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_strncpy(line, stash, i);
	line[i] = '\0';
	return (line);
}

char	*clean(char *stash)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || !stash[i + 1])
		return (free(stash), NULL);
	i++;
	while (stash[i] && stash[i + j])
		j++;
	aux = malloc(j + 1);
	if (!aux)
		return (free(stash), NULL);
	ft_strncpy(aux, stash + i, j);
	aux[j] = '\0';
	return (free(stash), aux);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	stash = read_fd(fd, stash);
	if (!stash || !*stash)
		return(free(stash), NULL);
	line = build_line(stash); // Need fix that
	stash = clean(stash);
	if (!stash || !*stash)
		stash = NULL;
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("one.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
