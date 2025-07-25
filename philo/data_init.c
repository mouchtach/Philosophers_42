/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:24:33 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/17 21:21:06 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	mutex_init(t_table *table)
{
	if (pthread_mutex_init(&table->mtx->end, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&table->mtx->print, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&table->mtx->meal, NULL) != 0)
		return (false);
	return (true);
}

bool	aloccated_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks)
		return (false);
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (free(table->forks), false);
		i++;
	}
	return (true);
}

void	fork_init(int index, t_table *table)
{
	if (table->nb_philo == 1)
	{
		table->p[index].r_fork = &table->forks[0];
		table->p[index].l_fork = &table->forks[0];
	}
	else
	{
		if (index == 0)
			table->p[index].r_fork = &table->forks[table->nb_philo - 1];
		else
			table->p[index].r_fork = &table->forks[index];
		table->p[index].l_fork = &table->forks[index - 1];
	}
}

bool	table_init(t_table *table)
{
	int	i;

	i = 0;
	if (!aloccated_forks(table))
		return (false);
	table->p = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->p)
		return (free_forks(table), false);
	while (i < table->nb_philo)
	{
		table->p[i].id = i + 1;
		fork_init(i, table);
		table->p[i].count_m = 0;
		table->p[i].full = false;
		table->p[i].table = table;
		table->p[i].time_stat = get_time();
		table->p[i].last_tm_eat = get_time();
		i++;
	}
	table->end = false;
	if (!mutex_init(table))
		return (free(table->p), free_forks(table), false);
	return (true);
}
