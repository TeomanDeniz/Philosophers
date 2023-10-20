/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:00:35 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/07 18:05:38 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H 20230930

/* **************************** [v] INCLUDES [v] **************************** */
# include <pthread.h> /*
# typedef pthread_mutex_t
# typedef pthread_t;
*/
# include <unistd.h> /*
# typedef useconds_t;
*/
/* **************************** [^] INCLUDES [^] **************************** */

/* **************************** [v] STRUCTS [v] ***************************** */
struct s_mutex
{
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	end;
	pthread_mutex_t	total_eaten_meal;
	pthread_mutex_t	starving;
	pthread_mutex_t	wait_death;
};

struct s_args
{
	unsigned int	number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	eat_limit;
};

typedef struct s_program
{
	unsigned long long		start_time;
	unsigned long long		total_eaten_meal;
	char					death;
	char					error;
	char					end;
	pthread_t				kill_checker;
	struct s_args			args;
	struct s_mutex			mutex;
}	*t_program;

typedef struct s_philo
{
	pthread_t			this;
	unsigned int		id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	unsigned int		starving;
	unsigned long long	eaten_meal;
	t_program			program;
}	*t_philo;
/* **************************** [^] STRUCTS [^] ***************************** */

/* ************************ [v] DECLARE ENTITIES [v] ************************ */
char					fill_the_arguments(t_program program, char **argv);
void					free_everything(t_program program, t_philo philo);
char					check_args(register int argc, char **argv);
void					create_threads(t_program program);
char					join_threads(t_program program);
int						ft_msleep(useconds_t time);
int						ft_atoi(const char *string);
void					*thread_philo(void *arg);
void					*kill_checker(void *arg);
unsigned long long		get_time(void);
/* ************************ [^] DECLARE ENTITIES [^] ************************ */

#endif /* MAIN_H */
