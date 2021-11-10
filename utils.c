/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:21:46 by eerika            #+#    #+#             */
/*   Updated: 2021/08/17 16:22:34 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	ft_exit(char *err)
{
	printf("%s\n", err);
	exit(1);
}

unsigned long long	get_time(void)
{
	struct timeval		cur_time;
	unsigned long long	res;

	gettimeofday(&cur_time, NULL);
	res = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000;
	return (res);
}

void	free_memory(t_input *input, pthread_t *threads,
	pthread_mutex_t **forks, t_philo *philo)
{
	int	i;

	free(input);
	free(threads);
	i = 0;
	while (i < input->count_of_phils)
	{
		free(forks[i]);
		i++;
	}
	free(forks);
	free(philo);
}
