/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 03:36:17 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/25 06:31:46 by tnakas           ###   ########.fr       */
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

void	print_thread_routine(t_philo *philo, t_print PRINT)
{
	if (should_stop_simulation(philo->table))
		return ;
	pthread_mutex_lock(&philo->table->thread_print);
	print_with_enum(philo, PRINT);
	pthread_mutex_unlock(&philo->table->thread_print);
}

void	ft_sleep(long long routine_time)
{
	long long	start;

	start = get_time_ms();
	while (get_time_ms() - start < routine_time)
		usleep(200);
}
