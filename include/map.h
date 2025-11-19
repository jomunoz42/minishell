/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:32:49 by pbongiov          #+#    #+#             */
/*   Updated: 2025/11/19 19:50:37 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdbool.h>
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
}							t_node;

struct						s_map
{
	void					(*put)(t_map *this, char *key, char *value);
	void					(*remove)(t_map *this, char *key);
	char					*(*get)(t_map *this, char *key);
	char					**(*to_str)(t_map *this);
	void					(*destroy)(t_map *this);
	int						size;
	t_node					*head;
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
	char					**str;
	int						is_change;
};

t_map						*new_map(void);

#endif