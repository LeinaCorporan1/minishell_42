/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:39:22 by massavie          #+#    #+#             */
/*   Updated: 2023/02/24 16:40:05 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "lbft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define AC_BLACK "\x1b[30m"
# define AC_RED "\x1b[31m"
# define AC_GREEN "\x1b[32m"
# define AC_YELLOW "\x1b[33m"
# define AC_BLUE "\x1b[34m"
# define AC_MAGENTA "\x1b[35m"
# define AC_CYAN "\x1b[36m"
# define AC_WHITE "\x1b[37m"
# define AC_NORMAL "\x1b[m"

extern int						g_ret;

typedef struct s_element_export	t_element_export;
typedef struct s_element		t_element;

typedef struct s_element_export
{
	char				*str;
	t_element_export	*precedent;
	t_element_export	*next;
}	t_element_export;

typedef struct s_lst_env_export
{
	t_element_export	*next;
	t_element_export	*fin;
}	t_exp;

typedef struct s_element
{
	char		*str;
	t_element	*precedent;
	t_element	*next;
}t_element;

typedef struct s_lst_env
{
	t_element	*next;
	t_element	*fin;
}	t_lst_env;

// typedef	struct	s_redirect t_redirect;

typedef struct s_redirect
{
	int		stdout;
	int		stdin;
	char	*infile;
	char	*outfile;
	char	*limiter;
	int		heredoc;
	char	*content_here;
}	t_redirect;

typedef struct s_cmd
{
	struct s_cmd	*prev;
	char			*cmd;
	char			***args;
	int				cmd_quotes;
	int				value_ret;
	int				*pipes;
	t_redirect		redirect;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_quote
{
	char			*splited;
	int				found_quotes;
	int				space;
	struct s_quote	*next;
}	t_quote;

typedef struct s_token
{
	char			*token;
	int				found;
	struct s_token	*next;
}	t_token;

typedef struct s_exec
{
	char			*path;
	char			**args;
}	t_exec;

typedef struct s_mini
{
	t_lst_env	*lst_env;
	t_exp		*lst_env_export;
	t_cmd		*cmd;
	t_quote		*quotes;
	t_token		*token;
	int			ret;
	int			tok;
	char		**tab_env;
	char		***heredoc_text;
}	t_mini;
void		ft_free_heredoc(char ***heredoc_text);
void		supp_one_occ(t_lst_env *lst_env, t_exp *exp, char *string);
int			findfirstoccurence_exp(t_exp *lst_env, char *string);
/*
    --------
    BUILTINS
    --------
*/

int			echo_newline_2(char *str);

/*
    builtin_cd
*/
//1
int			cd_ivld_opt(char **bufsplit);
int			cd_too_mnyarg(void);
int			cd_cdt(char **split_buf, t_mini *mini, int fd);
int			get_pwd(int fd, t_mini *mini);
int			get_old_pwd(int fd, t_mini *mini);
int			builtin_cd(t_mini *mini, int fd, char **split_buf);
//2
int			file_noaccess(char *new_repo);
int			not_directory(char *new_repo);
void		free_diff_cd(char *path, char *buf, char *buf2, char *oldpwd);
int			diff_cd(char *new_repo, t_mini *mini, int fd);
//cd_case.c
int			cd_home(t_mini *mini, int fd);
int			cd_old_pwd(t_mini *mini, int fd);

/*
    builtin_echo
*/
void		ft_echo(char *str, int fd, int nl);
int			echo_new_line2(int i, int y, char *str);
int			echo_newline(char *str);
char		*remove_quotes_echo(char *input, int wich);
int			builtin_echo(t_cmd *cmd, int fd);
int			valid_echo(t_cmd *cmd, char *bufargs); //changed_leina

/*
    builtin_env
*/
//builtin_env.c
int			count_lst_env(t_lst_env *lst_env);
int			printlist(t_lst_env *lst_env, int fd);
int			builtin_env2(t_mini *mini, char **bufsplit, int i);
int			builtin_env(t_mini *mini, int fd, char **bufsplit);
//diff_env.c
int			env_perm_such(int i, char **bufsplit);
int			env_cmd_not_found(char **bufsplit);
int			env_ivld_opt(char *buf);
int			env_perm(char *buf);
int			env_no_such(char *buf);
//get_env.c
char		*since_car_one(char *buf, char c);
void		print_export(char *buf, int fd);
int			printlst_envxport(t_exp *lst_env_export, int fd);
char		**tab_env_aftxp(t_lst_env *lst_env);
void		get_env(t_lst_env *lst_env, char **env);
//lst_env.c
int			suppression(t_lst_env *lst_env);
int			intro(t_lst_env *lst_env, char *string);
int			free_lst_env(t_lst_env *lst_env);
t_lst_env	*initialisation(void);
t_lst_env	*introback(t_lst_env *lst_env, char *string);

/*
	builtin_exit.c
*/
//atoi_exit.c
int			ft_atoi_uns(const char *str);
int			ft_atoi_ex(const char *str);
void		ft_atoi_unsigned(const char *str);
long long	ft_atoi_exit(const char *str);
//builtin_exit.c
int			ft_numeric(char **str, t_mini *mini);
int			count_moreless(char *str);
int			check_number(char *buf);
void		base_exit(char **arg, t_mini *mini);
long long	builtin_exit(char *str, char **arg, t_mini *mini);
//diff_exit.c
void		exit_neg(long long n, char **arg, t_mini *mini);
int			exit_tmarg(char **arg, t_mini *mini);
void		exit_arg_inc(char **arg, t_mini *mini);
void		exit_mod(long long n, char **arg, t_mini *mini);
void		exit_no_arg(char **arg, t_mini *mini);
//qte_exit.c
int			ft_quote(char *str, int i, t_mini *mini);
char		*ft_split_quote(char *str, char c);
int			parse_quote(char *buf);

/*
	builtin_export
*/
//builtin_export.c
int			builtin_export(char *buf, t_mini *mini, int fd, char **bufsplit);
int			sort_buf(char *buf, char *buf2);
void		init_exp_sort(t_lst_env *lst_env, t_exp *lst_env_export);
//car_export.c
int			nocar(char *buf, char *untilgnocar, char *bufsplit);
int			notvalid_car(char *buf, char *bufsplit);
char		*until_equal_no_car(char *buf);
//diff_export.c
int			export_opt_ivld(char **bufsplit, char *untilgnocar, int i);
void		export_sim(t_mini *mini, char **bufsplit, int i, char *untilgnocar);
void		export_no_sim(t_mini *mini, char **bufsplit, int i);
void		export_no_equal(char **bufsplit, int i, t_mini *mini, char *until);
void		export_no_occ(t_mini *mini, char **bufsplit, int i, char *until);
//findocc.c
int			findoccurence(t_lst_env *lst_env, char *string);
int			findfirstoccurence(t_lst_env *lst_env, char *string);
char		*find_occ_one(t_lst_env *lst_env, char *string);
//lst_env_export.c
t_exp		*initialisation_export(void);
int			suppression_export(t_exp *lst_env);
t_exp		*introbackexpsort(t_exp *lst_env, char *string);
t_exp		*intro_export(t_exp *lst_env, char *string);
int			free_lst_env_export(t_exp *lst_env);

/*
    builtin_unset
*/
//builtin_unset.c
int			unset_event(int i, char **bufsplit);
int			unset_not_val(int i, char **bufsplit);
int			builtin_unset_one(char **bufsplit);
int			find_first_occ_exp(t_exp *lst_env, char *string);
int			builtin_unset(t_lst_env *lst_env, t_exp *exp, char **bufsplit);
//suppocc.c
int			supp_occ_null(t_lst_env *lst_env, int i);
int			supp_occ_scd(t_lst_env *lst_env, int i);
int			supp_occ(t_lst_env *lst_env, char *string);
//suppoccexp.c
int			supp_occ_export2(t_exp *lst_env, int i);
int			supp_occ_export(t_exp *lst_env, char *string);
int			supp_exp_null(t_exp *lst_env, int i);
void		supp_all_occ(t_lst_env *lst_env, t_exp *lstexp, char **bufsplit);

/*
    builtin_pwd
*/
int			option_pwd(char *buf);
int			builtin_pwd(int fd);

/*
	Check_builtins
*/
int			which_builtins_sec(t_mini *mini, int ret, char *buf, char **args);
int			which_builtins(t_mini *mini, int ret, char *buf, char **bufargs);
int			exec_which_bul(t_mini *mini, int i, char *buf, char **bufargs);
int			check_builtins(t_mini *mini, char *buf, t_cmd *cmd);

/*
	Command
*/
//args.c
int			init_cmd_quotes(t_quote *quotes, char **tab, int y);
char		**join_tmp(char	**tmp, char **tab, int y, t_quote *quotes);
char		**cmd_args_init(char **tab, t_quote *quotes, int y);
char		***init_args(char ***args, t_quote *quotes, int c, int special);
//command.c
t_cmd		*add_empty(t_cmd *stack, char **str, char ***arg, t_quote *quotes);
t_cmd		*add_back(t_cmd *lst, char **str, char ***arg, t_quote *quotes);
t_cmd		*adding_cmd(t_quote *qt, t_cmd *tmp, char **cmd_split, char ***arg);
int			init_condition(t_quote *qt, int special, char **cmd_split, int y);
void		init_cmd(t_cmd **cmd, t_quote *quotes);
//def_buf_arg.c
char		*if_def_buf_arg(char *buf);
char		*def(char *buf, int flag);
char		**def_buf_arg(t_cmd *lst, char **bufarg);
//special_cmd.c
int			special_cmd_first(int prev, int space, char *split);
int			special_cmd(t_quote *quotes, int prev_spe, char **cmd_split);
//useful_cmd.c
int			count_lst(t_cmd *lst);
int			nbr_cmd(t_cmd *cmd);
t_cmd		*free_lst(t_cmd **cmd);

/*
	Execution
*/
//execution.c
void		exit_exec(void);
int			exec(t_redirect *redirect, t_mini *mini);
//path.c
char		*path_join(char *path, char *bin);
char		*get_path_scd(char *cmd, char *s);
char		*get_path(char *cmd, char **env);
char		*ft_path(char **args, char **env);
char		**free_arg_path(char **args, char *path);
//useful_exec.c
char		*until_colon(char *path);
int			new_colon(char *path);
int			new_slash(char *path);
void		free_dir_bin(char *dir, char *bin);

/*
	Multiexec
*/
//mainpi.c
int			free_muex(int frk, char *path, char **args);
void		mufail(char **args);
void		ft_waitpid(int *pids, int argnum);
void		sure_close(int pipefd[][2], int argnum);
int			multi_exec(t_mini *mini, t_cmd *cmd);
//muexec.c
void		handle_sigint(int sig);
void		signal_execu(void);
void		dup_close_mu(int pipefd[][2], int arg, t_cmd *cmd);
int			muexec(t_cmd *cmd, int pipefd[][2], int arg, t_mini *mini);
void		init_pa(t_exec *pa, t_cmd *cmd, t_mini *mini);
//mu_exec_last.c
void		dup_close_mu2(int pipefd[][2], int arg, t_cmd *cmd);
int			mu_exec_last(t_cmd *cmd, int pipefd[][2], int arg, t_mini *mini);
//mu_mi_exec.c
void		dup_close_mi(int pipefd[][2], int arg, t_cmd *cmd);
void		close_mi(int pipefd[][2], int arg);
int			mu_mi_exec(t_cmd *cmd, int pipefd[][2], int arg, t_mini *mini);
void		exit_mu_fail(t_mini *mini, char **args, char *path, int i);

/*
	Quotes
*/
//quote_valid.c
int			quotes_identi(char c);
int			quote_valid_utils(char *to_check, int i, int quotes, int wich);
int			quotes_valid_quotes(char *to_check, int i, int quotes, int wich);
int			quote_valid(char *to_check);
//quotes.c
t_quote		*qt_joined(char *str, t_quote *qt);
t_quote		*quote_empty(t_quote *stack, char *str, int end);
t_quote		*quote_back(t_quote *lst, char *str, int end);
int			to_add(int i, char *str, int begin, t_quote *tmp);
void		checker_quotes(char *buf, t_quote **quotes, t_mini *mini);
//useful_quotes.c
char		**join_tr_utils(char **to_join, char **add);
char		***ft_join_tr(char ***args, char **add);
int			ft_strlen_triple(char ***tab);
void		free_quotes(t_quote **quotes);
char		*remove_quotes(char *input, int wich, int to_free);
//var_and_quotes.c
int			incrementation(int i, int begin, int wich, char *str);
int			valid_dollar(char *str);
char		*strdup_varia(char *str, char *to_return, t_mini *mini);
int			i_dollar(char *str, int i);
char		*checker_varia(char *str, char *ret, t_mini *mini, int quotes);

/*
	Redirection
*/
//content_heredoc.c
char		**init_content(char *limiter);
char		*found_content(char *buf, char *limiter, char *found, t_mini *mini);
//heredoc.c
void		valid_heredoc(char **content, char *limit, char *buf, t_mini *mini);
int			ft_found_heredoc(char *buf, char *heredoc);
int			ft_heredoc(char *limiter, t_mini *mini);
char		*in_herdoc(char *cmd, t_redirect *red, char **tmp, t_mini *mini);
//init_redir.c
void		init_redirect(t_redirect *redirect);
int			init_content_here(t_redirect *re, char *in, t_mini *mi);
char		*init_args_redir(t_cmd *cmd, t_redirect *red, t_mini *mini);
char		**init_cmd_redir(t_cmd *cmd);
//redirection.c
void		ft_dup_second(t_redirect *redirect, int fd[]);
void		ft_dup(t_redirect *redirect);
int			msg_error_files(int types, char *in);
int			redir_stdin(t_redirect *re, char *tmp, char *in, t_mini *mini);
int			redir_open(t_redirect *redirect, char *tmp, char *in, t_mini *mini);
char		*redir_valid(char ***args, t_redirect *re, t_mini *mini, int i);
char		*ft_redirect(t_cmd *cmd, t_redirect *redirect, t_mini *mini);
//useful_redir.c
int			redir(char c);
int			cmd_pos(char **tmp, int i);
void		exec_std(t_redirect *redirect);
char		*added_space(char *argv, int quotes);

/*
	Syntax
*/
//syntax.c
int			count_split_syntax(char *buf);
char		**ft_split_syntax(char *buf);
int			checker_syntax_utils(char **tab, char **token, int i);
int			checker_found_heredoc(char **tab, char **tok, int i, t_mini *mini);
int			checker_syntax(char *buf, t_mini *mini);
//token.c
void		print_token_error(int error, char *token);
int			checker_token(char *tab, char **token, int wich);
char		*added_space_token(char **token, char *argv);

/*
	Useful
*/
//count.c
int			len_tab(char **tabl);
int			count_str_split(char *str, char sep);
int			count_tab(char **tab);
//cut.c
char		*ft_split_one(char *str, char c);
char		*ft_cut(char *str, char c);
char		*ft_split_char(char *str, char c);
//equal.c
int			check_equal(char *buf);
int			position_equal(char *buf);
char		*until_equal(char *buf);
//error.c
void		ft_error(char *buf);

//free.c
void		ft_free_tr(char ***tab);
char		**free_tab(char **tab);
int			to_free(char *buf);
char		*str_null(char *str);
char		**ft_free_dbl(char **to_free);
//string.c
char		*ft_str_ndup(char *str);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strndup(char *src, int end);
char		*ft_strdup_free(char *src);
char		*ft_strjoin_char(char *s1, char c);

/*
	Varenv
*/
//car_var.c
int			len_car(char *str, char c);
char		*since_car(char *buf, char c);
int			find_car_spe(char c);
int			check_car_spe_doll(char *buf);
int			count_since_car(char *buf, char c);
//space_var.c
char		*since_sp(char *buf);
int			count_sep(char *str, char sep);
char		*ret_until_sp(char *untilsp);
char		*until_space(char *buf);
int			count_since_sp(char *buf);
//useful_var.c
char		*echodoll(void);
void		freestrsplitdoll(char *stresp, char *untilsp);
char		*string_var(char **tabl);
int			check_num_first(char *stresp);
int			check_doll(char *buf);
//varenv.c
char		*varia(char *buf, t_mini *mini);
//which_doll.c
char		**str_split_doll(char *str, char sep, t_mini *mini);
char		*strsplitdoll2(char *buf, char *stresp, char *untilsp, int car);
char		*strsplitdoll3(char *stresp);
char		*strsplitdoll4(char *untilsp, char *stresp, t_lst_env *lst_env);
char		*which_split_doll(int i, char *stresp, char *untilsp, t_mini *mini);

/*
	Init
*/
void		initialisation_mini(t_mini *mini);
void		init_prompt(t_mini *mini);
void		init_main(t_mini *mini, char **env);
void		init_signal(void);
void		ignore_signal(void);

/*
	Signal
*/
//signal.c
void		handle_sigint(int sig);
void		handle_sigint_here(int sig);
void		signal_exec(void);

/*
	Main.c
*/
void		free_ctrl_d(t_mini *mini, char *buf);
void		free_ctrl_d_copy(t_mini *mini, char *buf);
void		ft_prompt(t_mini *mini);
void		initialisation_mini(t_mini *mini);

#endif
