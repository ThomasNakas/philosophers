/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:53:36 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/24 12:35:07 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int	parsing(int argc, char **argv, t_table *t)
{
	if (argc < 5 || argc > 6)
	{
		printf("%s number_of_philosophers time_to_die \
		time_to_eat time_to_sleep [number_of_times_each\
		_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	t->n_of_philos = ft_p_atol(argv[1]);
	t->die = ft_p_atol(argv[2]) * 1000;
	t->eat = ft_p_atol(argv[3]) * 1000;
	t->sleep = ft_p_atol(argv[4]) * 1000;
	if (argc == 6)
		t->min_meals = ft_p_atol(argv[5]);
	else
		t->min_meals = -1;
	if (t->n_of_philos <= 0 || t->die == 1
		|| t->eat == 1 || t->sleep == 1
		|| t->min_meals == 0
		|| check_ms(t->die, t->eat, t->sleep))
		return (2);
	t->n_of_full_philos = 0;
	t->someone_died = 0;
	t->start_simulation = 0;
	t->stop_simulation = 0;
	return (0);
}