/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:00:19 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/07 18:05:31 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../main.h" /*
#typedef t_program;
#typedef t_philo;
#    int ft_msleep(useconds_t);
*/
#include "../philo_constants.h" /*
# define MSG_DEATH;
*/
#include <pthread.h> /*
#    int pthread_mutex_lock(pthread_mutex_t *);
#    int pthread_mutex_unlock(pthread_mutex_t *);
*/
#include <stdio.h> /*
#    int printf(char *, ...);
*/
#include <unistd.h> /*
#    int usleep(useconds_t usec);
*/
/* **************************** [^] INCLUDES [^] **************************** */

/* *************************** [v] PROTOTYPES [v] *************************** */
static void	philo_starved(t_philo philo);
static void	philo_events(t_philo philo, t_program program);
/* *************************** [^] PROTOTYPES [^] *************************** */

void
	*kill_checker(void *arg)
{
	t_philo					philo;
	t_program				program;

	philo = (t_philo) arg;
	program = (t_program) philo->program;
	pthread_mutex_lock(&program->mutex.end);
	while (!program->end)
	{
		pthread_mutex_unlock(&program->mutex.end);
		ft_msleep(1);
		philo_events(philo, program);
		pthread_mutex_lock(&program->mutex.end);
	}
	pthread_mutex_unlock(&program->mutex.end);
	return ((void *) 0);
}

static void
	philo_events(t_philo philo, t_program program)
{
	register unsigned int	index;

	index = 4294967295U;
	while (++index, index < program->args.number_of_philos)
	{
		pthread_mutex_lock(&program->mutex.starving);
		if (philo[index].starving != 0U)
			philo[index].starving--;
		if (philo[index].starving == 0U)
		{
			pthread_mutex_lock(&philo->program->mutex.end);
			program->end = 1;
			philo_starved(&philo[index]);
			pthread_mutex_unlock(&program->mutex.end);
			return ;
		}
		else
			pthread_mutex_unlock(&program->mutex.starving);
	}
}

static void
	philo_starved(t_philo philo)
{
	t_program	program;

	program = philo->program;
	pthread_mutex_unlock(&program->mutex.starving);
	program->death = 1;
	pthread_mutex_lock(&program->mutex.print);
	printf(MSG_DEATH, get_time() - program->start_time, philo->id);
	pthread_mutex_unlock(&program->mutex.print);
	if (program->args.number_of_philos == 1)
		pthread_mutex_unlock(&program->mutex.wait_death);
}
