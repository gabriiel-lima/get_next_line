/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garodri2 <garodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:39:18 by garodri2          #+#    #+#             */
/*   Updated: 2026/06/05 16:31:26 by garodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*sobra;
	char		*buffer;
	int			bytes;
	
	if(fd < 0 && BUFFER_SIZE <= 0)	
		return NULL;
	bytes = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	sobra = clean_old(sobra);
	while (bytes > 0 && !check_new_line(sobra))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if(bytes == 0)
			break ;
		if(bytes < 0)
			return free(buffer), free(sobra), sobra = NULL, NULL; 
		buffer[bytes] = '\0';
		sobra = ft_strjoin(sobra, buffer);
	}
	free(buffer);
	return build_line(sobra);
}

int	main(void)
{
	int	fd;

	
	fd = open("test.txt", O_RDONLY);
	char *charpointer = get_next_line(fd);
	
	while(charpointer)
	{
		printf("%s", charpointer); 
		free(charpointer);
		charpointer = get_next_line(fd);
	}
	return (0);
}
