/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garodri2 <garodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 15:13:08 by garodri2          #+#    #+#             */
/*   Updated: 2026/06/05 16:47:20 by garodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if(!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	if(!s1)
		s1 = "";
	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (free(s1), NULL);
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
	return (free(s1), res);
}

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

char	*clean_old(char *static_var)
{
	char	*auxiliary;
	size_t	i;
	int	j;
	
	i = 0;
	j = 0;
	if(static_var != NULL)
	{
		while(static_var[i] != '\n')
		{
			i++;
		}
		i++;
		while(static_var[i] && static_var[i + j] != '\0')
			j ++;
		auxiliary = malloc (j + 1);
		if(!auxiliary)
			return (NULL);
		ft_memcpy(auxiliary, static_var + i, j);
		free(static_var);
		return auxiliary;
	}
	return(NULL);
}

char *build_line(char *str)
{
	char	*line;
	size_t	i;
	int	y;

	i = 0;
	y = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		i++;
	}
	line = malloc(i + 1);
	if(!line)
		return(NULL);
	i = 0;
	while(i < ft_strlen(str))
	{
		line[i] = str[i];
		i++;
	}
	line[i + 1] = '\0';
	return(line);
}

int	check_new_line(char *str)
{
	int	i;

	i = 0;
	if(!str)
		return (0);
	while(str[i] != '\0')
	{
		if(str[i] == '\n')
			return 1;
		i ++;
	}
	return 0;
}
