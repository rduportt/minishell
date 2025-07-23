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

#ifndef MINISHELL_H
# define MINISHELL_H

# include "signal.h"
# include "unistd.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "limits.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "signal.h"
# include "libft/libft.h"
# include <sys/ioctl.h>
# include <asm/termbits.h>
# include <errno.h>

extern pid_t	g_child_pid;

typedef enum e_token
{
	T_INVALID,
	T_WORD,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_PIPE,
	T_REDIR_APPEND,
	T_REDIR_HEREDOC,
	T_EOF
}	t_token_type;

typedef struct s_env
{
	char	**env;
	char	**export;
}	t_env;

typedef struct s_count
{
	int	cmd;
	int	arg;
	int	infile;
	int	outfile;
	int	append;
	int	heredoc;
}	t_count;

typedef struct s_lexer_count {
	int	i;
	int	words;
	int	buffer;
}	t_lexer_count;

typedef struct s_token
{
	char			*string;
	t_token_type	type;
}	t_token;

typedef struct s_parse_ctx
{
	t_token	*lexer;
	int		*i;
	char	**env;
}	t_parse_ctx;

typedef struct s_cd
{
	char	*path;
	char	old_pwd[PATH_MAX];
	char	*temp;
	char	new_pwd[PATH_MAX];
	int		ret;
}	t_cd;

typedef struct parsing
{
	char	*cmd;
	char	**arg;
	char	**infile;
	char	**outfile;
	char	**append;
	char	**heredoc;
	pid_t	pid;
	int		fd;
	char	*cmd_path;	
	int		is_built_in;
	int		exit_status;
	int		builtin_code;
	int		count;
	t_count	countt;
}t_parsing;

int			any_word(t_token *lexer);
void		free_parsing(t_parsing *parsing);
int			free_and_exit(t_env *env);
void		process_input(char *input, t_env *env);
int			actual_path(void);
int			is_valid_option(char *s);
int			echo(char **para);
int			exec_cd(char **args, t_env *env, t_parsing *parsing);
int			ft_exit(t_env *env, int (*pipes)[2], t_parsing *parsing,
				char **param);
void		free_tab(char **tab);
t_env		*init_env_i(t_env *env);
t_env		*fill_env(t_env *env, int count, char **envp);
t_env		*init_env(char **envp);
int			display_env(char **env);
int			get_count(char **env, char *new_var, int i, int *exist);
char		**ft_new_env(char **env, char *new_var, int i, int j);
int			is_delete(char *env, char **delete_var);
char		**fill_new_env(t_env *env, char **delete_var, char **new_env);
t_env		*ft_unset(t_env *env, char **delete_var);
int			valid_env(char *new_var);
int			count_export(t_env *env, char *new_var, int j);
int			exist_in_env(t_env *env, char *new_var, int j);
char		**export_tab(char **tab, t_env *env, char *new_var, int j);
int			handle_error(char *new_var, t_env *env, t_parsing *parsing);
t_env		*handle_new_var(t_env *env, char *new_var, int *i);
t_env		*ft_export(t_env *env, char **new_var, t_parsing *parsing);
char		*check_env(char **env, char *string);
t_env		*ft_export_questionmark(t_env *env, int exit_code);
void		free_array(char **array);
char		**split_path(char **envp);
char		*find_path(char **envp, char *str);
int			is_direct_path(char *cmd);
int			is_built_in(char *cmd);
t_env		*exec_builtin(t_parsing *parsing, t_env *env, int i,
				int (*pipes)[2]);
void		close_all_pipes(int (*pipes)[2], int nb_pipes);
void		wait_for_children(t_parsing *parsing, int i, int status);
int			init_pipes(int (**pipes)[2], t_parsing *parsing);
void		handle_heredoc_no_cmd(t_parsing *parsing, int i);
void		handle_append_no_cmd(t_parsing *parsing, int i);
void		handle_infile_no_cmd(t_parsing *parsing, int i);
void		handle_outile_no_cmd(t_parsing *parsing, int i);
int			handle_empty_cmd(t_parsing *parsing, int i);
void		manage_pipes(t_parsing *parsing, int (**pipes)[2], int i);
void		handle_infile_cmd(t_parsing *parsing, int i);
void		process_heredoc_input(char *delimiter,
				int heredoc_pipe, char **env);
void		handle_heredoc_cmd(t_parsing *parsing, int i,
				t_env *env, int (**pipes)[2]);
void		handle_outfile_cmd(t_parsing *parsing, int i);
void		handle_append_cmd(t_parsing *parsing, int i);
void		handle_exec(t_parsing *parsing, t_env *envp,
				int i, int (*pipes)[2]);
void		handle_child_process(t_parsing *parsing,
				int (**pipes)[2], int i, t_env *env);
int			wait_and_cleanup(int (**pipes)[2], t_parsing *parsing);
int			check_built_in(t_parsing *parsing, t_env *envp, int i,
				int (*pipes)[2]);
int			process_command(t_parsing *parsing, t_env *envp,
				int (*pipes)[2], int i);
int			handle_execution(t_parsing *parsing, t_env *envp, int (*pipes)[2]);
int			exec_cmd(t_parsing *parsing, t_env *envp);
int			prepare_commands(t_parsing *parsing, t_env *envp);
int			exec(t_parsing *parsing, t_env *envp);
int			is_redir(char s1, char s2);
char		*str_dup(const char *src, int start, int i);
void		check_redir_alloc(const char *s, int *i, int *buffer, int *words);
void		check_quote_alloc(const char *s, int *i, int *buffer);
void		split_new_word_alloc(const char *s, int *i,
				int *buffer, int *words);
char		**split_alloc(const char *s);
void		check_redir(char **split, char const *s, t_lexer_count *count);
void		check_quote(char const *s, t_lexer_count *count, char c);
void		split_new_word(char **split, char const *s,
				t_lexer_count *count, char c);
void		fill_split(char **split, char const *s,
				t_lexer_count *count, char c);
char		**ft_split_readline(char const *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
int			check_ft_lexer(char **split, t_token *lexer, int i);
t_token		*ft_lexer(char **split);
t_parsing	*return_null_parsing(t_parsing *parsing, int j);
t_count		count_init(void);
char		*exctract_file_name(char *dir);
char		*extract_env_name(char *string, int *idx);
int			copy_before_var(char *string, char *result);
char		*get_env_value(char *string, int *i, char **env);
char		*assemble_result(char *string, char *env_value, int i, int *j);
char		*string_env(char *string, char **env);
t_parsing	*init_parsing(int cmd_count);
void		allocate_cmd(t_parsing *p, int j, t_count c);
void		update_count(t_count *count, int type);
t_parsing	*init_structure(t_token *lexer);
void		prepare_args(t_parsing *parsing, t_token *lexer);
int			expand_string_if_needed(t_token *tok, char **env);
void		assign_token(t_parsing *p, t_token *tok, t_count *c);
int			parse_one_cmd(t_parsing *p, t_parse_ctx *ctx, t_count *c);
int			fill_parsing(t_parsing *parsing, t_token *lexer, char **env);
t_parsing	*ft_parsing(t_token *lexer, char **env);
int			has_simple_quote(char *string);
int			has_double_quote(char *string);
int			is_dollar(char *string);
int			is_quote_closed(char *string);
void		handler_sigint(int num);
void		handler_heredoc(int num);
int			update_pwd_vars(t_cd *cd, t_env *env, t_parsing *parsing);
int			handle_cd_path(t_cd *cd, char **args);
int			handle_cd_home(t_cd *cd);
int			print_echo(char **para, int i);
int			is_valid_option(char *s);
void		sort_ascii(char **tab);
void		handler_heredoc_cmd(int sig);
int			expand_string_if_needed_heredoc(char **string, char **env);
void		free_all_heredoc(t_parsing *parsing, t_env *env, int (**pipes)[2]);
void		free_all(t_parsing *parsing, t_env *env, int (*pipes)[2]);

#endif
