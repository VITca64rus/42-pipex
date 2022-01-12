/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:29:11 by sazelda           #+#    #+#             */
/*   Updated: 2021/10/18 13:57:01 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_real_len(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (start < ft_strlen(s) && i < len)
	{
		i++;
		start++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	end;
	char			*res;
	unsigned int	i;

	if (!s)
		return ((void *)0);
	len = ft_get_real_len(s, start, len);
	end = len + start;
	res = malloc(end - start + 1);
	if (!res)
		return ((void *)0);
	i = 0;
	while (start < end && start < ft_strlen(s))
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}
