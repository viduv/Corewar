/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viclucas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 06:54:27 by viclucas          #+#    #+#             */
/*   Updated: 2019/09/09 10:49:48 by viclucas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../includes/vm.h"

int		init_print(t_window *win, t_player *tmp, t_arena *arena)
{
	t_data data;

	ft_bzero(&data, sizeof(data));
	getbegyx(win->big, data.y, data.x);
	data.tmp = data.x + 2;
	data.x += 2;
	while (data.addr < MEM_SIZE)
	{
			if (data.x == data.tmp + 64 * 3)
			{
				data.x = data.tmp;
				data.y += 1;
			}
			if (data.addr == tmp->pc_inter)
			{
				win->tab[data.addr] = abs(tmp->pnum);
				tmp->oldpc = tmp->pc_inter;
				data.power = tmp->prog_size;
				wattron(win->big, COLOR_PAIR(abs(tmp->pnum)));
				data.color = 1;
				print_color(win, arena, data);
			}
			else if (data.power)
			{
				win->tab[data.addr] = abs(tmp->pnum);
				data.color = 3;
				print_color(win, arena, data);
				data.power--;
				if (!data.power)
					wattroff(win->big, COLOR_PAIR(abs(tmp->pnum)));
			}
			else if (win->first_loop)
			{
				data.color = 3;
				print_color(win, arena, data);
			}
			data.addr += 1;
			data.x += 3;
			data.color = 0;
	}
	return (0);
}

void		print_board(t_window *win)
{
	close_win();
	int i;
	int z;
	
	i = 0;
	z = 0;
	while (z < 4096)
	{
		printf("%d", win->tab[z]);
		if (i == 64)
		{
			printf("\n");
			i = 0;
		}
		else
			i++;
		z++;
	}
	exit(1);
}

void		loop_first_round(t_window *win, t_arena *arena, t_player *p)
{
	t_player	*tmp;
	t_data		data;

	ft_bzero(&data, sizeof(data));
	tmp = p;
	while (tmp)
	{
		init_print(win, tmp, arena);
		win->first_loop = 0;
		tmp = tmp->next;
	}
	win->first_round = 0;
	side_informations(win, p);
	wrefresh(win->big);
	wrefresh(win->side);
	wrefresh(win->down);
	getch_theses(win, 1);
}

t_window	*interactive(t_player *players, t_arena *arena, t_window *win)
{
	getch_theses(win, 0);
	down_infos(win, arena, players);
	write_mem(win, arena, players);
	side_informations(win, players);
	//mvwprintw(win->side, xd, 3, "s = %d\n", sleep_cursor);
	/*
	while (p)
	{
		mvwprintw(win->side, y++, x, "%d\n", p->write_addr);
		wrefresh(win->side);
		p = p->next;
	}
	*/
	wrefresh(win->big);
	wrefresh(win->down);
	wrefresh(win->side);
	usleep(win->sleep);
	return (win);
}
