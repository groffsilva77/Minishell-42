#ifndef MINISHELL_H
	# define MINISHELL_H

//first struct (gestão de memoria)
/* s_memory: esta estrutra é uma lista encadeada usada para rastrear as alocações
de memória feitas pelo minishell

Função principal: Facilitar a liberação de memória gerenciada, garantindo que nenhum bloco de memória fique "perdido" (leak)

ptr_for_memory_block = ponteiro para o bloco de memória que foi alocado
next_ptr = proximo ponteiro para outro bloco de memória (que também foi alocado)
*/
------------------------------------------------------------------------------------------------------------------------------

//segund struct (gerenciar informaçoes do estado)
/*s_shell = usada para armazenar e gerenciar informações essenciais que controlam o estado global do shell
*memory = re chama a função s_memory
**envp_copy = cópia do ambiente do sistema  -> Copiar o ambiente permite que o shell faça alterações (como adicionar, remover ou modificar variáveis) sem afetar o ambiente original.
ext_status = status do último comando/Mantém o código de saída do útimo comando -> Necessário para implementar o comportamento padrão do shell com $?
*/

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

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

//functions we will use to memory
void	*ft_malloc(t_shell *shell, size_t size); //pegar o brinquedo (ptr) e guardar em um local especial (struct)
void	ft_free(t_shell *shell, void *ptr); //devolver o brinquedo (ptr) tira da struct
void	ft_free_all(t_shell *shell); 



//the *ft_malloc
void *ft_malloc(t_shell *shell, size_t size)
{
	t_memory *new; //aonde será salvo o ptr
	void	 *ptr; //pontero que será/foi alocado

ptr = malloc(size) //aloca memoria para o ptr
if (!ptr) //verificação de erro
	return (NULL);
new= malloc(sizeof(t_memory))
if (!new)
{
	free(ptr);
	return (NULL);
}
new->ptr_for_memory_block = ptr;
new->next_ptr = shell->memory; // guarda o new (que contem o ptr) na struct
shell->memory = new;
return (ptr);
}
/*resumão de ft_malloc

aqui nos estamos mexendo com lista linkada
como funciona: o ft_malloc, basicamente, será utiizado para ordernar os todos os ponteiros
para que todos eles fiquem salvos na struct memory e depois seram apagados um por um

a teoria funciona assim: ptr está apontando para um bloco de memoria, precisamos salvar ele
em uma struct (a memory no caso) mas para isso precisamos "salvar" em new.

tipo : É como quando você ganha um brinquedo novo (ptr)
	Anota num papel onde guardou ele (new)
	Coloca esse papel numa pasta especial (struct memory)
	Assim você sempre sabe onde estão todos seus brinquedos!*/

----------------------------------------------------------------------------------------------------------
//the ft_free
void ft_free(t_shell *shell, void *ptr)
{
	t_memory	*atl; //ponteiro atual
	t_memory	*ant; //ponteiro anterior

	if (!ptr) //verifica se tem ponteiro para ser retirado, se não tiver, só retorna;
		return;
	ant = NULL;  //aqui declaramos que não temos um ponteiro anterior (por enquanto)
	atl = shell->memory; //aqui estamos apontando para o new (que possui o ptr) já que ele é o primeiro elemento da struct
	while (atl) // enquanto o new existir, procuramos o ponteiro dentro dele
		if (atl->ptr == ptr) //achamos o ptr
	if (ant) //se tiver algo no anterior
		ant->next = atl->next; //se tiver ele vira o proximo
	else //se não tiver
		shell->memory = atl->next //o proximo nó, elemento da lista será chamado
	free(ptr); //libera o ponteiro
	free(atl); //libera aonde está guardado esse ponteiro
	return;
}

/*olha o resumo

Você recebe um brinquedo para devolver
Começa a procurar na sua lista de papéis
Quando acha o papel com esse brinquedo:

Arruma a lista (liga os papéis vizinhos)
Devolve o brinquedo
Joga fora o papel

Se não achar, continua procurando até o fim da lista*/