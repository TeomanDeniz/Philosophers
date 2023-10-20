/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:55:07 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/12 16:55:09 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../../main_bonus.h" /*
#typedef t_ull;
*/
#include <sys/time.h> /*
# struct timeval;
#    int gettimeofday(struct timeval *, void *);
*/
/* **************************** [^] INCLUDES [^] **************************** */

t_ull
	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, (void *)0))
		return (0ULL);
	return ((time.tv_sec * 1000ULL) + (time.tv_usec / 1000));
}
