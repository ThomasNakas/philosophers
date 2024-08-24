/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 03:36:17 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/24 14:04:14 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	big_sixty_ms(int a)
{
	return (a < 60);
}

int	check_ms(int x, int y, int z)
{
	return (big_sixty_ms(x)
		|| big_sixty_ms(y) 
		|| big_sixty_ms(z));
}

void	safe_destroy(t_table *table, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		pthread_mutex_destroy(&table->forks[i]);
}

void	ft_sleep(long long routine_time)
{
	long long	start;

	start = get_time_ms();
	while (get_time_ms() - start < routine_time)
		usleep(200);
}