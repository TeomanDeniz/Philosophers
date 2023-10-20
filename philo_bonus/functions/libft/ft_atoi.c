/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:54:48 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/12 16:54:49 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int
	ft_atoi(const char *string)
{
	register int	index;
	register char	sign;
	int				result;

	index = 0;
	sign = 0;
	result = 0;
	while (string[index] == ' ' || (string[index] >= 9 && string[index] <= 13))
		++index;
	if (string[index] == '+' || string[index] == '-')
	{
		if (string[index] == '-')
			sign = 1;
		++index;
	}
	--index;
	while (++index, string[index] >= '0' && string[index] <= '9')
		result = (result * 10) + (string[index] & 15);
	if (sign)
		result = (++result, ~result);
	return (result);
}
