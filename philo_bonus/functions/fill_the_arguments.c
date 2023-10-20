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
#include "../main_bonus.h" /*
#typedef t_program;
#    int ft_atoi(char *);
#   void free_everything(t_program, t_philo);
*/
#include "../philo_constants.h" /*
# define ERROR_MSG_5;
# define ERROR_MSG_6;
# define ERROR_MSG_7;
# define ERROR_MSG_8;
# define ERROR_MSG_9;
# define ERROR_MSG_10;
# define ERROR_MSG_11;
# define ERROR_MSG_15;
# define ERROR_MSG_16;
# define ERROR_MSG_17;
# define ERROR_MSG_22;
# define ERROR_MSG_25;
# define ERROR_MSG_26;
# define ERROR_MSG_27;
# define ERROR_MSG_29;
# define WARNING_MSG;
*/
#include <semaphore.h> /*
# define SEM_FAILED;
#    int sem_wait(sem_t *);
#    int sem_post(sem_t *);
#  sem_t *sem_open(char *, int, mode_t, int);
#    int sem_unlink(char *);
*/
#include <stdlib.h> /*
#   void *malloc(int);
#   void free(void *);
*/
#include <stdio.h> /*
#    int printf(char *, ...);
*/
#include <fcntl.h> /*
# define O_CREAT;
*/
/* **************************** [^] INCLUDES [^] **************************** */

/* *************************** [v] PROTOTYPES [v] *************************** */
static char	check_any_problem(t_program program);
static char	create_forks(t_program program, unsigned int philo_len);
static char	open_sems(t_program program);
static char	sem_open_fork(unsigned int index, t_program program);
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
	if (program->args.number_of_philos > 201 \
		|| program->args.number_of_philos < 0)
		return (printf(WARNING_MSG), 1);
	program->start_time = get_time();
	if (program->start_time == 0ULL)
		return (printf(ERROR_MSG_13), 1);
	if (check_any_problem(program))
		return (1);
	program->sem.turns = (sem_t **) malloc(sizeof(sem_t *) * \
		(program->args.number_of_philos + 1));
	if (!program->sem.forks)
		return (printf(ERROR_MSG_29), 1);
	if (create_forks(program, program->args.number_of_philos))
		return (1);
	if (open_sems(program))
		return (1);
	return (0);
}

static char
	check_any_problem(t_program program)
{
	int	error_level;

	error_level = 0;
	if (program->args.number_of_philos <= 0)
		error_level = (printf(ERROR_MSG_5), 1);
	if (program->args.time_to_die <= 0)
		error_level = (printf(ERROR_MSG_6), 1);
	if (program->args.time_to_eat <= 0)
		error_level = (printf(ERROR_MSG_7), 1);
	if (program->args.time_to_sleep <= 0)
		error_level = (printf(ERROR_MSG_8), 1);
	return (error_level);
}

static char
	create_forks(t_program program, unsigned int philo_len)
{
	register unsigned int	index;

	program->sem.forks = (sem_t **) malloc(sizeof(sem_t *) * (philo_len + 1));
	if (!program->sem.forks)
	{
		free(program->sem.turns);
		program->sem.turns = (void *)0;
		return (printf(ERROR_MSG_9), 1);
	}
	index = 4294967295U;
	while (++index, index < philo_len)
		if (sem_open_fork(index, program))
			return (free_everything(program, (void *)0), printf(ERROR_MSG_10), \
				1);
	return (0);
}

static char
	open_sems(t_program program)
{
	sem_unlink("/philo_total_eaten_meal");
	sem_unlink("/philo_print");
	sem_unlink("/philo_philo_starved");
	sem_unlink("/philo_set_end");
	sem_unlink("/philo_all_forks_ready");
	program->sem.total_eaten_meal = sem_open("/philo_total_eaten_meal", \
		O_CREAT, 0777, 1);
	if (program->sem.total_eaten_meal == SEM_FAILED)
		return (free_everything(program, (void *)0), printf(ERROR_MSG_17), 1);
	program->sem.print = sem_open("/philo_print", O_CREAT, 0777, 1);
	if (program->sem.print == SEM_FAILED)
		return (free_everything(program, (void *)0), printf(ERROR_MSG_25), 1);
	program->sem.philo_starved = sem_open("/philo_philo_starved", \
		O_CREAT, 0777, 1);
	if (program->sem.philo_starved == SEM_FAILED)
		return (free_everything(program, (void *)0), printf(ERROR_MSG_26), 1);
	program->sem.set_end = sem_open("/philo_set_end", O_CREAT, 0777, 0);
	if (program->sem.set_end == SEM_FAILED)
		return (free_everything(program, (void *)0), printf(ERROR_MSG_22), 1);
	program->sem.all_forks_ready = sem_open("/philo_all_forks_ready", \
		O_CREAT, 0777, 0);
	if (program->sem.all_forks_ready == SEM_FAILED)
		return (free_everything(program, (void *)0), printf(ERROR_MSG_27), 1);
	return (0);
}

static char
	sem_open_fork(unsigned int index, t_program program)
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
	sem_unlink(edited_string);
	program->sem.forks[index] = sem_open(edited_string, O_CREAT, 0777, 1);
	if (program->sem.forks[index] == SEM_FAILED)
		return (1);
	return (0);
}
