/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:09:35 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/12 20:03:03 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_validity(int argc, char *argv[])
{
	
	if (ft_atoi(argv[NUMBER_OF_PHILO]) <= 0 || \
		ft_atoi(argv[TIME_TO_DIE]) < 60 || \
		ft_atoi(argv[TIME_TO_EAT]) < 60 || \
		ft_atoi(argv[TIME_TO_SLEEP]) < 60 || \
		(argc == 6 && ft_atoi(argv[MEAL_LIMIT]) < 1))
	{
		printf("❗❗❗Error: Invalid arguments. Please provide valid parameters❗❗❗\n\n");
		return (false);
	}
	return (true);
}

bool	get_args(int argc, char *argv[])
{
	if (argc < 5 || argc > 6) 
	{
		printf("❗❗❗Error: Invalid arguments. Please provide the following parameters❗❗❗\n");
		printf(" 🎉🎉🎉🎉🎉 Dining Philosophers Solution 🎉🎉🎉🎉🎉\n");
		printf(" Run the program with inputs for following parameters:\n");
		printf("       - 🧠 Number of guests (max 200)\n");
		printf("       - 🚫 Waiting time (ms) (min 60ms)\n");
		printf("       - 🍽️ Eating time (ms)(min 60ms)\n");
		printf("       - 😴 Sleep time (ms)(min 60ms)\n");
		printf("       - 🍜 [Meal limit] (min 1, max 20)\n");
		printf("   Example: ./philo 1 60 60 60 [3]\n\n");
		return (false);
	}
	return (check_validity(argc, argv));
}