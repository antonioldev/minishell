/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:50:34 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:50:34 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <termcap.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/libft.h"

// Prompt colours
# define GREEN "\x1b[32m"
# define CYAN "\x1b[36m"
# define RED "\x1b[31m"
# define RESET "\x1b[0m"

typedef enum e_token
{
	VAR ,
	WORD = 's',
	DLESS = 174,
	DGREAT = 175,
	LESS = '<',
	GREAT = '>',
	PIPE = '|',
	SQUOTE = '\'',
	DQUOTE = '\"',
	LOGICAL_AND ,
	LOGICAL_OR,
	O_PARENTHESIS = '(',
	C_PARENTHESIS = ')'
}	t_token;

typedef enum e_cmd_structure
{
	CMD,
	ARG,
	INFILE,
	OUTFILE,
	OPERATOR,
	COMPLEX_CMD,
	MEM_VAR,
	INIT
}	t_cmd_structure;

typedef enum e_cmd_exec_status
{
	COMMAND_EXECUTED,
	COMMAND_FAILED,
	RELEASE_TO_EXEC,
	STOP_CMD
}	t_cmd_exec_status;

typedef struct s_redir
{
	int				fd;
	char			*value;
	bool			found;
	t_token			token;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_wildcard_list
{
	char					*file;
	struct s_wildcard_list	*next;
}	t_wildcard_list;

typedef struct s_wildcard
{
	bool			has_wildcard;
	char			**dirs;
	int				n_dirs;
	t_wildcard_list	*list;
}	t_wildcard;

typedef struct s_args
{
	t_token				token;
	char				**args;
}	t_args;

typedef struct s_token_list
{
	t_token				token;
	t_cmd_structure		type;
	t_wildcard			wildcard;
	char				*value;
	char				*path;
	char				**args;
	bool				to_remove;
	bool				run;
	bool				is_var;
	bool				is_last;
	int					fd_in;
	int					fd_out;
	bool				d_quote_start;
	bool				s_quote_start;
	bool				is_fake_command;
	t_redir				*infile;
	t_redir				*outfile;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}	t_token_list;

typedef struct s_var_list
{
	char				*key;
	char				*value;
	bool				to_remove;
	struct s_var_list	*next;
	struct s_var_list	*prev;
}	t_var_list;

typedef struct s_state
{
	char			cwd[1024];
	char			prompt[128];
	char			*input;
	char			**path_env;
	int				command_status;
	int				number_commands;
	int				original_stdin;
	int				original_stdout;
	int				null_fd;
	int				**pipes;
	int				prev_pipe;
	bool			run;
	bool			error;
	pid_t			*pids;
	t_token_list	*token_list;
	t_var_list		*var_list;
	t_token_list	**segments;
	int				num_segments;
}	t_state;

typedef struct s_obj
{
	struct dirent	*object;
	int				n_objects;
	DIR				*dir;
	char			*path;
	char			*new_path;
}	t_obj;

// Main
void				manage_input(t_state *state);
bool				is_empty(char *str);

// State
void				init_state(t_state *state, char **envp,
						int argc, char **argv);
void				allocate_pipe_memory(t_state **state);

// Prompt
char				*get_prompt(t_state *state);
void				set_cwd(t_state *state) __attribute__((weak));

// Signals
void				init_signal_handlers(void);
void				sigint_handler(int signum);
void				sigint_child_handler(int signum);
void				heredoc_sigquit_handler(int signum);

//Token
t_token_list		*tokenize(char *str, size_t length);
char				*find_str(char *str, size_t *i,
						t_token token) __attribute__((weak));
char				*find_dollar(char *str, size_t *i);
void				set_command_structure(t_state **state, bool found_cmd);
void				add_path_to_cmd(t_token_list *cmd, char **envp);
void				find_redirections(t_state **state);
bool				is_infile_redirection(t_token_list *current);
bool				is_outfile_redirection(t_token_list *current);
void				create_args_array(t_state **state);
void				ensure_cmd_between_pipes(t_token_list *token_list);
bool				space(int c);
void				split_list(t_token_list *head, t_token_list ***segments,
						int *num, int index);
void				check_empty_nodes(t_token_list **token);
void				print_input_after_managing(t_state *state);
char				*is_not_terminated(char *input, t_state *state);
void				check_sintax_input(t_token_list *lst, t_state *s);

//Token list manager
void				token_lstadd_back(t_token_list **lst,
						t_token_list *new) __attribute__((weak));
t_token_list		*token_lstnew(t_token token,
						char *value) __attribute__((weak));
t_token_list		*token_lstlast(t_token_list *lst) __attribute__((weak));
void				token_print_list(t_token_list *lst);

//Infile and Outfile list manager
int					file_lstsize(t_redir *lst);
void				file_lstadd_back(t_redir **lst, t_redir *new);
t_redir				*file_lstnew(t_token token, char *value, int fd);
t_redir				*file_lstlast(t_redir *lst);
void				file_print_list(t_redir *lst);

//Env vars
t_var_list			*find_env_vars(t_token_list **head_token,
						t_var_list *head_vars, char *key, char *value);
void				replace_env_vars(t_token_list **head_token,
						t_var_list *head_vars, int count, int status);
void				find_duplicate_var(t_var_list **head_env_var);
void				delete_env_var(t_var_list **list, char *key);
char				*my_getenv(t_var_list *head, char *path);
void				create_key_and_value(char *str, char **key,
						char **value, int pos_equal);

//Var list manager
int					var_lstsize(t_var_list *lst);
t_var_list			*var_lstnew(char *key, char *value);
t_var_list			*var_lstlast(t_var_list *lst);
void				var_print_list(t_var_list *lst);
void				var_lstadd_back(t_var_list **lst, t_var_list *new);

//Execute
void				close_all_pipes(t_state *s);
void				open_fd(t_token_list *command, t_state *s);
int					ft_strcmp(const char *s1, const char *s2);
void				set_cmd_run_false(t_token_list **cmd, char *value);
int					check_wildcard_files(char **file_name);
void				set_redirection(t_token_list **command,
						t_state **state, int i);
void				execute_tree(t_state *state, int i);

//Execute Helper
int					count_nodes(t_token_list *current);
int					advance_and_skip_parentheses(t_state *s, int i);
char				**concatenate_key_value(t_var_list *list, int size);

// Built in commands
t_cmd_exec_status	handle_built_in(t_state *s, t_token_list *cmd);
t_cmd_exec_status	handle_exit_cmd(t_state *s, t_token_list *cmd);
t_cmd_exec_status	handle_cd_cmd(t_state *s, t_token_list *cmd);
t_cmd_exec_status	handle_env_cmd(t_state *s, t_token_list *cmd);
t_cmd_exec_status	handle_export(t_state *s, t_token_list *cmd);
t_cmd_exec_status	handle_unset_cmd(t_state *s, t_token_list *cmd);
t_cmd_exec_status	handle_echo_cmd(t_state *s, t_token_list *cmd);
t_cmd_exec_status	handle_pwd_cmd(t_state *s, t_token_list *cmd);
void				print_all_env_vars(t_var_list *vars);
int					open_fd_solo_command(t_state *s, t_token_list *cmd);
bool				is_solo_and_built_in(t_token_list *current, int n_commands);

// Wildcard
bool				match_pattern(char *pattern, char *str);
void				handle_wildcard(t_token_list *current);
void				wildcard_lstadd_back(t_wildcard_list **lst, \
						t_wildcard_list *new);
t_wildcard_list		*wildcard_lstnew(char *file_path);
t_wildcard_list		*wildcard_lstlast(t_wildcard_list *lst);
void				wildcard_print_list(t_wildcard_list *lst);
char				*build_path(char *path, char *name);
int					build_wildcard_list(t_token_list *current, \
						int i, int len, char *path);
void				free_wildcard(t_token_list *current);
void				free_wildcard_dirs(char **dirs);

//Error
void				ft_fork_error(void);
void				ft_malloc_error(void);
void				redirection_error(t_token_list *current);
int					error_exceve(char *str, t_state *s);
void				file_wildcard_error(char *file_name);
void				free_matches(char **matches);

//Clean
void				token_remove_unwanted_nodes(t_token_list **head);
void				var_remove_unwanted_nodes(t_var_list **head);
void				remove_pipes_and_args(t_token_list **head);
void				free_args_array(t_token_list *current);
void				free_allocation_malloc(t_token_list **lst, char *str, \
						t_token_list ***segments);
void				free_allocation_malloc_path_env(char **path_env,
						t_state *s);
void				free_allocation_malloc_pipes(t_state *state);

void				free_allocation_malloc_vars(t_var_list *env_var);
void				free_redirection(t_redir **infile, t_redir **outfile);
void				free_all_memory(t_state *s);
void				free_temporary_vars(char **key, char **value);

#endif