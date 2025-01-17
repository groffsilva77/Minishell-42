#ifndef MINISHELL_H
	# define MINISHELL_H

//library
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

//struct
typedef struct s_memory
{
	void				*ptr_for_memory_block;
	struct s_memory		*next_ptr;
}t_memory;

typedef struct s_shell
{
	t_memory	*memory;
	char		**env_copy;
	int			exit_status;
}t_shell;


//functions we will use to memory (prototype)
void	*ft_malloc(t_shell *shell, size_t size);






//functinos we will use to memory(mounted)

void *ft_malloc(t_shell *shell, size_t size)
{
	t_memory *new;
	void	 *ptr;

ptr = malloc(size)
if (!ptr)
	return (NULL);
new= malloc(sizeof(t_memory))
if (!new)
{
	free(ptr);
	return (NULL);
}
new->ptr_for_memory_block = ptr;
new->next_ptr = shell->memory;
shell->memory = new;
return (ptr);
}