/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:34:35 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/12 17:34:37 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_BONUS_H
# define MAIN_BONUS_H 20230930

/* ***************************** [v] INCLUDES [v] *************************** */
# include <pthread.h> /*
# typedef pthread_mutex_t
*/
# include <semaphore.h> /*
# typedef sem_t;
*/
# include <unistd.h> /*
# typedef useconds_t;
# typedef pid_t;
*/
/* ***************************** [^] INCLUDES [^] *************************** */

/* ***************************** [v] TYPEDEF [v] **************************** */
typedef unsigned long long	t_ull;
/* ***************************** [^] TYPEDEF [^] **************************** */

/* ***************************** [v] STRUCTS [v] **************************** */
struct s_sem
{
	sem_t	**forks;
	sem_t	**turns;
	sem_t	*total_eaten_meal;
	sem_t	*print;
	sem_t	*set_end;
	sem_t	*philo_starved;
	sem_t	*all_forks_ready;
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
	t_ull			start_time;
	t_ull			total_eaten_meal;
	char			end;
	struct s_args	args;
	struct s_sem	sem;
}	*t_program;

typedef struct s_philo
{
	pid_t			this;
	unsigned int	id;
	sem_t			*left_fork;
	sem_t			*right_fork;
	t_ull			starving;
	t_ull			eaten_meal;
	char			eating;
	pthread_mutex_t	mutex_total_eaten_meal;
	pthread_mutex_t	mutex_starving;
	pthread_mutex_t	mutex_end;
	t_program		program;
}	*t_philo;
/* **************************** [^] STRUCTS [^] ***************************** */

/* ************************ [v] DECLARE ENTITIES [v] ************************ */
extern char		fill_the_arguments(t_program program, char **argv);
extern void		free_everything(t_program program, t_philo philo);
extern void		print_massage(t_philo philo, const char *string);
extern char		check_args(register int argc, char **argv);
extern void		*thread_sub_total_eaten_meal(void *arg);
extern void		sem_sub_total_eaten_meal(t_philo philo);
extern void		create_process(t_program program);
extern void		*sub_total_eaten_meal(void *arg);
extern void		process_philo(t_philo philo);
extern void		*update_starving(void *arg);
extern int		ft_atoi(const char *string);
extern void		sem_set_end(t_philo philo);
extern int		ft_msleep(useconds_t time);
extern void		*kill_checker(void *arg);
extern void		*check_end(void *arg);
extern t_ull	get_time(void);
/* ************************ [^] DECLARE ENTITIES [^] ************************ */

#endif /* MAIN_BONUS_H */
