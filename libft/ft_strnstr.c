/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:17:18 by tnakas            #+#    #+#             */
/*   Updated: 2024/03/10 21:31:01 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sub, size_t l)
{
	size_t	i;
	size_t	j;

	if (!*sub)
		return ((char *)str);
	i = 0;
	while (str[i] && i < l)
	{
		j = 0;
		while (str[i + j] && sub[j] && i + j < l
			&& str[i + j] == sub[j])
			j++;
		if (!sub[j])
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
