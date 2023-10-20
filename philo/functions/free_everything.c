/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:00:00 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/07 18:05:48 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../main.h" /*
#typedef t_program;
#typedef t_philo;
*/
#include <pthread.h> /*
#    int pthread_mutex_unlock(pthread_mutex_t *);
#    int pthread_mutex_destroy(pthread_mutex_t *);
*/
#include <stdlib.h> /*
#   void free(void *);
*/
/* **************************** [^] INCLUDES [^] **************************** */

/* *************************** [v] PROTOTYPES [v] *************************** */
static void	destroy_mutexs(t_program program);
/* *************************** [^] PROTOTYPES [^] *************************** */

void
	free_everything(t_program program, t_philo philo)
{
	register unsigned int	index;

	destroy_mutexs(program);
	index = program->args.number_of_philos + 1U;
	if (!!program->mutex.forks)
	{
		while (--index, !!index)
			if (!pthread_mutex_unlock(&program->mutex.forks[index]))
				pthread_mutex_destroy(&program->mutex.forks[index]);
		free(program->mutex.forks);
		program->mutex.forks = (void *)0;
	}
	if (!!philo)
		philo = (free(philo), (void *)0);
}

static void
	destroy_mutexs(t_program program)
{
	if (!pthread_mutex_unlock(&program->mutex.total_eaten_meal))
		pthread_mutex_destroy(&program->mutex.total_eaten_meal);
	if (!pthread_mutex_unlock(&program->mutex.print))
		pthread_mutex_destroy(&program->mutex.print);
	if (!pthread_mutex_unlock(&program->mutex.starving))
		pthread_mutex_destroy(&program->mutex.starving);
	if (!pthread_mutex_unlock(&program->mutex.wait_death))
		pthread_mutex_destroy(&program->mutex.wait_death);
	if (!pthread_mutex_unlock(&program->mutex.end))
		pthread_mutex_destroy(&program->mutex.end);
}
