/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:54:57 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/12 16:54:58 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../../main_bonus.h" /*
#typedef t_philo;
#    ull get_time(void);
*/
#include <unistd.h> /*
#typedef useconds_t;
#    int usleep(useconds_t);
*/
#include <pthread.h> /*
#    int pthread_mutex_lock(pthread_mutex_t *);
#    int pthread_mutex_unlock(pthread_mutex_t *);
*/
/* **************************** [^] INCLUDES [^] **************************** */

int
	ft_msleep(useconds_t time)
{
	register unsigned long long	start;

	start = get_time();
	if (!start)
		return (1);
	while (((get_time() - start) < time))
		usleep(time / 10);
	return (0);
}
