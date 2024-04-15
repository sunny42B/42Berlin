/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhassoun <fhassoun@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:15:56 by fhassoun          #+#    #+#             */
/*   Updated: 2023/08/02 15:43:59 by fhassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define EMPTY 0
# define CMD 1
# define IN 2   // <
# define OUT 3  // >
# define PIPE 4 // |
# define APP 5  // >>
# define ARG 6
# define FLAG 7 // -
# define HERED 8

# define DQUOTE 9
# define SQUOTE 10
# define SPC 11
# define DOLLAR 12

/*
** Global Variable
*/
// typedef struct s_env
// {
// 	int exit_status;
// } t_env;

// extern t_env g_exit;
extern int			g_exit_status;
// extern volatile sig_atomic_t child_running;

typedef struct s_token
{
	char			*name;
	int				type;
	int				quotes;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_exe
{
	char			*com;
	char			**exec;
	int				type;
	int				end[2];
	int				fd_in;
	int				fd_out;
}					t_exe;

typedef struct s_shell
{
	t_list			*node;
	t_list			*head;

	char			*prompt;
	char			**com;
	int				units;
	char			**mypaths;
	char			*command;
	char			*cwd;
	char			**env;
	int				prev_fd;
	t_token			**token;
	t_exe			*final;
	int				fd[1024];

	pid_t			pid[1024];
	int				end[2];
	int				fd_in;
	int				fd_out;
}					t_shell;

/* typedef struct s_split
{
	char	**cmd;
	char	*buf;
	char	*str;
	int		i;
	int		j;
	int		k;
}	t_split; */

/*
** main.c
*/
void				check_args(int argc, char *argv[], char *envp[],
						t_shell *shell);
void				free_com(t_shell *shell);
int					print_exe_arr(t_shell *shell, t_exe *arr);

/*
** main.c
*/
void				free_com(t_shell *shell);
void				clean_up(t_shell *shell);

/*
** handle_envp.c
*/
void				handle_envp(t_shell *shell, char *envp[]);
char				*find_path(char **envp);
void				print_env(t_shell *shell);
void				get_new_env(t_shell *shell);

/*
** some_funcs.c
*/
void				export_no_arg(t_shell *shell);
void				ft_realloc_add_string(t_shell *shell, char *new);
void				ft_realloc_del_string(t_shell *shell, char *out);
void				ft_echo(t_shell *shell, int unit, int len);
int					check_export(t_shell *shell, int unit, int j);
int					export_valid_var(char *str);

/*
** some_funcs.c
*/
void				strg_swap(char **a, char **b);
void				sort_arr(char **arr, int len);
char				*remove_after_eq(char *str);

/*
** dollar.c
*/
void				check_dollar_node(t_shell *shell);
char				*replace_substring(char *str, const char *substr,
						char *replacement);
char				*get_variable(t_shell *shell, char *buf);
void				replaceSubstring(t_shell *shell, char *str,
						const char *substr, char *replacement);
void				check_for_dollar(t_shell *shell);

/*
** dollar_utils.c
*/
int					dollar_breaks(t_shell *shell, t_token **token);
int					not_squote_qm_digit(t_token **token, char *dup, char *buf);
void				is_digit_norminette_bitch(char **string_char, char **buf,
						char **qm);
/*
** signals.c
*/
int					signals(void);
void				handle_cmd(int sig);
void				handle_sig_here(int sig);

/*
** signal_utils.c
*/
void				signal_handler(int signum);
void				handle_cmd_signals(void);
void				signal_action_here(void);

/*
** minishell.c
*/

int					executer(t_shell *shell);

/*
** minishell_utils.c
*/
void				ft_free(char **str);

int					try_command(t_shell *shell, int i);
int					try_command2(t_shell *shell, int j);
void				set_token_type(t_shell *shell, t_token **token, int i);
int					is_built_in(char *str);
int					is_not_built_in(t_shell *shell, char *str);

/*
** parser.c
*/
int					pre_parser(t_shell *shell);
int					parser(t_shell *shell);
// void	print_list(t_lst **list);

/*
** lexer1.c
*/
int					lexer(t_shell *shell);
void				lex_cpy(t_shell *shell, int *i, int len);
void				lex_split2(t_shell *shell, int *i, char c, int len);
void				lex_redirect(t_shell *shell, int *i, char c);

/*
** lexer2.c
*/
int					pre_expander(t_shell *shell);
int					is_redirect(int type);
void				ft_expander(t_token *token, int *units);
void				set_token_type2(t_shell *shell, t_token *token);
void				use_set_token_type(t_shell *shell, t_token *token);
int					is_redirect_char(char c);
int					fill_tokens(t_shell *shell, int *i, int len);
// t_exe	*list_last(t_exe *head);
// int	insert_last(t_shell *shell, t_exe *ex);
// t_exe	*exe_list_new(char **ex, int typ);

char				**parser_cmd(t_shell *shell, t_token **token);
char				**parser_redirect(t_shell *shell, t_token **token);
int					ft_parser_lstlst(t_shell *shell);
void				free_exe_arr(t_shell *shell, t_exe *list);

/*
** lexer_helper.c   token list funcs
*/
t_token				*ft_token_last(t_token *list);
void				ft_del_token(t_shell *shell, t_token *node);
t_token				*ft_token_new(char *strg, int typ);
void				ft_token_add_back(t_token **list, t_token *new);
void				del_space_nodes(t_shell *shell);

void				join_when_no_spaces(t_shell *shell);
void				print_lexer(t_shell *shell);
void				free_lexer(t_shell *shell);
void				check_for_dollar(t_shell *shell);
void				replace_dollar(t_shell *shell, char *buf);

/*
** expander.c
*/
t_exe				*list_last(t_exe *head);
int					insert_last(t_shell *shell, t_exe *ex);
t_exe				*exe_list_new(char **ex, int typ);
int					pre_expander(t_shell *shell);
int					is_redirect(int type);

int					print_exe_list(t_shell *shell);
int					print_exe_arr(t_shell *shell, t_exe *arr);
int					test(t_shell *shell);
t_exe				*ft_exe_new(char **arr, int typ);
t_exe				*ft_exe_last(t_exe *list);
void				ft_exe_add_back(t_exe **lst, t_exe *new);
void				free_exe(t_exe **node);
void				free_exe_arr(t_shell *shell, t_exe *list);
void				free_executer(t_shell *shell);

/*
** redirect.c
*/
void				here_doc(t_shell *shell, int i);
void				print_here_doc(t_shell *shell);
void				append(t_shell *shell, int i);
void				redirect_in(t_shell *shell, int i);
void				redirect_out(t_shell *shell, int i);

/*
** redirect_utils.c
*/
void				test1(int fd);
void				del_node(t_list **node);

/*
** executer.c
*/
void				handle_out_redir(t_shell *shell, int i);

/*
** executer_utils.c
*/
void				run_cd(t_shell *shell, int i);
void				run_echo(t_shell *shell, int unit);
// void				run_export(t_shell *shell, int unit);
int					run_export(t_shell *shell, int unit);
void				run_unset(t_shell *shell, int unit);
void				part_of_echo(t_shell *shell, int unit, int *n_pos,
						int *n_flag);

/*
** executer_helper_one.c
*/
int					open_input_file(char *filename, t_shell *shell);
void				check_redir(t_shell *shell);
void				init_shell(t_shell *shell);
void				prepare_redirection(t_shell *shell);
int					execute_single_command(t_shell *shell, int i);

/*
** executer_helper_two.c
*/
int					open_append_file(char *filename);
int					open_output_file(char *filename);
int					is_redirection_valid(char *filename, t_shell *shell, int i);
void				run_child(t_shell *shell, int i);
void				handle_external_cmd(t_shell *shell, int i);
/*
** executer_helper_three.c
*/
void				run_built_in(t_shell *shell, int i);
int					run_builtin_no_fork(t_shell *shell, int i);
void				handle_here_doc(t_shell *shell, int i);
void				check_single(t_shell *shell, int i);
void				run_env(t_shell *shell);
#endif
