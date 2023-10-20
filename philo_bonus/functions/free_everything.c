/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:37:33 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/12 16:37:36 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../main_bonus.h" /*
#typedef t_program;
#typedef t_philo;
*/
#include <semaphore.h> /*
#typedef sem_t;
#    int sem_close(sem_t *);
#    int sem_unlink(const char *);
*/
#include <stdlib.h> /*
#   void free(void *);
*/
#include <pthread.h> /*
#    int pthread_mutex_unlock(pthread_mutex_t *);
#    int pthread_mutex_destroy(pthread_mutex_t *);
*/
/* **************************** [^] INCLUDES [^] **************************** */

/* *************************** [v] PROTOTYPES [v] *************************** */
static void	sem_close_fork(unsigned int index, sem_t *sem);
static void	sem_close_turn(unsigned int index, sem_t *sem);
static void	free_sem(sem_t *sem, const char *link);
static void	close_sems(t_program program);
/* *************************** [^] PROTOTYPES [^] *************************** */

void
	free_everything(t_program program, t_philo philo)
{
	register unsigned int	index;

	close_sems(program);
	index = program->args.number_of_philos + 1U;
	if (!!program->sem.forks)
	{
		while (--index, !!index)
			if (!!program->sem.forks[index])
				sem_close_fork(index, program->sem.forks[index]);
		free(program->sem.forks);
		program->sem.forks = (void *)0;
	}
	index = program->args.number_of_philos + 1U;
	if (!!program->sem.turns)
	{
		while (--index, !!index)
			if (!!program->sem.turns[index])
				sem_close_turn(index, program->sem.turns[index]);
		free(program->sem.turns);
		program->sem.turns = (void *)0;
	}
	if (!!philo)
		philo = (free(philo), (void *)0);
}

static void
	close_sems(t_program program)
{
	if (!!program->sem.total_eaten_meal)
		free_sem(program->sem.total_eaten_meal, "/philo_total_eaten_meal");
	if (!!program->sem.print)
		free_sem(program->sem.print, "/philo_print");
	if (!!program->sem.set_end)
		free_sem(program->sem.set_end, "/philo_set_end");
	if (!!program->sem.philo_starved)
		free_sem(program->sem.philo_starved, "/philo_philo_starved");
	if (!!program->sem.all_forks_ready)
		free_sem(program->sem.all_forks_ready, "/philo_all_forks_ready");
}

static void
	sem_close_fork(unsigned int index, sem_t *sem)
{
	char	edited_string[15];

	edited_string[0] = '/';
	edited_string[1] = 'p';
	edited_string[2] = 'h';
	edited_string[3] = 'i';
	edited_string[4] = 'l';
	edited_string[5] = 'o';
	edited_string[6] = '_';
	edited_string[7] = 'f';
	edited_string[8] = 'o';
	edited_string[9] = 'r';
	edited_string[10] = 'k';
	edited_string[11] = '0' + (index / 100);
	edited_string[12] = '0' + (index / 10) % 10;
	edited_string[13] = '0' + (index % 10);
	edited_string[14] = 0;
	free_sem(sem, edited_string);
}

static void
	sem_close_turn(unsigned int index, sem_t *sem)
{
	char	edited_string[15];

	edited_string[0] = '/';
	edited_string[1] = 'p';
	edited_string[2] = 'h';
	edited_string[3] = 'i';
	edited_string[4] = 'l';
	edited_string[5] = 'o';
	edited_string[6] = '_';
	edited_string[7] = 't';
	edited_string[8] = 'u';
	edited_string[9] = 'r';
	edited_string[10] = 'n';
	edited_string[11] = '0' + (index / 100);
	edited_string[12] = '0' + (index / 10) % 10;
	edited_string[13] = '0' + (index % 10);
	edited_string[14] = 0;
	free_sem(sem, edited_string);
}

static void
	free_sem(sem_t *sem, const char *link)
{
	sem_close(sem);
	sem_unlink(link);
	sem = (void *)0;
}
