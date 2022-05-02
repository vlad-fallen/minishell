#include "minishell.h"

void	exit_d()
{
	printf("exit\n");
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
    (void)argv;
    (void)env;
	char	*str; 
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1)
		return (1);
	while (1)
	{
		str = readline("minishell $ ");
		add_history(str);
		signal(SIGQUIT, SIG_IGN);
		if (!str)
		{
			exit_d();
			return (1);
		}
		printf("%s\n", str);  
        free(str);
		break;
    }
}