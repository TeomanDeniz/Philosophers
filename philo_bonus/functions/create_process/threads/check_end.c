/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:51:06 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/11 17:51:07 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../../../main_bonus.h" /*
#typedef t_philo;
*/
#include <semaphore.h> /*
#    int sem_wait(sem_t *);
*/
#include <stdlib.h> /*
#   void exit(int);
*/
/* **************************** [^] INCLUDES [^] **************************** */

void
	*check_end(void *arg)
{
	t_philo	philo;

	philo = (t_philo) arg;
	sem_wait(philo->program->sem.set_end);
	sem_post(philo->program->sem.set_end);
	exit(0);
	return ((void *)0);
}
