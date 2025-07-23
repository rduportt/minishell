/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:04:10 by rduport           #+#    #+#             */
/*   Updated: 2025/05/13 17:35:41 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**ft_new_env(char **env, char *new_var, int i, int j)
{
	int		count;
	int		exist;
	char	**tab;

	exist = 0;
	count = 0;
	count = get_count(env, new_var, i, &exist);
	tab = malloc(sizeof(char *) * (count + 2 - exist));
	if (!tab)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], new_var, j + 1) == 0)
			tab[i] = ft_strdup(new_var);
		else
			tab[i] = ft_strdup(env[i]);
		if (!tab[i])
			return (free_tab(tab), NULL);
	}
	if (exist == 0)
		tab[i++] = ft_strdup(new_var);
	tab[i] = NULL;
	free_tab(env);
	return (tab);
}

int	is_delete(char *env, char **delete_var)
{
	int	env_lenght;
	int	i;

	i = -1;
	while (delete_var[++i])
	{
		env_lenght = ft_strlen(delete_var[i]);
		if (ft_strncmp(env, delete_var[i], env_lenght) == 0
			&& env[env_lenght] == '=')
			return (1);
	}
	return (0);
}

char	**fill_new_env(t_env *env, char **delete_var, char **new_env)
{
	int	found_var;
	int	i;
	int	j;

	j = 0;
	i = -1;
	found_var = 0;
	while (env->env[++i])
	{
		found_var = is_delete(env->env[i], delete_var);
		if (found_var == 0)
			new_env[j++] = ft_strdup(env->env[i]);
	}
	new_env[j] = NULL;
	return (new_env);
}

t_env	*ft_unset(t_env *env, char **delete_var)
{
	int		i;
	int		found_var;
	char	**new_env;

	i = -1;
	found_var = 0;
	if (!delete_var)
		return (env);
	while (env->env[++i])
		found_var += is_delete(env->env[i], delete_var);
	if (found_var == 0)
		return (env);
	new_env = malloc(sizeof(char *) * (i - found_var + 1));
	if (!new_env)
		return (env);
	new_env = fill_new_env(env, delete_var, new_env);
	free_tab(env->env);
	env->env = new_env;
	return (env);
}

int	valid_env(char *new_var)
{
	int	i;

	i = 0;
	while (new_var[i] != '=' && new_var[i])
	{
		if (ft_isalnum(new_var[i]) == 0 && new_var[i] != '_'
			&& new_var[i] != '=')
			return (1);
		i++;
	}
	return (0);
}
