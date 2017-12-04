/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbooth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 14:59:05 by mbooth            #+#    #+#             */
/*   Updated: 2016/01/13 14:59:18 by mbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			is_just_bad(char *string)
{
	int				to_return;

	to_return = (string[0] == '\0'
					|| (string[0] == '-' && string[1] == '\0')
					|| (string[0] == '-' && !ft_isdigit(string[1]))
					|| (string[0] != '-' && !ft_isdigit(string[0])));
	return (to_return);
}

static void			set_is_negative(int *is_negative, char **string)
{
	if (**string == '-')
	{
		*is_negative = 1;
		(*string)++;
	}
	else
		*is_negative = 0;
}

int					ft_is_valid_int(char *string)
{
	long			number;
	int				is_negative;

	if (is_just_bad(string))
		return (0);
	set_is_negative(&is_negative, &string);
	number = 0;
	while (*string)
	{
		if (!ft_isdigit(*string))
			return (0);
		number = number * 10 + *string - '0';
		if ((is_negative && -number < INT_MIN)
			|| (!is_negative && number > INT_MAX))
			return (0);
		string++;
	}
	return (1);
}