/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garodri2 <garodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:39:18 by garodri2          #+#    #+#             */
/*   Updated: 2026/05/28 21:18:00 by garodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// int	find_next_line(char *str)
// {}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	if(!s1)
		s1 = "";
	if (!s2)
		return (NULL);
	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*sobra = NULL;
	char		*line;
	char		*buffer;
	int			bytes;
	size_t		i;
	int			y;

	bytes = 1;
	buffer = malloc(6);
	if (!buffer)
		return (NULL);
	i = 0;
	y = 0;
	while (bytes > 0)
	{	
		bytes = read(fd, buffer, 5);
		buffer[bytes] = '\0';
		sobra = ft_strjoin(sobra, buffer);
		while (i <= ft_strlen(sobra))
		{
			if (sobra[i] == '\n')
			{
				line = malloc(i + 2);
				while (sobra[y] != '\n')
				{
					line[y] = sobra[y];
					y++;
				}
				line[y] = '\n';
				line[y+1] = '\0';
				return (line);
			}
			i++;
		}
	}
	return (NULL);
}
// JA E POSSIVEL RETORNAR UMA LINHA, COMO FAZER PARA QUANDO A FUNCAO FOR CHAMADA UMA SEGUNDA VEZ ELA CONTINUA A LER DA ONDE PAROU?

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}
