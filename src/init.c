/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:31:53 by bfiguet           #+#    #+#             */
/*   Updated: 2022/11/02 12:33:34 by bfiguet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

size_t	ft_time(void)
{
	struct timeval	t;

	gettimeofday (&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_parse(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (ft_error("Need 5 or 6 arguments", NULL));
	if (ac == 5)
		data->nb_meals = -1;
	if ((ft_atoi(av[1], &data->nb_philo) || !data->nb_philo
			|| ft_atoi(av[2], &data->t_die) || ft_atoi(av[3], &data->t_eat)
			|| ft_atoi(av[4], &data->t_sleep) || (ac == 6 && ft_atoi(av[5],
					&data->nb_meals))))
		return (ft_error("Invalid argument", NULL));
	return (0);
}

int	ft_mutex(pthread_mutex_t **mtx, t_data *data)
{
	*mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!*mtx)
		return (ft_error(MALLOC_ERR, data));
	if (pthread_mutex_init(*mtx, NULL))
		return (ft_error(MUTEX_ERR, data));
	return (0);
}

int	ft_data(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (ft_mutex(&data->forks[i].mutex_fork, data)
			|| ft_mutex(&data->philos[i].mutex_meal, data))
			return (1);
		data->philos[i].alive = 1;
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].left_f = &(data->forks[i]);
		data->philos[i].right_f = &(data->forks[(i + 1) % data->nb_philo]);
		data->philos[i].already_eat = 0;
		data->threads[i] = malloc(sizeof(pthread_t));
		if (!data->threads[i++])
			return (ft_error(MALLOC_ERR, data));
	}
	return (0);
}

int	ft_check_arg(t_data *data)
{
	data->process = data->nb_philo;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (ft_error(MALLOC_ERR, data));
	memset(data->philos, 0, sizeof(t_fork) * data->nb_philo);
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->nb_philo);
	if (!data->forks)
		return (ft_error(MALLOC_ERR, data));
	memset(data->forks, 0, sizeof(t_fork) * data->nb_philo);
	data->threads = (pthread_t **)malloc(sizeof(pthread_t *) * data->nb_philo);
	if (!data->threads)
		return (ft_error(MALLOC_ERR, data));
	memset(data->threads, 0, sizeof(pthread_t *) * data->nb_philo);
	if (ft_mutex(&data->mutex_msg, data) || ft_mutex(&data->mutex_end, data)
		|| ft_data(data))
		return (1);
	return (0);
}
