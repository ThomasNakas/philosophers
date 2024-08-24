/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:44 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/23 17:46:56 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
//percision in ms
long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) +(tv.tv_usec / 1000));
}

long	ft_p_atol(char *str)
{
	long long	nbr;
	int			i;

	i = -1;
	nbr = 0;
	while (str[++i] && ft_isspace(str[i]))
		;
	if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		nbr *= 10;
		nbr += str[i] - '0';
		i++;
	}
	if (str[i] != '\0' || nbr > (long long)INT_MAX)
		return (-1);
	return (nbr);
}

//-----------------------MAYBE CHANGE-----------------------------
void	print_status(t_philo *philo,char *status)
{
	printf("%lld %d %s\n", get_time_ms() - philo->table->start_tv,
		philo-> id, status);
}

//-----------------------MAYBE CHANGE------------------------------
void	print_with_enum(t_philo *philo, t_print mes)
{
	if (mes == FORK)
		print_status(philo, "has taken a fork");
	else if (mes == EAT)
		print_status(philo, "is eating");
	else if (mes == SLEEP)
		print_status(philo, "is sleeping");
	else if (mes == THINK)
		print_status(philo, "is_thinking");
	else
		print_status(philo, "died");
}