
#include "minishell.h"

void    ft_unset(t_built *built)
{
    int i;

    i = 1;
    // while(built->input[i])
    // {
    //         printf("%s\n", built->input[i]);
    //         i++;
    // }
    if (built->exported)
    {
        while (built->input[i])
        {
            built->exported->remove(built->exported, built->input[i]);
            built->exported_len--;
            i++;
        }
    }
}
