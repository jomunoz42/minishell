/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:32:49 by pbongiov          #+#    #+#             */
/*   Updated: 2025/10/04 17:47:00 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_map		t_map;
typedef struct s_node		t_node;
typedef struct s_map_extra	t_map_extra;

typedef struct s_node
{
	char					*key;
	char					*value;
	struct s_node			*next;
	int						fd;
}							t_node;

struct						s_map
{
	void					(*put)(t_map *this, char *key, char *value);
	void					(*remove)(t_map *this, char *key);
	char					*(*get)(t_map *this, char *key);
	char					**(*to_str)(t_map *this);
	void					(*destroy)(t_map *this);
};

struct						s_map_extra
{
	void					(*put)(t_map_extra *this, char *key, char *value);
	void					(*remove)(t_map_extra *this, char *key);
	char					*(*get)(t_map_extra *this, char *key);
	char					**(*to_str)(t_map_extra *this);
	void					(*destroy)(t_map_extra *this);
	int						size;
	t_node					*head;
	t_node					*tail;
};

t_map						*new_map(void);
#endif