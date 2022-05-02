#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>
# include <termios.h>
# include <sys/types.h> 
# include <sys/stat.h>
# include <errno.h>

/* terminal colors */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define DEFAULT "\033[0m"

# define MSG_IS_DIRECTORY "is a directory"
# define MSG_FILE_NOT_FOUND "not such file or directory"
# define MSG_COMMAND_NOT_FOUND "command not found"
# define MSG_PERMISSION_DENIED "permission denied"

//Token
# define IN_FILE 0
# define OUT_FILE 1
# define APPEND 2
# define HEREDOC 3
# define BUILT_IN 4
# define CMD 5
# define PIPE 6

pid_t	g_pid[255];

// chained list to extract env
typedef struct s_env t_env;

struct s_env
{
	char	*initial_env;
	char	*name;
	char	*content;
	t_env	*next;
};

// chained list to order export list
typedef struct s_order
{
	t_env	*newNode;
	t_env	*temp1;
	t_env	*temp2;
}	t_order;

// chained list with minishell input
typedef struct s_token t_token;

struct s_token
{
	char		*content;//cmd, infile, outfile, etc
	int			type;
	int			cmd_index;//nro de commande
	int			in_index;//nro de redir_in
	int			out_index;//nro de redir_out
	int			export_vars;
	char		*export;
	char		*export_name;// var name
	char		*export_content; // var content
	t_token	*next;
// 	char		**tab_cmd;// remplace par t_info->split_cmd
};

typedef struct s_info
{
	t_token	*tk;
	t_env	*liste;
	// char	*input;
	char	**envp;
	char	**full_cmd;
	char	***split_cmd;
	char	*redir_in; 
	char	*redir_out;
	int		q_in; //q == quantite de redirection in
	int		q_out; //q == quantite de redirection out
	int		cmd_i;	//nro de commande
	int		q_cmd;
	int		pipe_i;
	int		**pipes;
	int		*pids;
	int		exit_status;
}	t_info;

//Error
void	err_msg(char *e, char *avant_e, int exit_status);
void	xperror(char *str);
void	print_join(char *s1, char *s2, int fd);
int		show_command_error(t_info *info, char *cmd, char *msg, int exit_status);

// redirection
void	redirect_in_out(t_info *info, int i);
int		find_last_in(t_token *tk, int i);
int		find_last_out(t_token *tk, int i);
int		get_q_in(t_token *tk, int i);
int		get_q_out(t_token *tk, int i);
// void	restart_in_out(t_info *info);

// heredoc
int		create_heredocs(t_token *tk);
void	get_heredoc(char *flag, int i);
int		get_heredoc_fd(int cmd_index);
int		destroy_heredocs(int q_cmd);
char	*ft_strjoin_whit_int(char *s1, int n);

// pipe
int		create_pipes(t_info *info);
void	close_pipes(t_info *shell);
void	free_pipes(int **pipes, int q);

//pid
void	create_pids(t_info *shell);
void	wait_pids(t_info *shell);
void	wait_pids_heredoc(t_info *info, int i);

// EXEC
char	*ft_strjoin_whit_space(char *s1, char const *s2);
int		is_builtin(char *cmd);
int		exec_builtin(char **tab_cmd, t_info *liste);
char	*ft_get_last_arg(char *src);
int		slash_case(char *cmd, t_info *info);
int		find_path(char *cmd, char **envp, t_env *liste);
void	execution_main(t_info *info);
int		exec_single_cmd(t_info *info);

// access
int		access_ok(char *cmd, t_info *info, char **path);
int		is_invalid_command(t_info *info, char *cmd);

// free
void	free_tab(char **tab);
void	free_tokens(t_token **tk);
void	free_all(t_info *info);
void	free_info_simple(t_info *info);
char	*ft_strjoin_free(char *s1, char const *s2);
void	print_tab(char **tab);
void	print_tab_tab(char ***tab);


// parser
t_info	*parser(t_env *liste, t_token *tk, char **envp, t_info *info);
t_info	*init_info(t_info *info, int last_exit);

// lexer
int		ft_c_vs_charset(char c, const char *cs);
int		ft_strchr_set(const char *s, char *set);
int		ft_strchr_char(const char *s, char c);
int		search_next_c(char **s, int *debut, char c);
int		ft_charset_found(const char *s, int* start, char *set);
void	loop_prompt(t_env *liste, char **envp);
int		lexer(char *input, t_env *liste, t_token **tk, t_info *info);
void	trimer (char *s, int *i);

// QUOTES
// char	*chercher_and_replace_dollar(char **s, int *i, t_env *liste);
// char	*search_and_replace_quotes(char **input, t_env *liste);
// char	*remplacer_dollar(char **s, int *index, t_env *liste); 
// char	*remplacer_rest_of_dollar(char **s, t_env *liste);
void	search_quotes_closed(char *str);
char	detect_and_check_quotes(char *s, int *i);
char	*search_and_replace_quotes(char **input, t_env *liste, t_info *info);
char	*chercher_env(t_env *liste, char *a_trouver);

char	*remplacer_dollar(char **s, int *index, t_env *liste, t_info *info); 
char	*ajouter_au_string(char **s, int *i, int enlever, char *ajouter);
char	*chercher_and_replace_dollar(char **s, int *i, t_env *liste, t_info *info);
char	*remplacer_rest_of_dollar(char **s, t_env *liste, t_info *info);

//TOKENS
void	explore_tokens_err(char **in);
void	search_next_token(char *s, int *start, int *tk_idx, int *type);
t_token	*get_tokens(char *s, t_token *tk);
void	printlist_tk(t_token *node);
char	**ft_split_from_charset(char *s, char *set);
void	tk_create_second(t_token **head, char **data, int type);
void    tk_create_node(t_token **head, char **data, int type);
int		set_type(char *s, int i, char c);
char	*erase_quotes(char *s);
void	erase_quotes_tk(t_token *node);

//ENV
void	create_node(t_env **head, char *data);
void	printlist(t_env *node);
void	create_env_list(t_env **head, char **envp);
t_env	*ft_sort_list(t_env *head);
t_env	*ft_search_in_list(t_env **head, char *name);
t_env	*ft_create_node(char *name, char *value);
void	ft_add_to_list(t_env **head, t_env *newnode);
int		ft_delete_first_node(t_env **head, t_env *temp, char *name);
void	ft_delete_from_list(t_env **head, char *name);
int		ft_count_list(t_env **head);
void  err_exit(char *e, char *avant_e, int exit_status);
char	*ft_get_line(char *line);
char	*ft_get_name(char *line);
void	ft_env_set_content(t_env *env, char *name, char *new_content);
void	free_env(t_env **env);
void	ft_free_list(t_env **head_a);

// BUILT_IN

int		ft_builtin(t_token *token, t_env *liste);
void	ft_exit(char **tab_cmd);
void	ft_cd(char **argv, t_env *env);
int		current_dir(void);
int		my_env(t_env *envp);
int		ft_echo(char **argv);
int		ft_equal(char *var);
int		ft_check_export_var(char *var);
t_env	*ft_export(char **argv, t_env *liste, t_info *info);
void	ft_add_to_list2(t_env **head, t_env *newnode);
void	ft_unset(t_env **env, char *argv);

// SIGNALS

void	signal_h(int signal);
void	ft_stop(char *input);
void	ft_stop2(char *input);
void	signal_q(int sig);
void	ft_get_pid(int i);
void	signal_here(int signal);
void	signal_2(int signal);

#endif