/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viduvern <viduvern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 20:32:52 by jcruz-y-          #+#    #+#             */
/*   Updated: 2019/09/01 18:33:26 by viduvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		get_flags(t_arena *arena, int *i, t_player **fplayer)
{
	if (ft_strcmp(arena->argv[*i], "-dump") == 0 &&
	arena->flags->dump_bl == 0)
	{
		if (ft_isdigitstr(arena->argv[*i + 1]) != 1)
			return (print_error(8, *fplayer, arena));
		arena->flags->dump_bl = 1;
		arena->flags->dump_cycles = ft_atoi(arena->argv[*i + 1]);
		*i = *i + 1;
		ft_printf("dump after %d\n", arena->flags->dump_cycles);
		return (1);
	}
	else if (ft_strcmp(arena->argv[*i], "-i") == 0)
	{
		arena->flags->interactive = 1;
		ft_printf("entering interactive mode...\n");
		return (1);
	}
	else
		return (0);
}
