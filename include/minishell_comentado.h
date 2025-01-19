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


