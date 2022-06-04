/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:55:40 by echrysta          #+#    #+#             */
/*   Updated: 2022/06/04 20:50:46 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

static void	print_value(char *str)
{
	int	i;

	i = 1;
	//printf("str[i] = %s\n", str);
	while (str[i])
	{
		//printf("str[i] = %c\n", str[i]);
		if (str[i] == '"' || str[i] == '$')
		{
			ft_putchar_fd('\\', STDOUT_FILENO);
		}
		ft_putchar_fd(str[i], STDOUT_FILENO);
		i++;
	}
	
}

static void	print_declare(char *key)
{
	t_env_var *env;
	
	env = g_envp.env_list;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			ft_putstr_fd("export ", STDOUT_FILENO);
			ft_putstr_fd(env->key, STDOUT_FILENO);
			if (env->value)
			{
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putchar_fd('"', STDOUT_FILENO);
				print_value(env->value);
				ft_putchar_fd('"', STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
			return ;
		}
		env = env->next;
	}	
}

static void	print_sorted_e(t_env_var *env)
{
	char	*previous;
	char	*actual;
	t_env_var	*tmp_env_val;
	t_env_var	*tmp_val;

	tmp_env_val = env;
	if (tmp_env_val)
	{
		previous = NULL;
		while (tmp_env_val)
		{
			tmp_val = env;
			actual = NULL;
			while (tmp_val)
			{
				if ((!previous || strcmp(tmp_val->key, previous) > 0)
					&& (!actual || strcmp(tmp_val->key, actual) < 0))
					actual = tmp_val->key;
				tmp_val = tmp_val->next;
			}
			print_declare(actual);
			previous = actual;
			tmp_env_val = tmp_env_val->next;
		}
	}
}

static t_env_var	*envlist_new_alone(char	*key)
{
	t_env_var	*list;

	list = (t_env_var *)malloc(sizeof(t_env_var));
	if (list != NULL)
	{
		list->key = ft_strdup(key);
		list->value = NULL;
		list->next = NULL;
	}
	return (list);
}

static int	check_argc(char *str)
{
	char ch;
	int	i;

	i = 1;
	//printf("str = %s\n", str);
	ch = str[0];
	if (!(97 <= ch && ch <= 122) && !(65 <= ch && ch <= 90))
	{
		ft_putstr_fd("zhs: export: '", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		//printf("CHAR = %c\n", str[i]);
		return (EXIT_FAILURE);
	}
	while (str[i] != '=' && str[i])
	{
		ch = str[i];
		if (!(97 <= ch && ch <= 122) && !(65 <= ch && ch <= 90) && !(48 <= ch && ch <= 57))
		{
			ft_putstr_fd("zhs: export: '", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			//printf("CHAR = %c\n", str[i]);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	change_val_ex(t_env_var	*list, char *val)
{
	char	*new_val;
	//int		len;
	
	if (ft_strlen(val) == 1)
	{
		free(list->value);
		new_val = (char *)malloc(sizeof(char) * 1);
		new_val[0] = '\0';
		list->value = new_val;
		return ;
	}
	else
	{
		free(list->value);
		//len = ft_strlen(val);
		list->value = val;
		return ;
	}
}

static int	add_elem_env(char *str, t_env_var *env_list)
{
	t_env_var	*new_env_list;
	t_env_var	*copy_env_list;
	char		*key;
	char		*value;
	int			i;

	key = NULL;
	value = NULL;
	copy_env_list = env_list;
	i = 0;
	if (check_argc(str))
		return (EXIT_FAILURE);
	while (str[i] != '=' && str[i] != '\0')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';	
	if (str[i] != '\0' && str[i])
	{
		value = strdup(&str[i]);
	}
	//printf("STR = %s\n", str);
	//printf("VAL = %s\n", value);
	while (copy_env_list)
	{
		if (check_str(copy_env_list->key, key) && ft_strlen(copy_env_list->key) == ft_strlen(key))
		{
			if (value)
				change_val_ex(copy_env_list, value);
			return (EXIT_SUCCESS);
		}
		copy_env_list = copy_env_list->next;
	}	
	while (env_list->next)
		env_list = env_list->next;
	if (value != NULL)
		new_env_list = envlist_new(key, value);
	else
		new_env_list = envlist_new_alone(key);
	envlist_add_back(&env_list, new_env_list);
	return (EXIT_SUCCESS);
}

void	update_env(t_env_var *env_list)
{
	char		**new_env;
	t_env_var	*copy_list;
	int			i;
	char		*tmp;
	char		*tmp2;
	
	i = 0;
	copy_list = env_list;
	while (copy_list)
	{
		copy_list = copy_list->next;
		i++;
	}
	new_env = (char **)malloc((i + 1) * sizeof(char *));
	copy_list = env_list;
	i = 0;
	//printf("key =%s\n", env_list->key);
	//printf("val =%s\n", env_list->value);
	while (copy_list)
	{
		tmp = ft_strdup(copy_list->key);
		if (copy_list->value)
		{
			tmp2 = ft_strdup(copy_list->value);
			new_env[i] = ft_strjoin(tmp, tmp2);
		}
		else
			new_env[i] = tmp;
		tmp = NULL;
		tmp2 = NULL;
		copy_list = copy_list->next;
		i++;
	}
	//printf("lol\n");
	//arr_free(&g_envp.env);
	//printf("new_env[0] =%s\n", new_env[0]);
	g_envp.env = new_env;
	//print_list_arguments(new_env);
}

int	export_fun(t_table_cmd *table)
{
	t_env_var	*env_list;
	int			i;

	env_list = g_envp.env_list;
	if (!table->arguments[1])
	{
			print_sorted_e(g_envp.env_list);
		return (EXIT_SUCCESS);
	}
	i = 1;
	while (table->arguments[i])
	{
		if (add_elem_env(table->arguments[i], env_list))
			return (EXIT_FAILURE);
		i++;
	}
	update_env(env_list);
	return(EXIT_SUCCESS);
}