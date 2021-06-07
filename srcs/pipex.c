/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 20:37:16 by rcabezas          #+#    #+#             */
/*   Updated: 2021/06/07 21:06:00 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void    arguments(t_pipex *ps, int argc, char **argv)
{
    if (argc != 6)
    {
        ft_putstr("Error\n");
        return (0);
    }
    ft_strcpy(ps->archive_one, argv[1]);
    ft_strcpy(ps->cmd_one, argv[2]);
    ft_strcpy(ps->cmd_two, argv[4]);
    ft_strcpy(ps->archive_two, argv[5]);
    
}

int	    main(int argc, char **argv)
{
    t_pipex *ps;
    
    ps = ft_calloc(4, sizeof(t_pipex));
    arguments(ps, argc, argv);
    return (0);
}