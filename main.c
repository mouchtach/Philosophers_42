/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:46:35 by ymouchta          #+#    #+#             */
/*   Updated: 2025/05/01 10:11:32 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int main(int argc, char **argv)
{
    t_table table;

    if(argc == 5 |  argc == 6)
    {
        parsing_input(&table, argv);
        if(!data_init(&table))
            return(1);
        dinner_start(&table);
        clean_table(&table);
    }
    else
    {
        printf("error\n");
        return(1);
    }
    return (0);
}