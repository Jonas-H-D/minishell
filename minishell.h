#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"
#include <stdlib.h>

// int	g_exit_status = 0;

//Error
void	err_msg(char *e, char *avant_e, int exit_status);

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

//Token

typedef struct s_token t_token;
struct s_token
{
	char		*info;//cmd
	char		**tab_cmd;
	int			type;
	int			tk_index;
	int			cmd_index;
	t_token	*next;
};
// 0 == stdrin
// 1 == cmd
// 2 == stdrout
// 3 == heredoc
// 4 == a definir

// token_index
// {
// 	int	index;
	
// }

//struct pour garder des info pour remplacer le quotes
typedef struct s_str t_str;

struct s_str
{
	int		start;
	int		len;
};

// lexer
int		ft_c_vs_charset(char c, const char *cs);
int		ft_strchr_set(const char *s, char *set);
int		ft_strchr_char(const char *s, char c);
int		search_next_c(char **s, int *debut, char c);


void	loop_prompt(int ac, char **av, char **envp);
int		lexer(char *input, t_env *liste, t_token *tk);
void	trimer (char *s, int *i);
void	search_quotes_closed(char *str);
char	detect_quotes(char *s, int *i);
char	*chercher_env(t_env *liste, char *a_trouver);
char	*ajouter_au_string(char **s, int *i, int enlever, char *ajouter);
char	*remplacer_dollar(char **s, int *index, t_env *liste); 
char	*chercher_and_replace_dollar(char **s, int *i, t_env *liste);
char	*search_and_replace_quotes(char **input, t_env *liste);
char	*remplacer_rest_of_dollar(char **s, t_env *liste);


//ENV
void	my_env(char **envp);
void	current_dir(void);
void	create_node(t_env **head, char *data);
void	printlist(t_env *node);
void	create_env_list(t_env **head, char **envp);
t_env	*ft_search_in_list(t_env **head, char *name);
t_env	*ft_create_node(char *name, char *value);
void	ft_add_to_list(t_env **head, t_env *newnode);
int		ft_delete_first_node(t_env **head, t_env *temp, char *name);
void	ft_delete_from_list(t_env **head, char *name);
int		ft_count_list(t_env **head);

char	*ft_get_line(char *line);
char	*ft_get_name(char *line);

#endif