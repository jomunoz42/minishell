/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:53:51 by jomunoz           #+#    #+#             */
/*   Updated: 2025/10/10 23:28:03 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void swap_var(t_node *a, t_node *b)
{
    char *key;
    char *value;

    key = a->key;
    value = a->value;
    a->key = b->key;
    a->value = b->value;
    b->key = key;
    b->value = value;
}

t_node *sort_node(t_map_extra *this)
{
    t_node  *a;
    t_node  *b;
    int     swapped;

    if (!this->sort)
        return (this->head);

    swapped = 1;
    while (swapped)
    {
        swapped = 0;
        a = this->head;
        while (a && a->next)
        {
            b = a->next;
            if (this->sort(a, b) > 0)
            {
                swap_var(a, b);
                swapped = 1;
            }
            a = a->next;
        }
    }
    return (this->head);
}
