/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:27:59 by sazelda           #+#    #+#             */
/*   Updated: 2021/10/11 18:07:38 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	ft_next(unsigned const char	*s, unsigned char		*d, size_t len)
{
	size_t	i;

	i = 0;
	if (d > s)
	{
		len--;
		while (len > 0)
		{
			d[len] = s[len];
			len--;
		}
		d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned const char	*s;
	unsigned char		*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (!len || d == s)
		return (dst);
	ft_next(s, d, len);
	return (dst);
}
