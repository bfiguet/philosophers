/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiguet <bfiguet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:51:44 by bfiguet           #+#    #+#             */
/*   Updated: 2022/11/02 13:13:10 by bfiguet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_is_dead(t_philo *philo)
{
	if (pthread_mutex_lock(philo->data->mutex_msg))
		return (ft_error(LOCK_ERR, NULL));
	printf("\033[0;35m%zu ms \033[m \033[1;36m%zu \033[m%s\n",
		ft_time() - philo->data->start_time, philo->id, DIED);
	if (pthread_mutex_unlock(philo->data->mutex_msg))
		return (ft_error(UNLOCK_ERR, NULL));
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->mutex_meal))
		return (ft_print(philo, ERROR, LOCK_ERR));
	philo->last_meal = ft_time();
	if (pthread_mutex_unlock(philo->mutex_meal))
		return (ft_print(philo, ERROR, UNLOCK_ERR));
	if ((ft_print(philo, PHILO, EAT) || ft_wait(philo->data->t_eat,
				philo->data->t_die)))
		return (1);
	return (0);
}

t_fork	*ft_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (philo->left_f);
	else
		return (philo->right_f);
}

int	ft_end_fork(t_philo *philo, t_fork *fork)
{
	if (pthread_mutex_unlock(fork->mutex_fork))
		return (ft_print(philo, ERROR, UNLOCK_ERR));
	if (philo->data->nb_philo == 1)
		return (1);
	return (0);
}

int	ft_forks(t_philo *philo, t_fork *fork)
{
	int		i;
	t_fork	*f;

	i = 3;
	f = fork;
	while (--i)
	{
		if (pthread_mutex_lock(f->mutex_fork))
			return (ft_print(philo, ERROR, LOCK_ERR));
		if (philo->id == f->last_philo)
		{
			if (ft_end_fork(philo, f))
				return (1);
		}
		f->last_philo = philo->id;
		if (ft_print(philo, PHILO, FORK) || (philo->data->nb_philo == 1
				&& ft_end_fork(philo, f)))
			return (1);
		if (philo->id % 2 == 0)
			f = philo->right_f;
		else
			f = philo->left_f;
	}
	return (0);
}
