/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:19:16 by bfiguet           #+#    #+#             */
/*   Updated: 2022/11/02 12:33:25 by bfiguet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_life(t_data *data, size_t id, int *flag, int *print)
{
	if (pthread_mutex_lock(data->mutex_end))
		return (ft_print(&data->philos[0], ERROR, LOCK_ERR));
	if (!data->process)
		*flag = 0;
	*print = 0;
	if (data->philos[id].alive)
	{
		*print = 1;
		data->end = 1;
	}
	if (pthread_mutex_unlock(data->mutex_end))
		return (ft_print(&data->philos[0], ERROR, UNLOCK_ERR));
	if ((!*flag || *print) && pthread_mutex_unlock(data->philos[id].mutex_meal))
		return (ft_print(&data->philos[0], ERROR, UNLOCK_ERR));
	if (*print)
		return (ft_is_dead(&data->philos[id]));
	return (0);
}

void	*dinner(void *ph)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)ph;
	while (1)
	{
		if (ft_is_end(p, 0) || ft_forks(p, ft_take_fork(p)))
			return (NULL);
		i = ft_is_end(p, 0);
		if (!i && ft_eat(p))
			i = 1;
		if (pthread_mutex_unlock(p->right_f->mutex_fork)
			|| pthread_mutex_unlock(p->left_f->mutex_fork))
		{
			ft_print(p, ERROR, UNLOCK_ERR);
			i = 1;
		}
		if (i || ft_is_end(p, 1) || ft_print(p, PHILO, SLEEP)
			|| ft_wait(p->data->t_sleep, p->data->t_die)
			|| ft_is_end(p, 0) || ft_print(p, PHILO, THINK))
			return (NULL);
	}
}

int	ft_philo(t_data *data)
{
	size_t	id;
	int		flag;
	int		print;

	id = 0;
	while (1)
	{
		usleep(100);
		if (pthread_mutex_lock(data->philos[id].mutex_meal))
			return (ft_print(&data->philos[0], ERROR, LOCK_ERR));
		flag = 0;
		if (data->t_die < ft_time() - data->philos[id].last_meal)
			flag = 1;
		if (flag)
		{
			if (ft_life(data, id, &flag, &print))
				return (1);
			if (!flag || print)
				return (0);
		}
		if (pthread_mutex_unlock(data->philos[id].mutex_meal))
			return (ft_print(&data->philos[0], ERROR, UNLOCK_ERR));
		id = (id + 1) % data->nb_philo;
	}
}

int	ft_start(t_data *data)
{
	size_t	i;

	i = 0;
	data->start_time = ft_time();
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(data->threads[i], NULL, dinner, &data->philos[i])
			&& ft_error(THREAD_ERR, NULL))
			return (0);
		i++;
	}
	if (ft_philo(data))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	size_t	i;

	////data = (t_data){0}; // remplace memset
	memset(&data, 0, sizeof(t_data));
	if (ft_parse(&data, ac, av))
		return (1);
	if (ac == 6 && !data.nb_meals)
		return (0);
	if (ft_check_arg(&data))
		return (1);
	if (ft_start(&data))
	{
		i = 0;
		while (i < data.nb_philo)
		{
			if (pthread_join(*data.threads[i], NULL)
				&& ft_error(THREAD_ERR, NULL))
				break ;
			i++;
		}
	}
	ft_error(NULL, &data);
	return (0);
}
