/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:23:08 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/19 11:57:04 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *memcpy(void *dest, const void *src, size_t n)
{
    unsigned char       *d;
    const unsigned char *s;
    size_t              i;

    if (!dst && !src)
        return (NULL);

    d = (unsigned char *)dst;
    s = (const unsigned char *)src;
    i = 0;
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }
    return (dst);
}