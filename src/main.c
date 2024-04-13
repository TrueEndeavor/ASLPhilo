/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:58:30 by lannur-s          #+#    #+#             */
/*   Updated: 2024/04/13 21:15:13 by lannur-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_feast	*feast;
	t_philo	*philo;

	if (!get_args(argc, argv))
		return (1);
	feast = (t_feast *) malloc (ft_atoi(argv[NUM_PHILO]) * sizeof(t_feast));
	if (!feast)
		return (1);
	if (!initialize_feast(argc, argv, feast))
	{
		free(feast);
		return (1);
	}
	philo = (t_philo *)malloc (feast->num_philo * sizeof(t_philo));
	if (!philo)
	{
		free(feast);
		return (1);
	}
	feast->philo_array = philo;
	create_philo_threads(feast, philo);
	bruce_almighty(feast);
	destroy_philo_threads(feast, philo);
	cleanup_feast(feast);
	return (0);
}
