/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_comment.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:51:57 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/17 16:52:58 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void add_token(t_token **tokens, const char *value)
{
    t_token *new_token; // Ponteiro para um novo token.
    t_token *current;    // Ponteiro auxiliar para percorrer a lista de tokens.

    // Aloca memória para um novo token.
    new_token = malloc(sizeof(t_token));
    if (!new_token)  // Se não conseguir alocar, sai da função.
        return ;

    // Cria uma cópia da string de valor do token.
    new_token->value = ft_strdup(value);
    if (!new_token->value)  // Se falhar ao alocar a string, libera a memória do token e sai da função.
    {
        free(new_token);
        return ;
    }
    
    new_token->next = NULL;  // Define o próximo token como NULL (final da lista).

    // Se não houver tokens na lista, o novo token é o primeiro.
    if (*tokens == NULL)
        *tokens = new_token;
    else
    {
        current = *tokens;
        // Percorre a lista até o final para adicionar o novo token.
        while (current->next)
            current = current->next;
        current->next = new_token; // Adiciona o novo token no final da lista.
    }
}

int is_whitespace(char c)
{
    // Retorna 1 se o caractere for um espaço em branco (espaço, tabulação, nova linha, etc.), 0 caso contrário.
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
        || c == '\f' || c == '\r');
}

char *copy_substr(const char *input, int start, int length)
{
    char *substr;

    // Se o comprimento for negativo, retorna NULL.
    if (length < 0)
        return (NULL);

    // Aloca memória para a substring.
    substr = malloc(length + 1);
    if (!substr)  // Se falhar na alocação, retorna NULL.
        return (NULL);

    // Copia a substring para a nova alocação de memória.
    ft_strncpy(substr, input + start, length);
    substr[length] = '\0';  // Garante que a substring terminada em '\0' seja válida.

    return (substr); // Retorna a substring copiada.
}

int handle_quotes(const char *input, int *i, t_token **tokens)
{
    char quote;
    int start;

    quote = input[*i]; // Armazena o tipo de aspa encontrada (simples ou dupla).
    start = ++(*i);    // Atualiza a posição do índice após encontrar a aspa.

    // Percorre os caracteres até encontrar a aspa correspondente.
    while (input[*i] && input[*i] != quote)
        (*i)++;
    
    // Se encontrar a aspa correspondente, cria o token.
    if (input[*i] == quote)
    {
        add_token(tokens, copy_substr(input, start, *i - start));
        (*i)++;  // Avança o índice após a aspa final.
        return (1);  // Retorna 1 indicando sucesso.
    }
    else
    {
        ft_putstr_fd("Error: Unmatched quotes\n", 2); // Se não encontrar a aspa final, exibe erro.
        return (0);  // Retorna 0 indicando erro.
    }
}

void hand_spc_chars(const char *input, int *i, int *start, t_token **tokens)
{
    // Se houver caracteres antes do operador especial, cria um token para a palavra anterior.
    if (*i > *start)
        add_token(tokens, copy_substr(input, *start, *i - *start));

    // Cria um token com o operador especial (como '|', '>', '<').
    add_token(tokens, copy_substr(input, *i, 1));
    (*i)++;  // Avança o índice para o próximo caractere.
    *start = *i; // Atualiza o ponto de início para o próximo token.
}
