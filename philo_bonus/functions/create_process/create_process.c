/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:16:57 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/12 17:16:59 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../../main_bonus.h" /*
#typedef t_program;
#typedef t_philo;
# struct s_philo;
#   void process_philo(t_philo);
#    int ft_msleep(useconds_t);
#   void free_everything(t_program, t_philo);
#    ull get_time(void);
*/
#include "../../philo_constants.h" /*
# define ERROR_MSG_11;
# define ERROR_MSG_12;
# define ERROR_MSG_28;
# define ERROR_MSG_30;
# define MSG_END;
*/
#include <stdlib.h> /*
#   void *malloc(int);
#   void exit(int);
*/
#include <stdio.h> /*
#    int printf(char *, ...);
*/
#include <signal.h> /*
# define SIGKILL;
#    int kill(pid_t, int);
*/
#include <sys/wait.h> /*
#  pid_t waitpid(pid_t, int *, int);
*/
#include <unistd.h> /*
#typedef pid_t;
#  pid_t fork(void);
*/
#include <semaphore.h> /*
# define SEM_FAILED;
#    int sem_post(sem_t *);
#  sem_t *sem_open(char *, int, mode_t, int);
#    int sem_unlink(char *);
*/
/* **************************** [^] INCLUDES [^] **************************** */

/* *************************** [v] PROTOTYPES [v] *************************** */
static t_philo	create_philo_struct(t_program program, unsigned int philo_len);
static void		wait_all_process(t_program program, t_philo philo);
static char		create(pid_t *pid, void (*function)(t_philo), t_philo arg);
static char		sem_open_turn(unsigned int index, t_program program);
/* *************************** [^] PROTOTYPES [^] *************************** */

void
	create_process(t_program program)
{
	register unsigned int	ecx;
	t_philo					philo;

	ecx = 4294967295U;
	philo = create_philo_struct(program, program->args.number_of_philos);
	if (!philo)
		return ;
	while (++ecx, ecx < program->args.number_of_philos)
	{
		if (create(&philo[ecx].this, process_philo, &philo[ecx]))
		{
			printf(ERROR_MSG_12, ecx);
			while (--ecx, ecx)
			{
				kill(philo[ecx].this, SIGKILL);
				waitpid(philo[ecx].this, (void *)0, 0);
			}
			free_everything(program, philo);
			return ;
		}
	}
	wait_all_process(program, philo);
	sem_post(program->sem.total_eaten_meal);
	free_everything(program, philo);
}

static t_philo
	create_philo_struct(t_program program, unsigned int philo_len)
{
	register unsigned int	index;
	t_philo					philo;

	index = 4294967295U;
	philo = (t_philo) malloc(sizeof(struct s_philo) * (philo_len + 1));
	if (!philo)
		return (free_everything(program, (void *)0), printf(ERROR_MSG_11), \
			(void *)0);
	while (++index, index < philo_len)
	{
		philo[index].id = (index + 1U);
		philo[index].this = 0;
		philo[index].starving = get_time();
		philo[index].left_fork = program->sem.forks[(index + 1U) % philo_len];
		philo[index].right_fork = program->sem.forks[index];
		philo[index].eaten_meal = 0ULL;
		philo[index].program = program;
		philo[index].eating = 0;
		if (sem_open_turn(index, program))
		{
			philo = (free(philo), (void *)0);
			return ((void *)0);
		}
	}
	return (philo);
}

static void
	wait_all_process(t_program program, t_philo philo)
{
	register unsigned int	index;

	index = 4294967295U;
	while (++index, index < program->args.number_of_philos)
		sem_post(program->sem.all_forks_ready);
	index = 4294967295U;
	while (++index, index < program->args.number_of_philos)
		waitpid(philo[index].this, (void *)0, 0);
	sem_post(program->sem.set_end);
	printf(MSG_END);
}

static char
	create(pid_t *pid, void (*function)(t_philo), t_philo arg)
{
	if (!function)
		return (1);
	*pid = fork();
	if (*pid == -1)
		return (-1);
	if (*pid == 0)
	{
		sem_wait(arg->program->sem.all_forks_ready);
		sem_post(arg->program->sem.all_forks_ready);
		if ((arg->id - 1) % 2 == 1)
			ft_msleep(2);
		function(arg);
		exit(0);
	}
	return (0);
}

static char
	sem_open_turn(unsigned int index, t_program program)
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
	sem_unlink(edited_string);
	program->sem.turns[index] = sem_open(edited_string, O_CREAT, 0777, 0);
	if (program->sem.turns[index] == SEM_FAILED)
		return (printf(ERROR_MSG_30), 1);
	return (0);
}
