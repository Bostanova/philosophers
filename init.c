/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:22:06 by eerika            #+#    #+#             */
/*   Updated: 2021/08/17 16:37:08 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	init(char **argv, t_input *input)
{
	input->count_of_phils = ft_atoi(argv[1]);
	input->time_to_die = ft_atoi(argv[2]);
	input->time_to_eat = ft_atoi(argv[3]);
	input->time_to_sleep = ft_atoi(argv[4]);
	if (!argv[5])
		input->count_of_meal = -1;
	else
	{
		input->count_of_meal = ft_atoi(argv[5]);
		if (input->count_of_meal < 1)
			ft_exit("Error: the value of the arguments is incorrect!");
	}
	if (input->count_of_phils < 1 || input->time_to_die < 1
		|| input->time_to_eat < 1 || input->time_to_sleep < 1)
		ft_exit("Error: the value of the arguments is incorrect!");
	input->start_time = get_time();
	input->full_phills = 0;
	input->need_to_stop = 0;
}

pthread_mutex_t	**alloc_forks(int len)
{
	int				i;
	pthread_mutex_t	**forks;

	forks = malloc(sizeof(pthread_mutex_t *) * len);
	if (!forks)
		ft_exit("Error: cannot allocate memory!");
	i = 0;
	while (i < len)
	{
		forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
			ft_exit("Error: cannot allocate memory!");
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philo	*alloc_philo(int count, pthread_mutex_t **forks, t_input *input)
{
	t_philo	*res;
	int		i;

	res = (t_philo *)malloc(sizeof(t_philo) * count);
	if (!res)
		return (NULL);
	i = 0;
	while (i < count)
	{
		res[i].id = i + 1;
		res[i].input = input;
		res[i].count_meal = 0;
		if (res[i].id % 2 == 1)
		{
			res[i].fork_left = forks[i];
			res[i].fork_right = forks[(i + 1) % input->count_of_phils];
		}
		else
		{
			res[i].fork_right = forks[(i + 1) % input->count_of_phils];
			res[i].fork_left = forks[i];
		}
		i++;
	}
	return (res);
}
