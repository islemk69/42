/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:02:51 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/02/15 15:06:43 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_pipex(t_pipe *p)
{
	if (p->first_cmd)
	{
		ft_free_tab(p->first_cmd);
		p->first_cmd = NULL;
	}
	if (p->second_cmd)
	{
		ft_free_tab(p->second_cmd);
		p->second_cmd = NULL;
	}
	if (p->paths)
	{
		ft_free_tab(p->paths);
		p->paths = NULL;
	}
	if (p->cmd)
	{
		free(p->cmd);
		p->cmd = NULL;
	}
}

void	error(t_pipe *p, char *str)
{
	free_pipex(p);
	perror(str);
}

void	init_tab(t_pipe *p)
{
	p->paths = NULL;
	p->first_cmd = NULL;
	p->second_cmd = NULL;
	p->cmd = NULL;
}

char	*ft_find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!*envp)
		return (NULL);
	return (*envp + 5);
}
