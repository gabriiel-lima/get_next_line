/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garodri2 <garodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:39:18 by garodri2          #+#    #+#             */
/*   Updated: 2026/06/02 16:58:46 by garodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// int	find_next_line(char *str)
// {}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	i = 0;
	ptr_src = (unsigned char *)src;
	ptr_dest = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*sobra;
	char		*line;
	char		*buffer;
	char		*auxiliary;
	int			bytes;
	size_t		i;
	int			y;
	int			z;
	int condicional;

	condicional = 0;
	z = 0;
	i = 0;
	y = 0;
	int j = 0;
	//int find_new_line;
	bytes = 1;
	buffer = malloc(3);
	if (!buffer)
		return (NULL);

	
	//Clean old static
	if(sobra != NULL)
	{
		while(sobra[i] != '\n')
		{
			i++;
		}
		i++;
		while(sobra[i] && sobra[i + j] != '\0')
			j ++;
		auxiliary = malloc (j + 1);
		if(!auxiliary)
			return NULL;
		ft_memcpy(auxiliary, sobra + i, j);
		free(sobra);
		sobra = auxiliary;
	}
	// Read Line 
	while (bytes > 0 && condicional == 0)
	{
		bytes = read(fd, buffer, 3);
		buffer[bytes] = '\0';
		sobra = ft_strjoin(sobra, buffer);
		while(sobra[z] != '\0')
		{
			if(sobra[z] == '\n')
			{
				condicional = 1;
			}
			z ++;
		}
		if(bytes == 0)
			return "Error";
			//CHECK IF THERE IS NO MORE TO READ
	}

	i = 0;
	//Build the line
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
			line[y + 1] = '\0';
			return(line);
		}
		i++;
	}
	return ("saiu");
}
// JA E POSSIVEL RETORNAR UMA LINHA, COMO FAZER PARA QUANDO A FUNCAO FOR CHAMADA UMA SEGUNDA VEZ ELA CONTINUA A LER DA ONDE PAROU?

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}
