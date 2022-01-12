/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:28:58 by sazelda           #+#    #+#             */
/*   Updated: 2021/10/18 14:02:23 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *havstack, const char *needle, size_t len)
{
	size_t	pos;
	size_t	i;

	if (!*needle)
		return ((char *)havstack);
	pos = 0;
	while (havstack[pos] != '\0' && (size_t)pos < len)
	{
		if (havstack[pos] == needle[0])
		{
			i = 1;
			while (needle[i] != '\0' && havstack[pos + i] == needle[i] \
					&& (size_t)(pos + i) < len)
				++i;
			if (needle[i] == '\0')
				return ((char *)&havstack[pos]);
		}
		++pos;
	}
	return (0);
}
