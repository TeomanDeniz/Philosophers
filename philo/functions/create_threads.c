/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:59:50 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/07 17:38:01 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../main.h" /*
#typedef t_program;
#typedef t_philo;
# struct s_philo;
#   void *thread_philo(void *);
#   void *kill_checker(void *);
#   void free_everything(t_program, t_philo);
*/
#include "../philo_constants.h" /*
# define ERROR_MSG_12;
# define ERROR_MSG_13;
# define MSG_END;
*/
#include <pthread.h> /*
#    int pthread_create(pthread_t *, pthread_attr_t *, void *(*)(void*), \
void *);
#    int pthread_join(pthread_t, void **);
#    int pthread_mutex_destroy(pthread_mutex_t *);
#    int pthread_mutex_lock(pthread_mutex_t *);
#    int pthread_mutex_unlock(pthread_mutex_t *);
*/
#include <stdlib.h> /*
#   void *malloc(int);
#   void free(void *);
*/
#include <stdio.h> /*
#    int printf(char *, ...);
*/
/* **************************** [^] INCLUDES [^] **************************** */

/* *************************** [v] PROTOTYPES [v] *************************** */
static t_philo	create_philo_struct(t_program program);
static void		join_all_threads(t_program program, t_philo philo);
static char		create_kill_checker(t_philo philo);
/* *************************** [^] PROTOTYPES [^] *************************** */

void
	create_threads(t_program program)
{
	register unsigned int	ecx;
	t_philo					philo;

	ecx = 4294967295U;
	philo = create_philo_struct(program);
	if (!philo || create_kill_checker(philo))
		return ;
	while (++ecx, ecx < program->args.number_of_philos)
	{
		if (pthread_create(&philo[ecx].this, (void *)0, thread_philo, \
			(void *)&philo[ecx]))
		{
			program->error = (printf(ERROR_MSG_13, ecx), 1);
			while (--ecx, ecx)
				pthread_join(philo[ecx].this, (void *)0);
			pthread_join(program->kill_checker, (void *)0);
			free_everything(program, philo);
			return ;
		}
	}
	join_all_threads(program, philo);
	free_everything(program, philo);
}

static t_philo
	create_philo_struct(t_program program)
{
	register unsigned int	index;
	t_philo					philo;

	philo = (t_philo) malloc(sizeof(struct s_philo) * \
		(program->args.number_of_philos + 1));
	if (!philo)
	{
		free_everything(program, (void *)0);
		return (printf(ERROR_MSG_12), (void *)0);
	}
	index = 4294967295U;
	while (++index, index < program->args.number_of_philos)
	{
		philo[index].id = (index + 1U);
		philo[index].starving = program->args.time_to_die;
		philo[index].left_fork = &program->mutex.forks[(index + 1U) \
			% program->args.number_of_philos];
		philo[index].right_fork = &program->mutex.forks[index];
		philo[index].eaten_meal = 0ULL;
		philo[index].program = program;
	}
	return (philo);
}

static void
	join_all_threads(t_program program, t_philo philo)
{
	register unsigned int	index;

	index = 4294967295U;
	while (++index, index < program->args.number_of_philos)
		pthread_join(philo[index].this, (void *)0);
	pthread_mutex_lock(&program->mutex.end);
	program->end = 1;
	pthread_mutex_unlock(&program->mutex.end);
	pthread_join(program->kill_checker, (void *)0);
	printf(MSG_END);
}

static char
	create_kill_checker(t_philo philo)
{
	if (!philo)
		return (1);
	if (pthread_create(&philo->program->kill_checker, (void *)0, kill_checker, \
		(void *)philo))
	{
		free_everything(philo->program, philo);
		return (1);
	}
	return (0);
}
