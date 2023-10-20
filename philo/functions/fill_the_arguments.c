/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:59:55 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/07 18:05:58 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../philo_constants.h" /*
# define ERROR_MSG_5;
# define ERROR_MSG_6;
# define ERROR_MSG_7;
# define ERROR_MSG_8;
# define ERROR_MSG_9;
# define ERROR_MSG_10;
# define ERROR_MSG_11;
# define ERROR_MSG_16;
# define ERROR_MSG_17;
# define ERROR_MSG_16;
# define ERROR_MSG_17;
# define ERROR_MSG_19;
# define ERROR_MSG_18;
# define WARNING_MSG;
*/
#include "../main.h" /*
#typedef t_program;
#    int ft_atoi(char *);
#   void free_everything(t_program, t_philo);
*/
#include <pthread.h> /*
#typedef pthread_mutex_t;
#    int pthread_mutex_init(pthread_mutex_t *, pthread_mutexattr_t *);
#    int pthread_mutex_destroy(pthread_mutex_t *);
#    int pthread_mutex_lock(pthread_mutex_t *);
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
static char	check_any_problem(t_program program);
static char	create_forks(t_program program);
static char	open_mutexs(t_program program);
/* *************************** [^] PROTOTYPES [^] *************************** */

char
	fill_the_arguments(t_program program, char **argv)
{
	program->args.number_of_philos = ft_atoi(argv[1]);
	program->args.time_to_die = ft_atoi(argv[2]);
	program->args.time_to_eat = ft_atoi(argv[3]);
	program->args.time_to_sleep = ft_atoi(argv[4]);
	if (!!argv[5])
		program->args.eat_limit = ft_atoi(argv[5]);
	if (program->args.number_of_philos > 200 \
		|| program->args.number_of_philos < 0)
	{
		printf(WARNING_MSG);
		return (1);
	}
	if (check_any_problem(program))
		return (1);
	if (create_forks(program))
		return (1);
	if (open_mutexs(program))
		return (1);
	if (program->args.number_of_philos == 1)
		pthread_mutex_lock(&program->mutex.wait_death);
	return (0);
}

static char
	check_any_problem(t_program program)
{
	int	error_level;

	error_level = 0;
	if (!program->args.number_of_philos)
		error_level = (printf(ERROR_MSG_5), 1);
	if (!program->args.time_to_die)
		error_level = (printf(ERROR_MSG_6), 1);
	if (!program->args.time_to_eat)
		error_level = (printf(ERROR_MSG_7), 1);
	if (!program->args.time_to_sleep)
		error_level = (printf(ERROR_MSG_8), 1);
	return (error_level);
}

static char
	create_forks(t_program program)
{
	register unsigned int	index;

	program->mutex.forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) \
		* (program->args.number_of_philos + 1));
	if (!program->mutex.forks)
		return (printf(ERROR_MSG_9), 1);
	index = 4294967295U;
	while (++index, index < program->args.number_of_philos)
	{
		if (pthread_mutex_init(&program->mutex.forks[index], (void *)0))
		{
			free_everything(program, (void *)0);
			printf(ERROR_MSG_10);
			return (1);
		}
	}
	return (0);
}

static char
	open_mutexs(t_program program)
{
	if (pthread_mutex_init(&program->mutex.print, (void *)0))
		return (free_everything(program, (void *)0), printf(ERROR_MSG_11), 1);
	if (pthread_mutex_init(&program->mutex.starving, (void *)0))
		return (free_everything(program, (void *)0), printf(ERROR_MSG_16), 1);
	if (pthread_mutex_init(&program->mutex.wait_death, (void *)0))
		return (free_everything(program, (void *)0), printf(ERROR_MSG_17), 1);
	if (pthread_mutex_init(&program->mutex.end, (void *)0))
		return (free_everything(program, (void *)0), printf(ERROR_MSG_18), 1);
	if (pthread_mutex_init(&program->mutex.total_eaten_meal, (void *)0))
		return (free_everything(program, (void *)0), printf(ERROR_MSG_19), 1);
	return (0);
}
