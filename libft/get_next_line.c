/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:26:15 by chorse            #+#    #+#             */
/*   Updated: 2022/01/11 13:52:41 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include <stdio.h>
#include <time.h>

int	find_n(char *ost)
{
	int	i;

	i = 0;
	while (ost[i] != '\0')
	{
		if (ost[i] == '\n')
			return (i + 1);
		i++;
	}
	return (-1);
}

char	*ft_change_ost(char **ost, size_t *size_ost, int id_n, int i)
{
	char	*tmp;

	if ((*ost)[i] != '\0')
	{
		tmp = *ost;
		*size_ost = (*size_ost) - id_n;
		*ost = ft_strdup1(&(*ost)[id_n], *size_ost);
		free(tmp);
		return (*ost);
	}
	else
	{
		free(*ost);
		return (NULL);
	}
}

static char	*ft_check_ost(char *ost, char **res, int n_read, size_t *size_ost)
{
	int		id_n;
	int		i;

	id_n = find_n(ost);
	if (id_n != -1)
	{
		ft_create_res(res, ost, id_n, &i);
		if (ft_change_ost(&ost, size_ost, id_n, i) == NULL)
			return (NULL);
	}
	else if (id_n == -1 && n_read == 0)
	{
		*res = ft_strdup1(ost, *size_ost);
		if (ost)
			free(ost);
		ost = NULL;
		return (NULL);
	}
	return (ost);
}

char	*ft_no_read(char **ost, char **res, int n_read, size_t *size_ost)
{
	if (*ost)
	{
		*ost = ft_check_ost(*ost, res, n_read, size_ost);
		return (*res);
	}
	else
		return (NULL);
}

char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE + 1];
	char			*res;
	static char		*ost;
	static size_t	size_ost;
	int				n_read;

	res = NULL;
	while (!res)
	{
		n_read = read(fd, &buf, BUFFER_SIZE);
		buf[n_read] = '\0';
		if (n_read > 0)
			ft_make_ost(&ost, buf, &size_ost, n_read);
		else if (n_read == 0)
			return (ft_no_read(&ost, &res, n_read, &size_ost));
		else
			return (NULL);
		ost = ft_check_ost(ost, &res, n_read, &size_ost);
	}
	return (res);
}
