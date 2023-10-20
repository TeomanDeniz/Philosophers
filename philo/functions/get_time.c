/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:00:15 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/07 17:00:15 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include <sys/time.h> /*
# struct timeval;
#    int gettimeofday(struct timeval *, void *);
*/
/* **************************** [^] INCLUDES [^] **************************** */

unsigned long long
	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, (void *)0))
		return (0ULL);
	return ((time.tv_sec * 1000ULL) + (time.tv_usec / 1000));
}
