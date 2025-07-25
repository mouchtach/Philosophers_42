/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:23:53 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/20 17:28:00 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	init_table(t_table *table)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	table->start_time = get_time();
	table->forks = sem_open("/forks", O_CREAT, 0644, table->nb_philo);
	table->print = sem_open("/print", O_CREAT, 0644, 1);
	if (table->forks == SEM_FAILED || table->print == SEM_FAILED
		|| table->death == SEM_FAILED)
	{
		printf(SEMA_ERROR);
		return (false);
	}
	table->pid = malloc(sizeof(pid_t) * table->nb_philo);
	if (!table->pid)
	{
		printf(MALLOC_ERROR);
		return (false);
	}
	return (true);
}

void	cleanup(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->print);
	sem_unlink("/forks");
	sem_unlink("/print");
	free(table->pid);
}

void	kill_philos(t_table *table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		kill(table->pid[i], SIGKILL);
		i++;
	}
}
