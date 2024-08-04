/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:17:05 by tnakas            #+#    #+#             */
/*   Updated: 2024/03/17 00:35:46 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	dest_l;
	size_t	src_l;
	size_t	cat_l;

	dest_l = ft_strlen(dest);
	src_l = ft_strlen(src);
	cat_l = size - dest_l - 1;
	if (size <= dest_l)
		return (src_l + size);
	if (cat_l > src_l)
		cat_l = src_l;
	if (cat_l != 0)
	{
		i = 0;
		while (*(src + i) && i < cat_l)
		{
			*(dest + dest_l + i) = *(src + i);
			i++;
		}
		*(dest + dest_l + i) = '\0';
	}
	return (dest_l + src_l);
}
