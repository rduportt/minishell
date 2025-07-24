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

t_parsing	*init_structure(t_token *lexer)
{
	t_parsing	*parsing;
	t_count		count;
	int			i;

	i = 0;
	count.cmd = 0;
	while (lexer[i].type != T_EOF)
	{
		if (lexer[i].type == T_PIPE)
			count.cmd++;
		i++;
	}
	parsing = init_parsing(count.cmd + 1);
	if (!parsing)
		return (NULL);
	prepare_args(parsing, lexer);
	return (parsing);
}
