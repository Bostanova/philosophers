/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eerika <eerika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:22:09 by eerika            #+#    #+#             */
/*   Updated: 2021/08/17 17:29:28 by eerika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	is_dead(t_philo *philo)
{
	int	i;

	while (!philo->input->need_to_stop)
	{
		i = 0;
		while (!philo->input->need_to_stop && i < philo->input->count_of_phils)
		{
			if (get_time() - philo[i].last_meal > philo[i].input->time_to_die)
			{
				philo[i].input->need_to_stop = 1;
				printf("%llu phil #%d died\n",
					get_time() - philo[i].last_meal, philo[i].id);
			}
			i++;
		}
	}
}

void	threads_exec(pthread_t *threads, t_philo *philo, t_input *input)
{
	int	i;

	input->start_time = get_time();
	i = -1;
	while (++i < input->count_of_phils)
	{
		pthread_create(&threads[i], NULL, start, &philo[i]);
		usleep(30);
	}
	is_dead(philo);
	i = -1;
	while (++i < input->count_of_phils)
		pthread_detach(threads[i]);
}

int	main(int argc, char **argv)
{
	t_input				*input;
	t_philo				*philo;
	pthread_t			*threads;
	pthread_mutex_t		**forks;
	int					i;

	if (argc < 5 || argc > 6)
		ft_exit("Error: wrong number of arguments!");
	input = (t_input *)malloc(sizeof(t_input));
	if (!input)
		ft_exit("Error: cannot allocate memory!");
	init(argv, input);
	forks = alloc_forks(input->count_of_phils);
	philo = alloc_philo(input->count_of_phils, forks, input);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * input->count_of_phils);
	if (!threads)
		ft_exit("Error: cannot allocate memory!");
	threads_exec(threads, philo, input);
	i = -1;
	while (++i < input->count_of_phils)
		pthread_mutex_destroy(forks[i]);
	free_memory(input, threads, forks, philo);
	return (0);
}
