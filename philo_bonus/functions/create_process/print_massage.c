/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_massage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:20:44 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/12 18:20:46 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../../main_bonus.h" /*
#typedef t_philo;
#   void sem_set_end(t_philo);
#    ull get_time(void);
*/
#include "../../philo_constants.h" /*
# define ERROR_MSG_14;
# define MSG_PRINT_MSG;
*/
#include <stdio.h> /*
#    int printf(char *, ...);
*/
#include <pthread.h> /*
#    int pthread_mutex_lock(pthread_mutex_t *);
#    int pthread_mutex_unlock(pthread_mutex_t *);
*/
#include <semaphore.h> /*
#    int sem_wait(sem_t *);
#    int sem_post(sem_t *);
*/
/* **************************** [^] INCLUDES [^] **************************** */

void
	print_massage(t_philo philo, const char *string)
{
	pthread_mutex_lock(&philo->mutex_end);
	if (!philo->program->end)
	{
		pthread_mutex_unlock(&philo->mutex_end);
		sem_wait(philo->program->sem.print);
		printf(MSG_PRINT_MSG, get_time() - philo->program->start_time, \
			philo->id, string);
		sem_post(philo->program->sem.print);
	}
	else
		pthread_mutex_unlock(&philo->mutex_end);
}
