
#include "pipex.h"
#include "/printf/ft_printf.h"

int pase_args(int argc, char **argv, char **envp)
{
	(void)envp;
	if (argc != 5)
	{
		ft_printf("%s", "Error: wrong number of arguments\n");
		return (-1);
	}
	return (0);
}
