/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:34 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/23 22:38:49 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_table(int argc, char **argv, t_table *table)
{
	int	i;
	int	j;

	parsing(argc, argv, table);
	protected_init_from_print_to_change_die(table);
	protected_init_change_of_full(table);
	protected_malloc_arr_philos(table);
	protected_malloc_arr_forks(table);
	protected_init_arr_forks(table);
	if (table->n_of_full_philos == 1)
		protected_create_arr_philos(table);
	else
		init_philos(table);
	table->start_tv = get_time_ms();
	pthread_mutex_lock(&table->thread_supervisor);
	table->start_simulation = 1;
	pthread_mutex_unlock(&table->thread_supervisor);
}

int	init_philos(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->n_of_philos)
	{
		protected_create_arr_philos(t, i);
		t->arr_philos[i].id = i + 1;
		t->arr_philos[i].meals = 0;
		t->arr_philos[i].left_fork = t->forks[i];
		t->arr_philos[i].right_fork
			= t->forks[t->arr_philos[i].id % t->n_of_philos];
		t->arr_philos[i].table = t;
		protected_mutex_init(t, i);
	}
}

int	init_supervisor(int argc, char *argv, t_supervisor *s)
{

	if (init_table(argc, argv, s->table))
		return (1);
	if (pthread_mutex_create(&s->super, NULL, supervisor, NULL))
		protected_mutex_init_supervisor(s);
}
