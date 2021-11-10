/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:22:13 by eerika            #+#    #+#             */
/*   Updated: 2021/08/17 17:15:18 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

static void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	printf("%llu phil #%d has taken first fork\n",
		(get_time() - philo->input->start_time), philo->id);
	pthread_mutex_lock(philo->fork_right);
	printf("%llu phil #%d has taken second fork\n",
		(get_time() - philo->input->start_time), philo->id);
	printf("%llu phil #%d is eating\n",
		(get_time() - philo->input->start_time), philo->id);
	philo->last_meal = get_time();
	philo->count_meal++;
	if (philo->count_meal == philo->input->count_of_meal)
	{
		philo->input->full_phills++;
		if (philo->input->full_phills == philo->input->count_of_phils)
			philo->input->need_to_stop = 1;
	}
}

void	*start(void *philo)
{
	t_philo				*tmp;
	unsigned long long	beg_time;

	tmp = (t_philo *)philo;
	tmp->last_meal = get_time();
	while (1)
	{
		is_eating(tmp);
		beg_time = get_time();
		while (get_time() - beg_time < tmp->input->time_to_eat)
			usleep(30);
		pthread_mutex_unlock(tmp->fork_right);
		pthread_mutex_unlock(tmp->fork_left);
		printf("%llu phil #%d is sleeping\n",
			(get_time() - tmp->input->start_time), tmp->id);
		beg_time = get_time();
		while (get_time() - beg_time < tmp->input->time_to_sleep)
			usleep(30);
		printf("%llu phil #%d is thinking\n",
			(get_time() - tmp->input->start_time), tmp->id);
	}
}
