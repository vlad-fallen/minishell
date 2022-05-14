#include "minishell.h"

int	pwd(void)
{
	char *str;

	str = NULL;
	str = getcwd(str, 0);
	if (str == NULL)
	{
		exit(EXIT_FAILURE);
	}
	printf("%s\n", str);
	free(str);
	return (EXIT_SUCCESS);
}