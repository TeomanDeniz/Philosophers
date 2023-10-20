/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_starving.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:02:15 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/12 15:02:16 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../../../main_bonus.h" /*
#typedef t_philo;
#typedef t_program;
#   void sem_set_end(t_philo);
#    ull get_time(void);
#    int ft_msleep(useconds_t);
*/
#include "../../../philo_constants.h" /*
# define MSG_DEATH;
*/
#include <stdio.h> /*
#    int printf(char *, ...);
*/
#include <semaphore.h> /*
#    int sem_wait(sem_t *);
#    int sem_post(sem_t *);
*/
#include <stdlib.h> /*
#   void exit(int);
*/
#include <pthread.h> /*
#    int pthread_mutex_lock(pthread_mutex_t *);
#    int pthread_mutex_unlock(pthread_mutex_t *);
*/
/* **************************** [^] INCLUDES [^] **************************** */

/* *************************** [v] PROTOTYPES [v] *************************** */
static void	philo_starved(t_philo philo);
/* *************************** [^] PROTOTYPES [^] *************************** */

void
	*update_starving(void *arg)
{
	t_philo	philo;

	philo = (t_philo) arg;
	pthread_mutex_lock(&philo->mutex_end);
	while (!philo->program->end)
	{
		pthread_mutex_unlock(&philo->mutex_end);
		ft_msleep(1);
		pthread_mutex_lock(&philo->mutex_starving);
		if ((get_time() - philo->starving) > philo->program->args.time_to_die)
		{
			sem_wait(philo->program->sem.print);
			pthread_mutex_unlock(&philo->mutex_starving);
			sem_post(philo->program->sem.set_end);
			sem_wait(philo->program->sem.philo_starved);
			philo_starved(philo);
		}
		else
			pthread_mutex_unlock(&philo->mutex_starving);
		pthread_mutex_lock(&philo->mutex_end);
	}
	pthread_mutex_unlock(&philo->mutex_end);
	return ((void *)0);
}

static void
	philo_starved(t_philo philo)
{
	t_program	program;

	program = philo->program;
	pthread_mutex_lock(&philo->mutex_end);
	if (!program->end)
	{
		pthread_mutex_unlock(&philo->mutex_end);
		printf(MSG_DEATH, get_time() - program->start_time, philo->id);
	}
	else
		pthread_mutex_unlock(&philo->mutex_end);
	exit(0);
}
