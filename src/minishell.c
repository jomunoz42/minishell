#include "minishell.h"

void print_struct(t_cmd *head);

static void    is_built_in(t_cmd *cmd, t_map *env, t_exec *exec)
{
    if (!cmd || !cmd->args)
        return;       
    if (!ft_strncmp(cmd->args[0], "cd", 3))
        ft_cd(cmd, env);
    if (!ft_strncmp(cmd->args[0], "echo", 5))
        ft_echo(cmd, env);
    if (!ft_strncmp(cmd->args[0], "pwd", 4))
        ft_pwd(env);
    if (!ft_strncmp(cmd->args[0], "env", 4))
        ft_env(env);
    if (!ft_strncmp(cmd->args[0], "export", 7))
        ft_export(cmd, env, exec);
    if (!ft_strncmp(cmd->args[0], "unset", 6))
        ft_unset(cmd, env, exec);
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
        free_double(current->args);
        while (current->redir)
        {
            next_redir = current->redir->next;
            free(current->redir->args[0]);
            free(current->redir->args[1]);
            free(current->redir);
            current->redir = next_redir;
        }
        free(current);
        current = next;
    }
}

int main(int argc, char **argv, char **environ)
{    
    static t_exec exec;
    char *input;
    t_map  *env;
    t_cmd  *cmd;

    env = new_map();
    copy_env(env, environ, &exec);
    while (1)
    {
        input = readline("<minishell>: ");
        if (*input)
            add_history(input);
        cmd = parsing(input, NULL);
        free(input);
        if (cmd)
        {
            print_struct(cmd);  
            if (!ft_strncmp(cmd->args[0], "exit", 4))
                break;
            //execute_command(cmd, env, &exec);
        }
        free_list(cmd);
    }
    free_list(cmd);
    rl_clear_history();
    env->destroy(env);
}
