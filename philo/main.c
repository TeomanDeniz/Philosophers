/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:00:29 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/07 17:00:30 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "main.h" /*
# struct s_program;
#   char check_args(int, char **);
#   char fill_the_arguments(t_program, char **);
#   void create_threads(t_program);
#   char join_threads(t_program);
#    ull get_time(void);
*/
#include "philo_constants.h" /*
# define ERROR_MSG_14;
*/
#include <stdio.h> /*
#    int printf(char *, ...);
*/
/* **************************** [^] INCLUDES [^] **************************** */

int
	main(int argc, char **argv)
{
	struct s_program	program;

	program.start_time = get_time();
	if (program.start_time == 0ULL)
	{
		printf(ERROR_MSG_14);
		return (1);
	}
	program.error = 0;
	program.death = 0;
	program.end = 0;
	program.total_eaten_meal = 0ULL;
	program.args.eat_limit = 0;
	if (!check_args(argc, argv))
		if (!fill_the_arguments(&program, argv))
			create_threads(&program);
	return (0);
}
