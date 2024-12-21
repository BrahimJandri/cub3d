/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reddamss <damssi.art@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:25:44 by reddamss          #+#    #+#             */
/*   Updated: 2023/12/01 14:40:22 by reddamss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter(int n)
{
	int	num;

	num = 0;
	while (n)
	{
		n /= 10;
		num++;
	}
	if (num == 0)
		return (1);
	return (num);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		num_len;
	int		sign;

	sign = n < 0;
	num_len = counter(n) + sign;
	res = (char *)malloc(sizeof(char) * num_len + 1);
	if (!res)
		return (NULL);
	res[num_len] = '\0';
	if (sign)
	{
		*res = '-';
		res[--num_len] = -(n % 10) + 48;
		n = -(n / 10);
	}
	while (num_len-- - sign)
	{
		res[num_len] = n % 10 + 48;
		n /= 10;
	}
	return (res);
}
