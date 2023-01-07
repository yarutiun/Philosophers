#include "../inc/philo.h"

int main(int argc, char **argv)
{
	data_t data;
	if(!(parse(&data, argc, argv)))
		return(0);
	assign_philo_threads(&data);
	execu(&data);
	return(0);
 }
