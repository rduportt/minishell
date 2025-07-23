/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal2.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: tirimesc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:38:52 by tirimesc          #+#    #+#             */
/*   Updated: 2024/11/12 16:08:42 by tirimesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*get_env_value(char *string, int *i, char **env)
{
	char	*env_name;
	char	*env_value;

	env_name = extract_env_name(string, i);
	if (!env_name)
		return (NULL);
	env_value = check_env(env, env_name);
	free(env_name);
	if (!env_value)
		env_value = ft_strdup("");
	return (env_value);
}

char	*assemble_result(char *string, char *env_value, int i, int *j)
{
	char	*result;
	int		k;

	result = malloc(ft_strlen(string) + ft_strlen(env_value) + 1);
	if (!result)
		return (NULL);
	*j = copy_before_var(string, result);
	result[*j] = '\0';
	ft_strcat(result, env_value);
	*j += ft_strlen(env_value);
	k = *j;
	while (string[i])
		result[k++] = string[i++];
	result[k] = '\0';
	return (result);
}