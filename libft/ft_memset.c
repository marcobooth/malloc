/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbooth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 19:17:09 by mbooth            #+#    #+#             */
/*   Updated: 2018/02/03 19:17:09 by mbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memset(void *destination, int int_value, size_t len)
{
	size_t			i;
	unsigned char	*location;
	unsigned char	value;

	value = (unsigned char)int_value;
	location = (unsigned char*)destination;
	i = 0;
	while (i < len)
	{
		location[i] = value;
		i++;
	}
	return (destination);
}
