/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_total_eaten_meal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:50:46 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/12 15:50:47 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../../../main_bonus.h" /*
#typedef t_philo;
*/
#include <semaphore.h> /*
#    int sem_wait(sem_t *);
*/
#include <pthread.h> /*
#    int pthread_mutex_lock(pthread_mutex_t *);
#    int pthread_mutex_unlock(pthread_mutex_t *);
*/
/* **************************** [^] INCLUDES [^] **************************** */

void
	*sub_total_eaten_meal(void *arg)
{
	t_philo	philo;

	philo = (t_philo) arg;
	pthread_mutex_lock(&philo->mutex_end);
	while (!philo->program->end)
	{
		pthread_mutex_unlock(&philo->mutex_end);
		sem_wait(philo->program->sem.turns[(philo->id - 1U)]);
		pthread_mutex_lock(&philo->mutex_total_eaten_meal);
		philo->program->total_eaten_meal++;
		pthread_mutex_unlock(&philo->mutex_total_eaten_meal);
		pthread_mutex_lock(&philo->mutex_end);
	}
	pthread_mutex_unlock(&philo->mutex_end);
	return ((void *)0);
}
