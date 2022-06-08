/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 13:54:13 by mbutter           #+#    #+#             */
/*   Updated: 2022/06/08 15:07:17 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*envlist_new(char *key, char *value)
{
	t_env_var	*list;

	list = (t_env_var *)malloc(sizeof(t_env_var));
	if (list != NULL)
	{
		list->key = ft_strdup(key);
		list->value = ft_strdup(value);
		list->next = NULL;
	}
	return (list);
}

void	envlist_add_back(t_env_var **lst, t_env_var *new)
{
	t_env_var	*tmp;

	if (new != NULL)
	{
		if (*lst != NULL)
		{
			tmp = *lst;
			while (tmp->next != 0)
				tmp = tmp->next;
			tmp->next = new;
		}
		else
			*lst = new;
	}
}

t_env_var	*env_to_list(char **env)
{
	t_env_var	*env_list;
	char		*key_tmp;
	char		*value_tmp;
	int			i;

	if (env == NULL)
		return (NULL);
	i = 0;
	env_list = NULL;
	while (env[i])
	{
		key_tmp = ft_substr(env[i], 0,
				ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '=')));
		value_tmp = ft_strdup(ft_strchr(env[i], '='));
		envlist_add_back(&env_list, envlist_new(key_tmp, value_tmp));
		free(key_tmp);
		free(value_tmp);
		i++;
	}
	return (env_list);
}

void	env_init(void)
{
	extern char	**environ;
	int			i;

	if (environ == NULL)
		return ;
	i = 0;
	while (environ[i] != NULL)
		i++;
	g_envp.env = (char **)malloc((i + 1) * sizeof(char *));
	if (g_envp.env == NULL)
		exit(1);
	i = 0;
	while (environ[i] != NULL)
	{
		g_envp.env[i] = ft_strdup(environ[i]);
		i++;
	}
	g_envp.env[i] = NULL;
	g_envp.status_exit = 0;
	g_envp.env_list = env_to_list(environ);
}

void	free_global_env(void)
{
	t_env_var	*tmp_env_list;
	t_env_var	*next;

	tmp_env_list = g_envp.env_list;
	arr_free(&g_envp.env);
	while (tmp_env_list)
	{
		next = tmp_env_list->next;
		free(tmp_env_list->key);
		free(tmp_env_list->value);
		free(tmp_env_list);
		tmp_env_list = next;
	}
}
