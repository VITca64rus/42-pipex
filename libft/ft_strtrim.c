/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:29:04 by sazelda           #+#    #+#             */
/*   Updated: 2021/10/11 17:50:40 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_in(char a, char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == a)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	at_end;
	unsigned int	at_start;
	char			*res;

	at_start = 0;
	if (!s1)
		return ((void *)0);
	if (ft_strlen(s1) == 0)
		return (ft_substr(s1, 0, 0));
	while (check_in(s1[at_start], (char *)set) == 1 && s1[at_start])
		at_start++;
	at_end = 0;
	i = ft_strlen(s1) - 1;
	while (check_in(s1[i], (char *)set) == 1 && i > 0)
	{
		at_end++;
		i--;
	}
	res = ft_substr(s1, at_start, ft_strlen(s1) - at_end - at_start);
	return (res);
}
