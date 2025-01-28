/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_comment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:49:34 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/23 18:03:59 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_word(const char *input, int *i, int *start, t_token **tokens)
{
    // Começa um loop que vai até encontrar um caractere de espaço em branco, um operador especial (|, <, >), ou aspas.
    while (input[*i] && !is_whitespace(input[*i])
        && !ft_strchr("|<>", input[*i])
        && input[*i] != '\'' && input[*i] != '\"')
        (*i)++;  // Aumenta o índice para percorrer os caracteres até encontrar o final da palavra ou um operador especial.
    
    // Se o índice atual for maior que o valor inicial (significa que há uma palavra a ser tokenizada).
    if (*i > *start)
    {
        // Adiciona a palavra (token) extraída ao lista de tokens.
        add_token(tokens, copy_substr(input, *start, *i - *start));
        
        // Atualiza a posição de início para o índice atual.
        *start = *i;
    }
}

t_token *tokenize(const char *input)
{
    t_token *tokens; // Ponteiro para a lista de tokens.
    int i;           // Índice que percorre a string de entrada.
    int start;       // Posição inicial de cada token encontrado.

    i = 0;          // Inicializa o índice.
    start = 0;      // Inicializa o início da palavra.
    tokens = NULL;  // Inicializa a lista de tokens como vazia.

    // Loop principal que percorre cada caractere do input.
    while (input[i])
    {
        // Se o caractere for um espaço em branco (ou outros caracteres de espaço como tabulação ou quebra de linha).
        if (is_whitespace(input[i]))
        {
            // Se o intervalo de caracteres desde o último token for maior que 0, adiciona o token encontrado.
            if (i > start)
                add_token(&tokens, copy_substr(input, start, i - start));
            start = ++i; // Atualiza a posição inicial para o próximo caractere após o espaço.
        }
        // Se o caractere for uma aspa simples ou dupla (indicando uma string).
        else if (input[i] == '\'' || input[i] == '\"')
        {
            // Chama a função handle_quotes para lidar com a expansão de tokens dentro das aspas.
            if (!handle_quotes(input, &i, &tokens))
            {
                ft_putstr_fd("Error: Unmatched quotes\n", 2); // Em caso de erro, imprime uma mensagem.
                break; // Interrompe o loop em caso de erro.
            }
            start = i; // Atualiza a posição inicial para a posição atual de i.
        }
        // Se o caractere for um dos caracteres especiais (como |, <, >).
        else if (ft_strchr("|<>", input[i]))
            hand_spc_chars(input, &i, &start, &tokens); // Lida com esses caracteres especiais.
        else
            handle_word(input, &i, &start, &tokens); // Chama a função handle_word para tratar palavras normais.
    }

    // Se houver algum token não adicionado após o loop.
    if (i > start)
        add_token(&tokens, copy_substr(input, start, i - start)); // Adiciona o último token.
    
    return (tokens); // Retorna a lista de tokens gerada.
}
