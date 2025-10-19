#include "minishell.h"

void print_struct(t_cmd *head);

static void    is_built_in(t_cmd *cmd, t_map *env)
{
    if (!cmd || !cmd->args)
        return;
    if (!cmd || !cmd->args[0])
        return ;
    if (!ft_strncmp(cmd->args[0], "exit", 5))
        ft_exit(0);
    else if (!ft_strncmp(cmd->args[0], "echo", 5))
        ft_echo(cmd);
    else if (!ft_strncmp(cmd->args[0], "pwd", 4))
        ft_pwd();
    else if (!ft_strncmp(cmd->args[0], "env", 4))
        ft_exit(0);        
    if (!ft_strncmp(cmd->args[0], "cd", 3))
        ft_cd(cmd, env);
    if (!ft_strncmp(cmd->args[0], "echo", 5))
        ft_echo(cmd, env);
    if (!ft_strncmp(cmd->args[0], "pwd", 4))
        ft_pwd(env);
    if (!ft_strncmp(cmd->args[0], "env", 4))
        ft_env(env);
    else if (!ft_strncmp(cmd->args[0], "export", 7))
        ft_export(cmd, env);
    else if (!ft_strncmp(cmd->args[0], "unset", 6))
        ft_unset(cmd, env);
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
    // char *args[] = {"export", "-la", NULL};
    // t_cmd cmd = 
    // {
    //     .args=args,
    //     .redir=NULL,
    //     .next=NULL
    // };
    t_exec *exec;
    t_map  *env;
    t_cmd *cmd;

    exec = malloc(sizeof(t_exec));
    if (!exec)
        ft_exit(1);
    copy_env(env, environ, exec);
    env = new_map();
    while (1)
    {
        input = readline("<minishell>: ");
        is_built_in(&cmd, env, exec);
        execute_command(&cmd, env, exec);
        if (*input)
            add_history(input);
        cmd = parsing(input, NULL);
        if (cmd)
        {
            print_struct(cmd);
        // is_built_in(cmd, env);
            if (!ft_strncmp(cmd->args[0], "exit", 5))
                break;
        }
        free_list(cmd);
    }
    free_list(cmd);
    rl_clear_history();
   // env->destroy(env);
}
