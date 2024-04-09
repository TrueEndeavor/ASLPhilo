#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_PHILOSOPHERS 200

typedef struct SHARED_STRUCT
{
	int num_guests;
	int waiting_time;
	int eating_time;
	int sleep_time;
	int meal_limit;

	pthread_mutex_t forks[NUM_PHILOSOPHERS];
	pthread_mutex_t print_mutex;
} t_shared;

typedef struct PHILO_STRUCT
{
	int id;
	int meals_eaten;

	t_shared *data;
} t_philo;

void print_message(int id, const char *message, t_shared *data)
{
	pthread_mutex_lock(&(data->print_mutex));
	printf("[%d] %s\n", id, message);
	pthread_mutex_unlock(&(data->print_mutex));
}

void *philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_shared *data = philo->data;
	int id = philo->id;
	int right_fork = id;
	int left_fork = (id + 1) % NUM_PHILOSOPHERS;

	while (1) {

		// Acquire forks
		pthread_mutex_unlock(&(data->forks[id]));
		pthread_mutex_unlock(&(data->forks[(id + 1) % data->num_guests]));

		// Start eating
		pthread_mutex_lock(&(data->forks[id]));
		printf("Philosopher %d picked up the right chopstick\n", id + 1);
   
		pthread_mutex_lock(&(data->forks[(id + 1) % data->num_guests]));
		printf("Philosopher %d picked up the left chopstick\n", id + 1);
		print_message(id, "started eating", data);
		sleep(rand() % 3 + 1); // Simulate eating
		// Release forks
		pthread_mutex_unlock(&(data->forks[right_fork]));
		pthread_mutex_unlock(&(data->forks[left_fork]));
	   
		// Increment meals eaten
		philo->meals_eaten++;

		// Check if meals eaten limit reached
		if (philo->meals_eaten >= data->meal_limit) {
			break;
		}

		// Start thinking
		print_message(id + 1, "started thinking", data);
		sleep(rand() % 3 + 1); // Simulate thinking
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc < 5 || argc > 6) {
		printf("❗❗❗Error: Invalid arguments. Please provide the following parameters❗❗❗\n");
		printf(" 🎉🎉🎉🎉🎉 Dining Philosophers Solution 🎉🎉🎉🎉🎉\n");
		printf(" Run the program with inputs for following parameters:\n");
		printf("       - 🧠 Number of guests (max 200)\n");
		printf("       - 🚫 Waiting time (ms) (min 60ms)\n");
		printf("       - 🍽️ Eating time (ms)(min 60ms)\n");
		printf("       - 😴 Sleep time (ms)(min 60ms)\n");
		printf("       - 🍜 [Meal limit] (min 1, max 20)\n");
		printf("   Example: ./philo 1 60 60 60 [3]\n\n");
		return 1;
	}

	// Parse command-line arguments and init shared data
	t_shared data;
	data.num_guests = atoi(argv[1]);
	data.waiting_time = atoi(argv[2]);
	data.eating_time = atoi(argv[3]);
	data.sleep_time = atoi(argv[4]);
	data.meal_limit = (argc == 6) ? atoi(argv[5]) : 0;

	// Check validity of arguments
	if (data.num_guests <= 0 || data.num_guests > NUM_PHILOSOPHERS ||
		data.waiting_time < 60 || data.eating_time < 60 || data.sleep_time < 60 ||
		(argc == 6 && (data.meal_limit < 1 || data.meal_limit > 20))) {
		printf("❗❗❗Error: Invalid arguments. Please provide valid parameters❗❗❗\n\n");
		return 1;
	}

	srand(time(NULL));

	int	i;

	i = 0;
	// Initialize mutexes of shared data
	pthread_mutex_init(&(data.print_mutex), NULL);
	while (i < data.num_guests)
	{
		pthread_mutex_init(&(data.forks[i]), NULL);
		i++;
	}

	i = 0;
	// Initialize philosophers
	t_philo philo[data.num_guests];
	while (i < data.num_guests)
	{
		philo[i].id = i;
		philo[i].meals_eaten = 0;
		philo[i].data = &data;
		i++;
	}

	i = 0;
	// Create philosopher threads
	pthread_t threads[data.num_guests];
	while (i < data.num_guests)
	{
		if (pthread_create(&(threads[i]), NULL, philosopher_routine, &(philo[i])) != 0)
		{
			printf("Error creating thread %d\n", i);
			return 1;
		}
	}

	i = 0;
	// Wait for philosopher threads to finish
	while (i < data.num_guests)
	{
		pthread_join(threads[i], NULL);
		i++;
	}

	// Clean up mutexes
	pthread_mutex_destroy(&(data.print_mutex));
	for (int i = 0; i < data.num_guests; i++) {
		pthread_mutex_destroy(&(data.forks[i]));
	}

	return 0;
}
