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

int	get_count(char **env, char *new_var, int i, int *exist)
{
	int	count;

	count = 0;
	while (env[count])
	{
		if (ft_strncmp(env[count], new_var, i) == 0)
			*exist = 1;
		count++;
	}
	return (count);
}

t_env	*ft_export_questionmark(t_env *env, int exit_code)
{
	int		i;
	int		j;
	char	*temp;
	char	*temp2;

	temp2 = ft_itoa(exit_code);
	temp = ft_strjoin("?=", temp2);
	i = 0;
	while (temp[i] != '=')
		i++;
	j = i;
	if (temp[i] == '=')
	{
		i++;
		env->env = ft_new_env(env->env, temp, i, j);
		if (!env->env)
		{
			free(temp);
			free(temp2);
			return (env);
		}
	}
	free(temp);
	free(temp2);
	return (env);
}

t_env	*ft_export(t_env *env, char **new_var, t_parsing *parsing)
{
	int		i;
	int		var_i;
	int		count;
	char	**tab;
	int		j;

	i = -1;
	if (handle_error(new_var[0], env, parsing))
		return (env);
	while (new_var[++i])
	{
		if (handle_error(new_var[i], env, parsing))
			return (env);
		var_i = 0;
		while (new_var[i][var_i] && (ft_isalpha(new_var[i][var_i])
			|| ft_isdigit(new_var[i][var_i])))
			var_i++;
		j = var_i;
		env = handle_new_var(env, new_var[i], &var_i);
		count = count_export(env, new_var[i], j);
		tab = malloc(sizeof(char *) * (count + 3));
		if (!tab)
			return (NULL);
		tab = export_tab(tab, env, new_var[i], j);
		free_tab(env->export);
		env->export = tab;
	}
	return (env);
}

char	*check_env(char **env, char *string)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	tab = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && string[j] &&
			string[j] == env[i][j] && env[i][j] != '=')
			j++;
		if (string[j] == '\0' && env[i][j] == '=')
		{
			tab = ft_strdup(&env[i][j + 1]);
			break ;
		}
		i++;
	}
	if (!tab)
		return (NULL);
	return (tab);
}
