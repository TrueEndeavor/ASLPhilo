/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:09:35 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/13 19:05:44 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_validity(int argc, char *argv[])
{
	if (ft_atoi(argv[NUM_PHILO]) <= 0 || \
		ft_atoi(argv[TIME_TO_DIE]) < 60 || \
		ft_atoi(argv[TIME_TO_EAT]) < 60 || \
		ft_atoi(argv[TIME_TO_SLEEP]) < 60 || \
		(argc == 6 && ft_atoi(argv[MEAL_LIMIT]) < 1))
	{
		printf("Error: Invalid arguments\n\n");
		return (false);
	}
	return (true);
}

bool	get_args(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid arguments.\n");
		printf(" Run the program with inputs for following parameters:\n");
		printf("       - 🧠 Number of philos (max 200)\n");
		printf("       - 🚫 Waiting time (ms) (min 60ms)\n");
		printf("       - 🍽️ Eating time (ms)(min 60ms)\n");
		printf("       - 😴 Sleep time (ms)(min 60ms)\n");
		printf("       - 🍜 [Meal limit] (min 1, max 20)\n");
		printf("   Example: ./philo 2 60 60 60 [3]\n\n");
		return (false);
	}
	return (check_validity(argc, argv));
}
