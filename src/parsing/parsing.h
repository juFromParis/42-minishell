#ifndef PARSING_H
# define PARSING_H
#include <unistd.h>

typedef struct s_token	t_token;
typedef struct s_node	t_node;
t_node					*parse(t_token *token);
char	**insert_arg(char **old_list, size_t wild_index, char **new_args);
#endif