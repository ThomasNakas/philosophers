/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:51:41 by tnakas            #+#    #+#             */
/*   Updated: 2024/03/10 18:23:45 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen(int n)
{
	int	i;

	i = 0;
	if (n < 1)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

long int	ft_abs(long int n)
{
	int	neg;

	neg = (n < 0);
	return ((-1) * neg * n + !neg * n);
}

char	*ft_nbr_malloc(int n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	int				sign;
	int				len;
	char			*str;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = ft_nbrlen(n);
	str = ft_nbr_malloc(len);
	if (!str)
		return (NULL);
	n = ft_abs(n);
	str[len] = '\0';
	nbr = ft_abs(n);
	while (len--)
	{
		str[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
