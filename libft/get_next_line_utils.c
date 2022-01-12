/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:06:28 by sazelda           #+#    #+#             */
/*   Updated: 2022/01/11 13:52:56 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin1(char const *s1, char const *s2, \
					size_t *size_ost, size_t len_s2)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;

	if (!s1)
		return ((void *)0);
	i = 0;
	res = (char *)malloc(*size_ost + len_s2 + 1);
	if (!res)
		return ((void *)0);
	while (i < *size_ost)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len_s2)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	*size_ost = *size_ost + len_s2;
	return (res);
}

char	*ft_strdup1(const char *s1, size_t size_ost)
{
	char	*res;

	res = malloc(size_ost + 1);
	if (!res)
		return ((void *)0);
	ft_memcpy(res, s1, size_ost + 1);
	return (res);
}

void	ft_make_ost(char **ost, char *buf, size_t *size_ost, int n_read)
{
	char	*for_free;

	if (*ost)
	{
		for_free = *ost;
		*ost = ft_strjoin1(*ost, buf, size_ost, n_read);
		free(for_free);
	}
	else
	{
		*size_ost = n_read;
		*ost = ft_strdup1(buf, *size_ost);
	}
}

void	ft_create_res(char **res, char *ost, int id_n, int *i)
{
	*res = (char *)malloc(id_n + 1);
	if (!res)
		return ;
	*i = 0;
	while (*i < id_n)
	{
		(*res)[*i] = ost[*i];
		*i = *i + 1;
	}
	(*res)[*i] = '\0';
}
