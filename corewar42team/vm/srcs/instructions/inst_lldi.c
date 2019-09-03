/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viduvern <viduvern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 01:22:18 by viduvern          #+#    #+#             */
/*   Updated: 2019/09/02 19:30:53 by viduvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
/*
**	ft_lldi
**	opcode 0x0a, changes the carry
**  usage : lldi ARG_1(RG/ID/D2), ARG_2(ID/D2), ARG_3(RG)
**	same as ldi but without % IDX_MOD
**	reads REG_SIZE at the adress process->pc + (ARG_1 + ARG_2) and stores it
**	in ARG_3
**
*/
void	    	inst_lldi(t_player *cur, t_arena *arena)
{
    int result_adress;
    int move_pc;
    char e_pair;
    int tmp_pc;

    result_adress = 0;
    move_pc = ((cur->inst->args[0] + cur->inst->args[1]));
    cur->carry = (move_pc == 0) ? 1 : 0;
    e_pair = cur->inst->ebyte >> 6 & 3;
    if(e_pair == REG_CODE)
     {
        advance_proc_pc(&cur, (cur->pc, (-4)));
        tmp_pc = cur->pc;
     }
    else
      {
        advance_proc_pc(&cur,(cur->pc, (-5)));
        tmp_pc = cur->pc;
      }
    advance_proc_pc(&cur, (cur->pc + move_pc));
    memory_to_int(&result_adress, arena, cur->pc, 4);
    cur->reg[cur->inst->args[2] - 1] = result_adress;
    cur->carry = (result_adress == 0) ? 1 : 0;
    advance_proc_pc(&cur,(-(tmp_pc + move_pc)));
    e_pair == REG_CODE ? advance_proc_pc(&cur, 4) : advance_proc_pc(&cur, 5);
}
