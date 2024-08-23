/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 03:36:17 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/23 16:46:13 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	big_sixty_ms(int a)
{
	return (a >= 60000);
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