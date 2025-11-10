

#include "minishell.h"

static void handle_shell_lvl(t_map *map)
{
	char		*lvl;

	lvl = map->get(map, "SHLVL");
	if (!ft_strncmp(lvl, "999", 4))
	{
		write(2, "bash: warning: shell level (1000) too high, resetting to 1\n", 60);
		lvl = ft_itoa(1);
	}
	else
		lvl = ft_itoa(ft_atoi(lvl) + 1);
	map->put(map, "SHLVL", lvl);
}

static void	handle_no_env(t_map *map)
{
	map->put(map, ft_strdup("SHLVL"), ft_strdup("3"));
	map->put(map, ft_strdup("PWD"), ft_strdup(getcwd(NULL, 0)));
	map->put(map, ft_strdup("PATH"),
		ft_strdup("/home/jomunoz/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"));
}

void	copy_env(t_map *map, char **env, t_exec *exec)
{
    static char	*args[2];
	int			j;
	int			i;

	i = -1;
	if (env && env[0])
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
	map->put(map, ft_strdup("$"), ft_strdup("substituir")); ////////
}

int	ft_env(t_cmd *cmd, t_map *env, t_exec *exec)
{
	char	**vars;
	int		i;

	i = -1;
	if (cmd->args[1])
	{
		write(1, "Minishell subject: env with no options or arguments.\n", 54);
		return (0);
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
