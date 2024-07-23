/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:40:51 by lzaengel          #+#    #+#             */
/*   Updated: 2024/07/23 16:38:17 by lzaengel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

// INCLUDES
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include <time.h>

typedef struct s_minishell
{
	char	*prompt;
	int		i;
	char	**splitted_prompt;
	char	**env;
	char	***commands;
	t_list	*tokenized_prompt;
	int		errnum;
	int		status;
}			t_minishell;

typedef struct s_quote
{
	char	*str;
	char	*token;
	int		id;
}			t_quote;

// PROTOS
t_minishell	*_ms(int params);
int			read_line(void);
char		**prompt_splitter(char const *s);
int			print_tab(char **tab);
int			tab_size(char **tab);
int			ft_cd(char **dirtogo);
int			ft_pwd(void);
int			ft_exit(char *reason, char **prompt);
void		init_env(char **env);
int			get_index_of_varname(char *varname);
char		*get_value_of_varname(char *varname);
void		expend_env_vars(void);
void		delete_quotes(void);
int			is_pipe(char c);
void		ft_signal(int signo);
void		ft_token(void);
void		fill_list(void);
void		exec(void);
void		ft_lstprint(t_list *lst);
void		ft_pipe(void);
int			make_redir(int i, int pfd[], int *p_out);
int			ft_echo(char **cmd);
int			ft_export(char **arg);
int			ft_unset(char **arg);
int			ft_strcmp(const char *str1, const char *str2);
void		free_content(void *content);
int			ft_pexit(int exit_number);
void		free_tab(char **tab);
void		free_taboftab(char ***tab);
int			check_quotes(void);
int			check_token_grammar(void);
void		free_content(void *content);
void		pipe_error_code(void);
void		write_heredocs(void);
int			ft_error_check(char *prompt);
int			ft_search(char **prompt, char **path);
int			checkifpath(char *str);
int			ft_exec_builtins(char **prompt);
int			size_without_set(int i, int set);
int			get_size_of_var(int j, int blind);
void		skip_single_quote(int *i);
char		*calloc_var(int j, int i);
int			should_be_skipped(int i);

#endif
