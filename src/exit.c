/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:55:55 by bfiguet           #+#    #+#             */
/*   Updated: 2022/11/02 12:03:11 by bfiguet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_is_end(t_philo *philo, int after_eat)
{
	int	flag;

	if (pthread_mutex_lock(philo->data->mutex_end))
		return (ft_print(philo, ERROR, LOCK_ERR));
	flag = 0;
	if (philo->data->end)
		flag = 1;
	if (!flag && after_eat && (++philo->already_eat == philo->data->nb_meals))
	{
		flag = 1;
		philo->data->process--;
		philo->alive = 0;
	}
	if (pthread_mutex_unlock(philo->data->mutex_end))
		return (ft_print(philo, ERROR, UNLOCK_ERR));
	return (flag);
}

void	ft_clean_mtx(pthread_mutex_t *mtx)
{
	if (mtx)
		pthread_mutex_destroy(mtx);
	free(mtx);
}

void	ft_exit(t_data *data)
{
	size_t	i;

	ft_clean_mtx(data->mutex_msg);
	ft_clean_mtx(data->mutex_end);
	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philos)
			ft_clean_mtx(data->philos[i].mutex_meal);
		if (data->forks)
			ft_clean_mtx(data->forks[i].mutex_fork);
		if (data->threads)
			free(data->threads[i]);
		i++;
	}
	free(data->philos);
	free(data->forks);
	free(data->threads);
}
