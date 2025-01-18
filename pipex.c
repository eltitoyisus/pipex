
#include "pipex.h"
#include "/printf/ft_printf.h"

int main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_printf("%s", "Error: wrong number of arguments\n");
		return (1);
	}
	if (pase_args(argc, argv, envp) == -1)
		return (1);
	return (0);
}
