/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:28:22 by sazelda           #+#    #+#             */
/*   Updated: 2022/01/11 13:35:09 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_count_word(char const *s, char c)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 0;
	if (ft_strlen(s) == 0)
		return (0);
	while (s[i] == c && c != '\0')
		i++;
	if (i == 0 && s[i] != c)
	{
		res++;
		i++;
	}
	while (s[i])
	{
		if ((s[i - 1] == c && s[i] != c))
			res++;
		i++;
	}
	return (res);
}

static unsigned int	ft_get_id_next_word(const char *s, char c, unsigned int *i)
{
	while (s[*i] == c)
		*i = *i + 1;
	if (*i == 0 && s[*i] != c)
		return (*i);
	while (s[*i])
	{
		if ((s[*i - 1] == c && s[*i] != c))
			return (*i);
		*i = *i + 1;
	}
	return (ft_strlen(s) + 1);
}

static unsigned int	ft_get_length_word(const char *s, char c, unsigned int *i)
{
	unsigned int	res;

	res = 0;
	while (s[*i] != c && s[*i] != '\0')
	{
		*i = *i + 1;
		res++;
	}
	return (res);
}

static int	ft_clean_all(char **res, unsigned int j)
{
	if (!res[j])
	{
		j--;
		while (j >= 0)
		{
			free(res[j]);
		}
		free(res);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	count_word;
	char			**res;
	unsigned int	i;
	unsigned int	j;

	if (!s)
		return ((void *)0);
	count_word = ft_count_word(s, c);
	res = (char **)malloc(sizeof(char *) * (count_word + 1));
	if (!res)
		return ((void *)0);
	i = 0;
	j = 0;
	while (j < count_word)
	{
		res[j] = ft_substr(s, ft_get_id_next_word(s, c, &i), \
							ft_get_length_word(s, c, &i));
		if (ft_clean_all(res, j) == 0)
			return ((void *)0);
		j++;
	}
	res[j] = ((void *)0);
	return (res);
}
