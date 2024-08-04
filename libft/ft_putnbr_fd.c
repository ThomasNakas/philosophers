/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 09:00:33 by tnakas            #+#    #+#             */
/*   Updated: 2024/03/08 14:38:46 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nl;

	nl = n;
	if (nl == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (nl < 0)
	{
		ft_putchar_fd('-', fd);
		nl = -1 * nl;
	}
	if (nl > 9)
		ft_putnbr_fd(nl / 10, fd);
	ft_putchar_fd(nl % 10 + '0', fd);
}
