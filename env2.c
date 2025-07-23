/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 18:27:10 by rduport           #+#    #+#             */
/*   Updated: 2025/07/19 18:27:10 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    count_export(t_env *env, char *new_var, int j)
{
	int	count;
	int	exist;

	exist = 0;
	count = 0;
	while (env->export[count])
	{
		if (ft_strncmp_export(env->export[count], new_var, j + 1) == 1)
			exist = 1;
		count++;
	}
	if (exist == 1)
		count--;
	return (count);
}

int    exist_in_env(t_env *env, char *new_var, int j)
{
	int	i;

	i = 0;
	while (env->export[i])
	{
		if (ft_strncmp_export(env->export[i], new_var, j + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_ascii(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
				swap(&tab[i], &tab[j]);
			j++;
		}
		i++;
	}
}


char    **export_tab(char **tab, t_env *env, char *new_var, int j)
{
    int	i;

    i = -1;
	while (env->export[++i])
	{
		if (ft_strncmp_export(env->export[i], new_var, j + 1) == 0)
			tab[i] = ft_strdup_export(new_var);
		else
			tab[i] = ft_strdup_export(env->export[i]);
		if (!tab[i])
		{
			free_tab(tab);
			return (NULL);
		}
	}
	if (exist_in_env(env, new_var, j) == 0)
		tab[i++] = ft_strdup_export(new_var);
	tab[i] = NULL;
	sort_ascii(tab);
	return (tab);
}

int	handle_error(char *new_var, t_env *env, t_parsing *parsing)
{
	if (!new_var)
	{
		display_env(env->export);
		return (1);
	}
	if (valid_env(new_var) == 1)
	{
		parsing->exit_status = 1;
		printf("minishell: export: %s: not a valid identifier\n", new_var);
		return (1);
	}
	return (0);
}

t_env	*handle_new_var(t_env *env, char *new_var, int *i)
{
	int	j;

	j = *i;
	if (new_var[*i] == '=')
	{
		env->env = ft_new_env(env->env, new_var, ++(*i), j);
		if (!env->env)
			return (env);
	}
	return (env);
}
