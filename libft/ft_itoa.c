/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazelda <sazelda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:26:54 by sazelda           #+#    #+#             */
/*   Updated: 2021/10/11 17:34:40 by sazelda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	ft_get_len(int n)
{
	unsigned int	res;

	res = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = n * (-1);
		res++;
	}
	while (n > 0)
	{
		res++;
		n = n / 10;
	}
	return (res);
}

static char	*ft_create_zero(void)
{
	char	*res;

	res = (char *)malloc(2);
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

static void	ft_work_with_minus(char	*res, int *n, unsigned int *len)
{
	res[0] = '-';
	if (*n != -2147483648)
		*n = *n * (-1);
	else
	{
		res[10] = '8';
		*n = *n / 10;
		*n = *n * (-1);
		*len = *len - 1;
	}
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	len;

	if (n == 0)
		return (ft_create_zero());
	len = ft_get_len(n);
	res = (char *)malloc(len + 1);
	if (!res)
		return ((void *)0);
	res[len] = '\0';
	if (n < 0)
		ft_work_with_minus(res, &n, &len);
	while (n > 0)
	{
		res[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (res);
}
