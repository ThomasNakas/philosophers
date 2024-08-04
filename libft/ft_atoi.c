/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:16:13 by tnakas            #+#    #+#             */
/*   Updated: 2024/06/07 04:14:54 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	p_or_n(char c);
int	ft_abs(int n);

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	atoi;

	i = 0;
	neg = 0;
	atoi = 0;
	while (ft_isspace(*(str + i)))
	{
		i++;
	}
	if (p_or_n(*(str + i)))
	{
		if (*(str + i) == '-')
			neg++;
		i++;
	}
	if (p_or_n(*(str + i)))
		return (0);
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		atoi = atoi * 10 + (*(str + i) - '0');
		i++;
	}
	return (((neg % 2) != 0) * (-1) * atoi + ((neg % 2) == 0) * atoi);
}

int	abs(int n)
{
	return ((n >= 0) * n + (n < 0) * (-1) * n);
}

int	p_or_n(char c)
{
	return ((c == '-' || c == '+') * 1);
}
