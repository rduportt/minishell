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

void	prepare_args(t_parsing *parsing, t_token *lexer)
{
	int		i;
	int		j;
	t_count	count;

	i = 0;
	j = 0;
	while (lexer[i].type != T_EOF)
	{
		count = count_init();
		while (lexer[i].type != T_EOF && lexer[i].type != T_PIPE)
			update_count(&count, lexer[i++].type);
		allocate_cmd(parsing, j++, count);
		if (lexer[i].type == T_PIPE)
			i++;
	}
	parsing[0].count = j;
}

int	expand_string_if_needed(t_token *tok, char **env)
{
	char	*tmp;

	if (is_quote_closed(tok->string) == 1)
		return (0);
	while (is_dollar(tok->string))
	{
		tmp = string_env(tok->string, env);
		if (!tmp)
			return (0);
		if (ft_strcmp(tmp, tok->string) == 0)
		{
			free(tmp);
			break ;
		}
		free(tok->string);
		tok->string = tmp;
	}
	return (1);
}

void	assign_token(t_parsing *p, t_token *tok, t_count *c)
{
	char	*str;

	str = exctract_file_name(tok->string);
	if (tok->type == T_WORD && (c->arg == 0 || tok[-1].type == T_PIPE))
	{
		p->cmd = ft_strdup(str);
		p->arg[c->arg++] = ft_strdup(str);
		p->arg[c->arg] = NULL;
	}
	else if (tok->type == T_WORD)
	{
		p->arg[c->arg++] = ft_strdup(str);
		p->arg[c->arg] = NULL;
	}
	else if (tok->type == T_REDIR_IN)
		p->infile[c->infile++] = ft_strdup(str);
	else if (tok->type == T_REDIR_OUT)
		p->outfile[c->outfile++] = ft_strdup(str);
	else if (tok->type == T_REDIR_APPEND)
		p->append[c->append++] = ft_strdup(str);
	else if (tok->type == T_REDIR_HEREDOC)
		p->heredoc[c->heredoc++] = ft_strdup(str);
	free(str);
}

int	parse_one_cmd(t_parsing *p, t_parse_ctx *ctx, t_count *c)
{
	while (ctx->lexer[*(ctx->i)].type != T_EOF
		&& ctx->lexer[*(ctx->i)].type != T_PIPE)
	{
		if (!expand_string_if_needed(&ctx->lexer[*(ctx->i)], ctx->env))
			return (0);
		assign_token(p, &ctx->lexer[*(ctx->i)], c);
		(*(ctx->i))++;
	}
	p->arg[c->arg] = NULL;
	p->outfile[c->outfile] = NULL;
	p->infile[c->infile] = NULL;
	p->append[c->append] = NULL;
	p->heredoc[c->heredoc] = NULL;
	if (c->arg == 0)
		p->cmd = NULL;
	return (1);
}

int	fill_parsing(t_parsing *parsing, t_token *lexer, char **env)
{
	int				i;
	int				j;
	t_count			count;
	t_parse_ctx		ctx;

	i = 0;
	j = 0;
	ctx.lexer = lexer;
	ctx.i = &i;
	ctx.env = env;
	while (lexer[i].type != T_EOF)
	{
		count = count_init();
		if (!parse_one_cmd(&parsing[j], &ctx, &count))
			return (0);
		j++;
		if (lexer[i].type == T_PIPE)
		i++;
	}
	parsing[0].count = j;
	return (1);
}
