# Philosophers 
### This project teaches the notion of Thread and Mutex.
The project consists in making X Philosophers live at the same time as a thread, each one has to eat, think and sleep.

Each action of a philosopher must be output like this: timestamp_in_ms X has taken a fork

⚠️ 1 philo can only eat with 2 forks in hand, and the forks cannot be shared!

💬 Example : If you throw 1 philosopher, there will be only one fork, the philosopher will not be able to eat and he will die after the time indicated in argument 1

## How to test philo :

Just do ./make
and execute with ./philo [arg1] [arg2] [arg3] [arg4] [arg5 (optionnel)]

◦ [number_of_philosophers] : is the number of philosophers and also the number of forks.

◦ [time_to_die] : is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting their last meal or the beginning of the simulation, it dies.

◦ [time_to_eat] : is in milliseconds and is the time it takes for a philosopher to eat. During that time they will need to keep the two forks.

◦ [time_to_sleep] : is in milliseconds and is the time the philosopher will spend sleeping.

◦ [number_of_times_each_philosopher_must_eat] : argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.
