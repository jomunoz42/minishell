/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:21:18 by jomunoz           #+#    #+#             */
/*   Updated: 2025/11/21 18:36:54 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_shell_lvl(t_map *map)
{
	char	*lvl;

	lvl = map->get(map, "SHLVL");
	if (!lvl)
		return ;
	if (!ft_strncmp(lvl, "999", 4))
	{
		write(2, "bash: warning: shell level (1000) too high, resetting to 1\n",
			60);
		lvl = ft_itoa(1);
	}
	else
		lvl = ft_itoa(ft_atoi(lvl) + 1);
	map->put(map, ft_strdup("SHLVL"), lvl);
}

static void	handle_no_env(t_map *map)
{
	map->put(map, ft_strdup("SHLVL"), ft_strdup("2"));
	map->put(map, ft_strdup("PWD"), ft_strdup(getcwd(NULL, 0)));
}

void	copy_env(t_map *map, char **env, t_exec *exec, t_cmd *cmd)
{
	static char	*args[2];
	int			j;
	int			i;
	int			pid;

	i = -1;
	get_map_addr(map);
	get_exec_addr(exec);
	if (env && *env)
	{
		while (env[++i])
		{
			j = length_of_equal(env[i]);
			args[0] = ft_substr(env[i], 0, j++);
			args[1] = ft_substr(env[i], j, (ft_strlen(env[i]) - j));
			map->put(map, args[0], args[1]);
		}
	}
	else
		handle_no_env(map);
	handle_shell_lvl(map);
	map->put(map, ft_strdup("?"), ft_strdup("0"));
	pid = get_pid(exec, cmd);
	map->put(map, ft_strdup("$"), ft_itoa(pid));
}

int	ft_env(t_cmd *cmd, t_map *env, t_exec *exec)
{
	char	**vars;
	int		i;

	i = -1;
	if (cmd->args[1])
	{
		write(2, "Minishell subject: env with no options or arguments.\n", 53);
		return (1);
	}
	vars = env->to_str(env);
	while (vars && vars[++i] && is_there_value(vars[i]))
	{
		if (!ft_strncmp(vars[i], "?", 1) || !ft_strncmp(vars[i], "$", 1))
			continue ;
		write(exec->out, vars[i], ft_strlen(vars[i]));
		write(exec->out, "\n", 1);
	}
	return (0);
}
