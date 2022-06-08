/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:02:53 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/08 21:03:36 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_help_part_two(t_env_var	*copy_list, char **n_env, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(copy_list->key);
	if (copy_list->value)
	{
		tmp2 = ft_strdup(copy_list->value);
		n_env[i] = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
	}
	else
		n_env[i] = tmp;
	tmp = NULL;
	tmp2 = NULL;
}

void	update_env_help(t_env_var	*copy_list, int i)
{
	char	**new_env;

	arr_free(&g_envp.env);
	g_envp.env = NULL;
	new_env = (char **)malloc((i + 2) * sizeof(char *));
	i = 0;
	while (copy_list)
	{
		update_env_help_part_two(copy_list, new_env, i);
		copy_list = copy_list->next;
		i++;
	}
	new_env[i] = NULL;
	g_envp.env = new_env;
}

void	update_env(t_env_var *env_list)
{
	t_env_var	*copy_list;
	int			i;

	i = 0;
	copy_list = env_list;
	while (copy_list)
	{
		copy_list = copy_list->next;
		i++;
	}
	copy_list = env_list;
	update_env_help(copy_list, i);
}
