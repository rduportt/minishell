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

t_parsing	*ft_parsing(t_token *lexer, char **env)
{
	t_parsing	*parsing;

	parsing = init_structure(lexer);
	if (!parsing)
		return (NULL);
	if (!fill_parsing(parsing, lexer, env))
		return (return_null_parsing(parsing, parsing[0].count));
	parsing[parsing[0].count].cmd = NULL;
	return (parsing);
}

int	has_simple_quote(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	has_double_quote(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	is_dollar(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	is_quote_closed(char *string)
{
	int	i;
	int	quote1;
	int	quote2;

	quote1 = 0;
	quote2 = 0;
	i = 0;
	while (string[i])
	{
		if (string[i] == '\'' && quote2 % 2 == 0)
			quote1++;
		if (string[i] == '"' && quote1 % 2 == 0)
			quote2++;
		i++;
	}
	if (quote1 % 2 != 0 || quote2 % 2 != 0)
	{
		printf("quote not closed");
		return (1);
	}
	return (0);
}
