/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:02:37 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/24 12:22:51 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_table			table;
	t_supervisor	s;

	init_supervisor(argc, argv, &s);
	
	return (printf("%d\n", (int)ft_p_atol(argv[1])));
}
