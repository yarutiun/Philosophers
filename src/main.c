#include "../inc/philo.h"

int main(int argc, char **argv)
{
	data_t data;
	if(parse(&data, argc, argv) == 0)
		return(0);
	execu(&data);
	return(0);
}
