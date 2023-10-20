/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_sub_total_eaten_meal.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:50:46 by hdeniz            #+#    #+#             */
/*   Updated: 2023/10/12 15:50:47 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** [v] INCLUDES [v] **************************** */
#include "../../../main_bonus.h" /*
#typedef t_philo;
*/
#include <semaphore.h> /*
#    int sem_wait(sem_t *);
#    int sem_post(sem_t *);
*/
/* **************************** [^] INCLUDES [^] **************************** */

void
	sem_sub_total_eaten_meal(t_philo philo)
{
	register unsigned int	index;

	index = 4294967295U;
	sem_wait(philo->program->sem.total_eaten_meal);
	while (++index, index < philo->program->args.number_of_philos)
		sem_post(philo->program->sem.turns[index]);
	sem_post(philo->program->sem.total_eaten_meal);
}
