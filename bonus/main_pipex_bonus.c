/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 12:46:22 by hel-ouar          #+#    #+#             */
/*   Updated: 2023/02/15 14:33:23 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_bonus(int argc, char **argv, char **envp, t_pipe *p)
{
	if (!*envp)
		return (0);
	p->infile = open(argv[1], O_RDONLY);
	p->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p->infile < 0)
		error(p, "error infile");
	if (p->outfile < 0)
		return (error(p, "error outfile"), exit(1), 0);
	p->path = ft_find_path(envp);
	if (!p->path)
		return (error(p, "error env"), exit(0), 0);
	p->paths = ft_split(p->path, ':');
	return (1);
}

void	new_cmd(t_pipe *p, char *str)
{
	p->first_cmd = ft_split(str, ' ');
	if (!p->first_cmd)
		return (error(p, "command not found : "), exit(1));
	p->cmd = init_cmd(p, p->first_cmd);
	if (p->cmd == 0)
		return (error(p, "command not found : "), exit(1));
}

int	pipex_bonus(t_pipe *p, int argc, char **argv, char **envp)
{
	p->x = 0;
	p->nb_process = 0;
	while (p->i < argc - 1)
	{
		new_cmd(p, argv[p->i]);
		pipex_multiple(p, envp, argc);
		dup2(p->fd[0], 0);
		close(p->fd[0]);
		close(p->fd[1]);
		ft_free_tab(p->first_cmd);
		free(p->cmd);
		p->cmd = NULL;
		p->i += 1;
	}
	p->nb_process++;
	close(p->outfile);
	while (p->x <= p->nb_process)
	{
		wait(NULL);
		p->x++;
	}
	p->first_cmd = NULL;
	free_pipex(p);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	p;

	if (argc < 5)
		return (write(2, "error args", 10), 0);
	init_tab(&p);
	p.flg = 0;
	if (argc >= 6 && !ft_strncmp(argv[1], "here_doc", 8))
	{
		p.i = 3;
		p.flg = 1;
		here_doc(&p, argc, argv, envp);
	}
	else
	{
		p.i = 2;
		if (!init_bonus(argc, argv, envp, &p))
			return (0);
	}
	pipex_bonus(&p, argc, argv, envp);
	exit(0);
}
