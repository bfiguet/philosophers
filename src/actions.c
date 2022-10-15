/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:14:04 by bfiguet           #+#    #+#             */
/*   Updated: 2022/10/15 16:36:43 by bfiguet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->philo_data;
	pthread_mutex_lock(&(data->mutex_forks[philo->left_f]));
	pthread_mutex_lock(&(data->mutex_meal));
	ft_print(data, philo->id, "\033[0;32mhas taken a left for\033[m");
	pthread_mutex_unlock(&(data->mutex_meal));
	pthread_mutex_lock(&(data->mutex_forks[philo->right_f]));
	pthread_mutex_lock(&(data->mutex_meal));
	ft_print(data, philo->id, "\033[0;32mhas taken a right for\033[m");
	ft_print(data, philo->id, "\033[0;31mis eating\033[m");
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&(data->mutex_meal));
	ft_sleep(data->t_sleep, data);
	pthread_mutex_lock(&(data->mutex_meal));
	(philo->nb_meal)++;
	pthread_mutex_unlock(&(data->mutex_meal));
	pthread_mutex_unlock(&(data->mutex_forks[philo->right_f]));
	pthread_mutex_unlock(&(data->mutex_forks[philo->left_f]));
}

void	ft_sleep(long long time, t_data *data)
{
	long long	i;

	i = ft_get_time();
	//pthread_mutex_lock(&(data->mutex_meal));
	while ((!((ft_get_time() - i) >= time)) && !(data->is_dead))
	{
		pthread_mutex_unlock(&(data->mutex_meal));
		usleep(50);
		pthread_mutex_lock(&(data->mutex_meal));
	}
	pthread_mutex_unlock(&(data->mutex_meal));
}

void	*dinner(void *dinner)
{
	t_philo		*ph;
	t_data		*data;
	int			i;

	i = 0;
	ph = (t_philo *)dinner;
	data = ph->philo_data;
	if (ph->id % 2 == 0)
		usleep(1500);
	pthread_mutex_lock(&(data->mutex_meal));
	while (!(data->is_dead) && !(data->all_ate))
	{
		pthread_mutex_unlock(&(data->mutex_meal));
		ft_eat(ph);
		pthread_mutex_lock(&(data->mutex_meal));
		ft_print(data, ph->id, "\033[0;34mis sleeping\033[m");
		//pthread_mutex_unlock(&(data->mutex_meal));
		ft_sleep(data->t_sleep, data);
        pthread_mutex_lock(&(data->mutex_meal));
        ft_print(data, data->philo->id, "\033[0;33mis thinking\033[m"); 
        i++;
	}
	pthread_mutex_unlock(&(data->mutex_meal));
	return (NULL);
}

void	ft_check_death(int i, t_data *data, t_philo *ph)
{
	while (++i < data->nb_philo && !(data->is_dead))
	{
		pthread_mutex_lock(&(data->mutex_meal));
		if ((ft_get_time() - ph[i].last_eat) >= data->t_die)
		{
            ft_print(data, i + 1, "\033[7;31mis dead\033[m");
		    data->is_dead = 1;
        }
		pthread_mutex_unlock(&(data->mutex_meal));
		usleep(100);
	}
}

void	ft_is_dead(t_data *data, t_philo *ph)
{
	int	i;

	while (!(data->all_ate))
	{
		i = -1;
		ft_check_death(i, data, ph);
		if (data->is_dead)
			break ;
		i = 0;
		pthread_mutex_lock(&(data->mutex_meal));
		while (data->t_die != -1 && i < data->nb_philo
			&& ph[i].nb_meal >= data->t_die)
			i++;
		if (i == data->nb_philo)
			data->all_ate = 1;
		pthread_mutex_unlock(&(data->mutex_meal));
	}
}
