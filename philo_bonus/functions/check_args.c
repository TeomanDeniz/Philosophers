/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:59:44 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/07 16:59:44 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../main_bonus.h" /*
#    int ft_atoi(char *);
*/
#include "../philo_constants.h" /*
# define ERROR_MSG_1;
# define ERROR_MSG_4;
# define ERROR_MSG_2;
# define ERROR_MSG_3;
*/
#include <stdio.h> /*
#    int printf(char *, ...);
*/
/* **************************** [^] INCLUDES [^] **************************** */

/* *************************** [v] PROTOTYPES [v] *************************** */
static char	check_number_of_argumant(register int argc);
static char	check_all_argumants_valid(char **argv);
static char	check_all_argumants_positive(char **argv);
/* *************************** [^] PROTOTYPES [^] *************************** */

char
	check_args(register int argc, char **argv)
{
	if (check_number_of_argumant(argc))
		return (1);
	if (check_all_argumants_valid(argv))
		return (1);
	if (check_all_argumants_positive(argv))
		return (1);
	return (0);
}

static char
	check_number_of_argumant(register int argc)
{
	if (argc == 5 || argc == 6)
		return (0);
	printf(ERROR_MSG_1);
	return (1);
}

static char
	check_all_argumants_valid(char **argv)
{
	register int	string;
	register int	index;

	string = 0;
	while (++string, argv[string])
	{
		index = -1;
		while (++index, argv[string][index])
		{
			if (argv[string][index] == '-')
			{
				printf(ERROR_MSG_4);
				return (1);
			}
			if (!(argv[string][index] >= '0' && argv[string][index] <= '9'))
			{
				printf(ERROR_MSG_2);
				return (1);
			}
		}
	}
	return (0);
}

static char
	check_all_argumants_positive(char **argv)
{
	register int	index;

	index = 0;
	while (++index, argv[index])
	{
		if (ft_atoi(argv[index]) <= 0)
		{
			printf(ERROR_MSG_3);
			return (1);
		}
	}
	return (0);
}
