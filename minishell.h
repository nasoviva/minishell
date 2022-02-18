/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hverda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:24:23 by hverda            #+#    #+#             */
/*   Updated: 2021/12/15 15:24:27 by hverda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <termios.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

int						g_error;
typedef struct s_list	t_list;

struct	s_list
{
	char	*key;
	char	*value;
	int		flag;
	t_list	*next;
};

typedef struct s_exe
{
	char			*comnd;
	char			**cmd_arg;
	char			*cmdi_path;
	char			*infile;
	char			*outfile;
	char			*append;
	char			*limiter;
	int				fd1;
	int				fd2;
	struct s_exe	*next;

}					t_exe;

typedef struct s_cmd
{
	int				oldpwd;
	char			*path;
	char			**mypathes;
	int				i;
	t_list			*env_list;
	t_list			*export_list;
	t_exe			*exe;
	char			**argv;
	int				argc;
	int				quote;
	int				quote_2;
	int				pipe;
	int				len;
	int				ok;
	int				k;
	int				f;
	int				out;
	int				std_in;
	int				std_out;
	int				*proc;
	int				pid;
	char			**envp;
}					t_cmd;

void	ft_putstr(char *str);
void	ft_copy_from_list(t_list *env_list, t_cmd *cmd);
char	*ft_path(char *comd, char **mypathes, t_cmd *cmd);
void	ft_free(t_cmd *cmd);
void	ft_free_cmd(char **argv);
void	ft_free_char(char *argv);
void	ft_mistake(char *message, t_cmd *cmd);
int		ft_str_cmp(char *s1, char *s2);
void	ft_get_next_line(char *file_name, char *limiter, t_cmd *cmd);
void	ft_execv_i(t_cmd *cmd);
void	ft_cycle_pipes(t_cmd *cmd);
void	ft_multiple_pipe(t_cmd *cmd);
void	ft_here_doc(t_cmd *cmd);
void	ft_init(t_cmd *cmd, char **envp);
void	ft_init_cmd(t_cmd *cmd);
void	handler(int sig);
void	handler1(int sig);
void	handler4(int sig);
void	handler11(int sig);
void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);
int		ft_strlen(char *str);
char	*ft_strdup(char *s1, t_cmd *cmd);
t_list	*ft_init_node(t_list *list, char *comd, t_cmd *cmd);
t_list	*ft_add_node_back(t_list *list, char *comd, t_cmd *cmd);
int		ft_env_path_check(t_cmd *cmd);
void	ft_env(t_cmd *cmd);
void	ft_echo(t_cmd *cmd);
void	ft_pwd(t_cmd *cmd);
char	**ft_split(char *s, char c, t_cmd *cmd);
void	ft_unset(t_cmd *cmd);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
void	ft_export(t_cmd *cmd);
int		ft_char_inside_str(char *str, char c);
int		ft_isalpha(int c);
void	ft_cd(t_cmd *cmd);
char	*ft_strjoin(char *s1, char *s2, t_cmd *cmd);
void	ft_del_from_list(char **argv, t_list **list);
int		ft_change_value(char *comd, t_list *list, t_cmd *cmd);
void	ft_new_value(t_list *list, char *key, char *value, t_cmd *cmd);
char	*ft_get_some_dir(t_cmd *cmd, char *key);
void	ft_free_list(t_list *list);
void	ft_exit(t_cmd *cmd);
void	ft_bash_layer(t_cmd *cmd);
int		ft_atoi(char *str);
char	*ft_itoa(int n, t_cmd *cmd);
t_list	*ft_env_list_creation(char **envp, t_cmd *cmd);
t_list	*ft_export_list_creation(char **envp, t_cmd *cmd);
char	*ft_substr(char *s, unsigned int start, size_t len, t_cmd *cmd);
char	*ft_prepars_dollar2(char *str, t_cmd *cmd, int *j);
char	*ft_after(char *str, t_cmd *cmd);
char	*ft_check_value(char *tmp2, t_cmd *cmd, int *j);
void	ft_if_dollar_null(char *tmp2, t_cmd *cmd);
char	*ft_dollar2(char *str, t_cmd *cmd, int *j);
int		ft_ifkey(char c);
void	ft_dollar_2_result(char *tmp, char *tmp2, char *tmp3, t_cmd *cmd);
char	*ft_dollar_2_result1(char *tmp, char *tmp3, char *tmp4, t_cmd *cmd);
char	*ft_dollar_2_result2(char *tmp, char *tmp2, char *tmp4, t_cmd *cmd);
char	*ft_dollar_2_result3(char *tmp, char *tmp4, t_cmd *cmd);
char	*ft_check_for_dollar(char *str, t_cmd *cmd);
char	*ft_copykey(char *tmp2, t_cmd *cmd, t_list	*copy);
char	*ft_if_dollar_question(char *tmp2, t_cmd *cmd);
char	*ft_if_dollar_question2(char *tmp2, t_cmd *cmd);
char	*ft_join(char *tmp, char *tmp3, t_cmd *cmd);
char	*ft_dollar_result(char *tmp, char *tmp2, char *tmp3, t_cmd *cmd);
char	*ft_onlydollar(char *str, char *tmp, char *tmp2, t_cmd *cmd);
char	*ft_prepare(char *str, t_cmd *cmd);
char	*ft_dollar(char *str, t_list *env_list, t_cmd *cmd);
char	*ft_if_dollar(char *str, char *tmp, t_cmd *cmd, int g);
char	*ft_if_quote(char *str, t_cmd *cmd, int *j);
char	*ft_if_quote2(char *str, t_cmd *cmd, int *j);
char	*ft_delete_quote(char *str, char *tmp, t_cmd *cmd, int *j);
char	*ft_return_str_pipe(char *str, char *tmp, t_cmd *cmd, int *j);
char	*ft_pass_quote(char *str, char *tmp, t_cmd *cmd, int *j);
char	*ft_put(char *tmp, t_cmd *cmd);
char	*ft_put_in_command(char *tmp, t_cmd *cmd);
char	*ft_pars_remaind(char *str, char *tmp, t_cmd *cmd, int *j);
int		ft_check_remaind(char *str, t_cmd *cmd);
char	*ft_delete_quote(char *str, char *tmp, t_cmd *cmd, int *j);
char	*ft_return_str_pipe(char *str, char *tmp, t_cmd *cmd, int *j);
void	ft_result_str(char *err, t_cmd *cmd);
char	*ft_return_str_in(char *str, char *tmp, t_cmd *cmd, int *j);
char	*ft_return_str_in2(char *str, char *tmp, t_cmd *cmd, int *j);
char	*ft_return_str_out(char *str, char *tmp, t_cmd *cmd, int *j);
char	*ft_return_str_out2(char *str, char *tmp, t_cmd *cmd, int *j);
int		ft_len(char *str);
void	ft_if_layer_2(t_cmd *cmd);
void	ft_no_input(t_cmd *cmd, char *input);
char	*ft_prepars(char *str, t_cmd *cmd, int *j);
void	ft_pars(char *str, t_cmd *cmd, int *j);
void	ft_check_pars(t_cmd *cmd);
void	ft_final_pars(t_cmd *cmd);
void	ft_cmd_create(t_cmd *cmd, char *str);
char	*ft_outfile(char *str, t_cmd *cmd, int *j);
char	*ft_infile(char *str, t_cmd *cmd, int *j);
char	*ft_error_pipe_redir(char *str, t_cmd *cmd, char *error);
char	*ft_pipe(char *str, t_cmd *cmd, int *j);
int		ft_isdigit(char *str);
void	ft_init_node_exe(t_cmd *cmd);
void	ft_add_node_back_exe(t_cmd *cmd);
void	ft_if_infile(t_cmd *cmd);
void	ft_if_outfile(t_cmd *cmd);
void	ft_if_append(t_cmd *cmd);
void	ft_minishell(t_cmd *cmd, char *input);
int		main(int argc, char **argv, char **envp);
void	ft_free_list_exe(t_exe *exe);
int		ft_check_key(t_list *env_list, char *key, char *err, char *object);
void	ft_error(char *begin, char *object, char *err, int i);
void	handler3(int sig);
char	*ft_getcwd(t_cmd *cmd);
void	ft_standard_exit(t_cmd *cmd);
void	ft_update_oldpwd(t_cmd *cmd);
void	ft_up(t_cmd *cmd);
void	ft_free_node_data(t_cmd *cmd);

#endif
