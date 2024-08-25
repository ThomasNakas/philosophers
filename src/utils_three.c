/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:38:17 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/25 07:17:59 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(char c)
{
	return ((((c >= 9) && (c <= 13)) || c == ' ' || c == '\n') * 1);
}

long long	max(long long a, long long b)
{
	return (a * (a >= b) + b * (a < b));
}
