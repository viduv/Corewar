/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 10:55:08 by tholzheu          #+#    #+#             */
/*   Updated: 2019/08/30 14:24:05 by jcruz-y-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*static void		init_inst_funct(t_inst_funct *inst_functions[16])
{
	inst_functions[0] = inst_live;*/
	/*inst_functions[1] = &inst_ld;*/
	/*inst_functions[2] = &inst_st;*/
	/*inst_functions[3] = &inst_add;*/
	/*inst_functions[4] = &inst_sub;*/
	/*inst_functions[5] = &inst_and;*/
	/*inst_functions[6] = &inst_or;*/
	/*inst_functions[7] = &inst_xor;*/
	/*inst_functions[8] = &inst_zjmp;*/
	/*inst_functions[9] = &inst_ldi;*/
	/*inst_functions[10] = &inst_sti;*/
	/*inst_functions[11] = &inst_fork;*/
	/*inst_functions[12] = &inst_lld;*/
	/*inst_functions[13] = &inst_lldi;*/
	/*inst_functions[14] = &inst_lfork;*/
	/*inst_functions[15] = &inst_aff;
}*/

/* static inst_functions[16] =
{
	{inst_live},
	{inst_ld},
	{inst_st},

} */

/*
** The loop consists of the main structure and mgmnt of the program,
** during each loop the cycle increases it finishes when 
** cycles_to_die have been reduced to >= 0 via or when there are no more processes 
** The cycles decrease whenever a loop is executed.
*/

void			loop(t_player *players, t_arena *arena)
{
	t_player		*cur;

	printf("cycle_to_die = %d\n", arena->cycle_to_die);
	while (arena->cycle_to_die >= 0)
	{
		cur = players;
		while (cur)
		{
			if (cur->inst->counter == -1 && save_inst(cur, arena) == -1) // if it's -1 it means to save inst
				cur->pc++;
			if (cur->inst->counter == 0)
			{
				printf("cur->inst->op_code = %d\n", cur->inst->op_code);
				//inst_functions[cur->inst->op_code - 1](cur, arena);
			}
			cur->inst->counter != -1 ? cur->inst->counter-- : cur->inst->counter;
			cur = cur->next;
		}
		if (arena->cycle_counter == arena->cycle_to_die)
			if (live_checkup(players, arena) == -1)
				return ;
		graphics(arena, players);
		print_memory(arena->memory);
		print_info(arena, players);
	//	sleep(10);
		break;
		arena->cycle_counter++;
		arena->total_cycles++;
	}
}
