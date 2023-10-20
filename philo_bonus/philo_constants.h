/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_constants.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:00:40 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/07 18:06:08 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_CONSTANTS_H
# define PHILO_CONSTANTS_H 20231003

# define PHILO_STYLIST

# define WARNING_MSG "You entered invalid number of philosophers!\n"

# define ERROR_MSG_1 "Invalid number of argument entered!\n"
# define ERROR_MSG_2 "Every character in the arguments must be a number!\n"
# define ERROR_MSG_3 "The number is bigger than an integer!\n"
# define ERROR_MSG_4 "There shouldn't be a '-' character in the arguments!\n"
# define ERROR_MSG_5 "Number of philosophers shouldn't be 0!\n"
# define ERROR_MSG_6 "Time of die shouldn't be 0!\n"
# define ERROR_MSG_7 "Time of eat shouldn't be 0!\n"
# define ERROR_MSG_8 "Time of sleep shouldn't be 0!\n"
# define ERROR_MSG_9 "Malloc failed to allocate memory for forks. :(\n"
# define ERROR_MSG_10 "sem_t failed to open the 'fork' process. :(\n"
# define ERROR_MSG_11 "Malloc failed to allocate memory for philosophers. :(\n"
# define ERROR_MSG_12 "Failed to create fork (%d). :(\n"
# define ERROR_MSG_13 "Failed to get Unix time from the computer. :(\n"
# define ERROR_MSG_14 "Failed to get Unix time at frok (%d). :(\n"
# define ERROR_MSG_15 "sem_t failed to open the 'starving'. :(\n"
# define ERROR_MSG_16 "sem_t failed to open the 'end'. :(\n"
# define ERROR_MSG_17 "sem_t failed to open the 'total_eaten_meal'. :(\n"
# define ERROR_MSG_18 "Failed to create thread 'updater_thread'. :(\n"
# define ERROR_MSG_19 "Failed to create thread 'update_starving'. :(\n"
# define ERROR_MSG_20 "Failed to create thread 'sub_total_eaten_meal'. :(\n"
# define ERROR_MSG_21 "mutex failed to open the 'mutex_starving'. :(\n"
# define ERROR_MSG_22 "sem failed to open the 'set_end'. :(\n"
# define ERROR_MSG_23 "mutex failed to open the 'mutex_end'. :(\n"
# define ERROR_MSG_24 "mutex failed to open the 'mutex_total_eaten_meal'. :(\n"
# define ERROR_MSG_25 "sem failed to open the 'print'. :(\n"
# define ERROR_MSG_26 "sem failed to open the 'philo_starved'. :(\n"
# define ERROR_MSG_27 "sem failed to open the 'all_forks_ready'. :(\n"
# define ERROR_MSG_28 "sem failed to open the 'philos_turn'. :(\n"
# define ERROR_MSG_29 "Malloc failed to allocate memory for turns. :(\n"
# define ERROR_MSG_30 "sem failed to open a 'turn'. :(\n"

# ifdef PHILO_STYLIST
#  define MSG_PRINT_MSG "\e[0;36m%5llums \e[0;33m[%d] %s\e[0;0m\n"
#  define MSG_DEATH "\e[0;36m%5llums \e[0;31m💀 philo %d is dead!\e[0;0m\n"
#  define MSG_FORK_RIGHT "\e[0;32m🥄 has taken a fork \e[0;35m(right_fork ✋)"
#  define MSG_FORK_LEFT "\e[0;32m🥄 has taken a fork \e[0;35m(left_fork 🤚)"
#  define MSG_EATING "\e[0;32m🤤 is started to eating"
#  define MSG_SLEEPING "\e[0;34m😴 is sleeping"
#  define MSG_THINKING "\e[0;37m🤔 is thinking"
#  define MSG_END "\n \e[49;5;7m✅ Program is sucessfully ended!\e[0;0m\n\n"
# else
#  define MSG_PRINT_MSG "%llu %d %s\n"
#  define MSG_DEATH "%llu %d died\n"
#  define MSG_FORK_RIGHT "has taken a fork"
#  define MSG_FORK_LEFT "has taken a fork"
#  define MSG_EATING "is eating"
#  define MSG_SLEEPING "is sleeping"
#  define MSG_THINKING "is thinking"
#  define MSG_END "\n ✅ Program is sucessfully ended!\n\n"
# endif

#endif /* PHILO_CONSTANTS_H */
