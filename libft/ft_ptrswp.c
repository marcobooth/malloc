/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrswp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbooth <mbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/30 15:17:06 by mbooth            #+#    #+#             */
/*   Updated: 2015/01/30 15:23:41 by mbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ptrswp(void **ptr1, void **ptr2)
{
	void	*temporary;

	temporary = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temporary;
}
