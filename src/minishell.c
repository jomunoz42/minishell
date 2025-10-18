#include "minishell.h"

void print_struct(t_cmd *head);

static void    is_built_in(t_cmd *cmd, t_map *env)
{
    if (!cmd || !cmd->args)
        return;
    if (!ft_strncmp(cmd->args[0], "exit", 5))
        ft_exit(0);
    else if (!ft_strncmp(cmd->args[0], "echo", 5))
        ft_echo(cmd);
    else if (!ft_strncmp(cmd->args[0], "pwd", 4))
        ft_pwd();
    else if (!ft_strncmp(cmd->args[0], "env", 4))
        ft_env(env);
    else if (!ft_strncmp(cmd->args[0], "export", 7))
        ft_export(cmd, env);
    else if (!ft_strncmp(cmd->args[0], "unset", 6))
        ft_unset(cmd, env);
}

void free_list(t_cmd *all)
{
    t_cmd *current;
    t_cmd *next;
    t_redir *next_redir;

    if (!all)
        return;
    current = all;
    while (current)
    {
        next = current->next;
        if (current->args)
            free_double(current->args);
        while (current->redir)
        {
            next_redir = current->redir->next;
            if (current->redir->args)
            {
                free(current->redir->args[0]);
                free(current->redir->args[1]);
            }
            if (current->redir)
                free(current->redir);
            current->redir = next_redir;
        }
        free(current);
        current = next;
    }
}

int main(int argc, char **argv, char **environ)
{
    char *input;
    t_cmd *cmd;
    t_map *env;

    env = new_map();
    //copy_env(env, environ);
    while (1)
    {
        input = readline("<minishell>: ");
        if (*input)
        add_history(input);
        cmd = NULL;
        cmd = parsing(input, cmd);
        if (!cmd)
        {
            free_list(cmd);
            break;
        }
        print_struct(cmd);
        is_built_in(cmd, env);
        free_list(cmd);
    }
    rl_clear_history();
    env->destroy(env);
}

