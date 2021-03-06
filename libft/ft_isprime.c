/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 16:45:05 by szheng            #+#    #+#             */
/*   Updated: 2018/07/15 16:47:18 by szheng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isprime(unsigned int n)
{
	unsigned int i;

	i = 2;
	if (n == 2 || n == 3)
		return (1);
	while ((i * i) <= n && i <= 46340)
	{
		if (n % i == 0)
			return (0);
		i++;
	}
	return (1);
}
