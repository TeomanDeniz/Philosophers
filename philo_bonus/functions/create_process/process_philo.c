/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:17:15 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/12 17:17:16 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../../main_bonus.h" /*
#typedef t_philo;
#    int ft_msleep(useconds_t);
#   void sem_set_end(t_philo);
#   void *update_starving(void *);
#   void *check_end(void *);
#   void *sub_total_eaten_meal(void *);
#   void print_massage(t_philo, const char *);
#   void sem_sub_total_eaten_meal(t_philo);
#    ull get_time(void);
*/
#include "../../philo_constants.h" /*
# define ERROR_MSG_18;
# define ERROR_MSG_19;
# define ERROR_MSG_21;
# define ERROR_MSG_23;
# define ERROR_MSG_24;
# define MSG_DEATH;
# define MSG_FORK_RIGHT;
# define MSG_FORK_LEFT;
# define MSG_EATING;
# define MSG_SLEEPING;
# define MSG_THINKING;
*/
#include <stdio.h> /*
#    int printf(char *, ...);
*/
#include <sys/wait.h> /*
#  pid_t waitpid(pid_t, int *, int);
*/
#include <pthread.h> /*
#typedef pthread_t;
#    int pthread_mutex_lock(pthread_mutex_t *);
#    int pthread_mutex_unlock(pthread_mutex_t *);
#    int pthread_mutex_destroy(pthread_mutex_t *);
#    int pthread_mutex_init(pthread_mutex_t *, pthread_mutexattr_t *);
#    int pthread_create(pthread_t *, pthread_attr_t *, void *(*)(void*), \
void *);
#    int pthread_join(pthread_t, void **);
*/
#include <stdlib.h> /*
#   void exit(int);
*/
#include <semaphore.h> /*
#    int sem_wait(sem_t *);
#    int sem_post(sem_t *);
*/
/* **************************** [^] INCLUDES [^] **************************** */

/* ***************************** [v] STRUCTS [v] **************************** */
typedef struct s_threads
{
	pthread_t	updater_thread;
	pthread_t	update_starving;
	pthread_t	sub_total_eaten_meal;
}	t_threads;
/* ***************************** [^] STRUCTS [^] **************************** */

/* *************************** [v] PROTOTYPES [v] *************************** */
static void	eat_meal(t_philo philo);
static char	thread_error(t_philo philo, const char *msg, t_threads thread);
static void	philo_setup(t_philo philo, t_threads *thread);
/* *************************** [^] PROTOTYPES [^] *************************** */

void
	process_philo(t_philo philo)
{
	t_threads	thread;

	philo_setup(philo, &thread);
	pthread_mutex_lock(&philo->mutex_end);
	while (!philo->program->end)
	{
		pthread_mutex_unlock(&philo->mutex_end);
		if ((philo->program->args.eat_limit == philo->eaten_meal) && \
			!!philo->program->args.eat_limit)
			break ;
		pthread_mutex_lock(&philo->mutex_total_eaten_meal);
		if (((philo->program->total_eaten_meal) \
			/ philo->program->args.number_of_philos) == philo->eaten_meal)
			eat_meal(philo);
		else
			pthread_mutex_unlock(&philo->mutex_total_eaten_meal);
		pthread_mutex_lock(&philo->mutex_end);
	}
	exit(0);
}

static void
	philo_setup(t_philo philo, t_threads *thread)
{
	if (pthread_mutex_init(&philo->mutex_starving, (void *)0))
		exit(thread_error(philo, ERROR_MSG_21, *thread));
	if (pthread_mutex_init(&philo->mutex_end, (void *)0))
		exit(thread_error(philo, ERROR_MSG_23, *thread));
	if (pthread_mutex_init(&philo->mutex_total_eaten_meal, (void *)0))
		exit(thread_error(philo, ERROR_MSG_24, *thread));
	if (pthread_create(&thread->updater_thread, (void *)0, check_end, \
		(void *)philo))
		exit(thread_error(philo, ERROR_MSG_18, *thread));
	if (pthread_create(&thread->update_starving, (void *)0, update_starving, \
		(void *)philo))
		exit(thread_error(philo, ERROR_MSG_19, *thread));
	if (pthread_create(&thread->sub_total_eaten_meal, (void *)0, \
		sub_total_eaten_meal, (void *)philo))
		exit(thread_error(philo, ERROR_MSG_20, *thread));
}

static void
	eat_meal(t_philo philo)
{
	pthread_mutex_unlock(&philo->mutex_total_eaten_meal);
	sem_wait(philo->right_fork);
	print_massage(philo, MSG_FORK_RIGHT);
	sem_wait(philo->left_fork);
	print_massage(philo, MSG_FORK_LEFT);
	sem_sub_total_eaten_meal(philo);
	philo->eaten_meal++;
	print_massage(philo, MSG_EATING);
	ft_msleep(philo->program->args.time_to_eat);
	pthread_mutex_lock(&philo->mutex_starving);
	philo->starving = get_time();
	pthread_mutex_unlock(&philo->mutex_starving);
	sem_post(philo->right_fork);
	sem_post(philo->left_fork);
	print_massage(philo, MSG_SLEEPING);
	ft_msleep(philo->program->args.time_to_sleep);
	print_massage(philo, MSG_THINKING);
}

static char
	thread_error(t_philo philo, const char *msg, t_threads thread)
{
	sem_set_end(philo);
	printf("%s\n", msg);
	pthread_join(thread.updater_thread, (void *)0);
	pthread_join(thread.update_starving, (void *)0);
	pthread_join(thread.sub_total_eaten_meal, (void *)0);
	if (!pthread_mutex_unlock(&philo->mutex_starving))
		pthread_mutex_destroy(&philo->mutex_starving);
	if (!pthread_mutex_unlock(&philo->mutex_end))
		pthread_mutex_destroy(&philo->mutex_end);
	if (!pthread_mutex_unlock(&philo->mutex_total_eaten_meal))
		pthread_mutex_destroy(&philo->mutex_total_eaten_meal);
	return (1);
}
