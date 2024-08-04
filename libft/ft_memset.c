/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:16:48 by tnakas            #+#    #+#             */
/*   Updated: 2024/03/10 14:05:55 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b_filled, int b_value, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
		*(unsigned char *)(b_filled + i) = (unsigned char)b_value;
	return (b_filled);
}
