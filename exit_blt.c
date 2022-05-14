#include "minishell.h"

int exit_blt(t_table_cmd *table)
{
	(void)table;

	write(2, "exit\n", 5);
	exit (0);
	return (0);
}