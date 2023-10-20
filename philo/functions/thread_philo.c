/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:00:25 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/07 18:15:09 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../main.h" /*
#typedef t_philo;
#    int ft_msleep(useconds_t);
*/
#include "../philo_constants.h" /*
# define ERROR_MSG_15;
# define MSG_DEATH;
# define MSG_FORK_RIGHT;
# define MSG_FORK_LEFT;
# define MSG_EATING;
# define MSG_SLEEPING;
# define MSG_THINKING;
# define MSG_PRINT_MSG;
*/
#include <stdio.h> /*
#    int printf(char *, ...);
*/
#include <pthread.h> /*
#    int pthread_mutex_lock(pthread_mutex_t *);
#    int pthread_mutex_unlock(pthread_mutex_t *);
*/
#include <unistd.h> /*
#    int usleep(useconds_t usec);
*/
/* **************************** [^] INCLUDES [^] **************************** */

/* *************************** [v] PROTOTYPES [v] *************************** */
static void	eat_meal(t_philo philo);
static void	print_massage(t_philo philo, const char *string);
/* *************************** [^] PROTOTYPES [^] *************************** */

void
	*thread_philo(void *arg)
{
	t_philo	philo;

	philo = (t_philo) arg;
	if ((philo->id - 1) % 2 == 1)
		ft_msleep(2);
	pthread_mutex_lock(&philo->program->mutex.end);
	while (!philo->program->end)
	{
		pthread_mutex_unlock(&philo->program->mutex.end);
		if ((philo->program->args.eat_limit == philo->eaten_meal) && \
			!!philo->program->args.eat_limit)
			return ((void *)0);
		pthread_mutex_lock(&philo->program->mutex.total_eaten_meal);
		if ((philo->program->total_eaten_meal \
			/ philo->program->args.number_of_philos) \
			== philo->eaten_meal)
			eat_meal(philo);
		else
			pthread_mutex_unlock(&philo->program->mutex.total_eaten_meal);
		pthread_mutex_lock(&philo->program->mutex.end);
	}
	pthread_mutex_unlock(&philo->program->mutex.end);
	return ((void *)0);
}

static void
	eat_meal(t_philo philo)
{
	pthread_mutex_unlock(&philo->program->mutex.total_eaten_meal);
	if (!pthread_mutex_lock(philo->right_fork))
		print_massage(philo, MSG_FORK_RIGHT);
	if (philo->program->args.number_of_philos == 1)
	{
		pthread_mutex_lock(&philo->program->mutex.wait_death);
		return ;
	}
	if (!pthread_mutex_lock(philo->left_fork))
		print_massage(philo, MSG_FORK_LEFT);
	pthread_mutex_lock(&philo->program->mutex.total_eaten_meal);
	philo->program->total_eaten_meal++;
	pthread_mutex_unlock(&philo->program->mutex.total_eaten_meal);
	philo->eaten_meal++;
	print_massage(philo, MSG_EATING);
	ft_msleep(philo->program->args.time_to_eat);
	pthread_mutex_lock(&philo->program->mutex.starving);
	philo->starving = philo->program->args.time_to_die;
	pthread_mutex_unlock(&philo->program->mutex.starving);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_massage(philo, MSG_SLEEPING);
	ft_msleep(philo->program->args.time_to_sleep);
	print_massage(philo, MSG_THINKING);
}

static void
	print_massage(t_philo philo, const char *string)
{
	pthread_mutex_lock(&philo->program->mutex.end);
	if (!philo->program->end)
	{
		pthread_mutex_lock(&philo->program->mutex.print);
		printf(MSG_PRINT_MSG, get_time() - philo->program->start_time, \
			philo->id, string);
		pthread_mutex_unlock(&philo->program->mutex.print);
	}
	pthread_mutex_unlock(&philo->program->mutex.end);
}
