/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-y- <jcruz-y-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 01:22:18 by viduvern          #+#    #+#             */
/*   Updated: 2019/09/03 19:13:00 by jcruz-y-         ###   ########.fr       */
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
    unsigned char ebyte;
    int adress;
    int get_byte;
    ebyte = cur->inst->ebyte >> 6 & 3;
    if (ebyte == DIR_CODE|| ebyte == REG_CODE) 
    {
        adress = get_addr_value(cur, (-cur->inst->size) + (cur->inst->args[0] + cur->inst->args[1]));
        memory_to_int(&get_byte, arena, adress, 4);
        cur->carry = (get_byte == 0) ? 1 : 0;
        cur->reg[cur->inst->args[2] - 1] = get_byte;
    }
    else
    {
        adress = get_addr_value(cur, (-cur->inst->size) + (cur->inst->args[0] % IDX_MOD)); /// CHECK IF IDXMOD FOR IND
        memory_to_int(&get_byte, arena, adress, 4);
        adress = get_addr_value(cur, (-cur->inst->size) + (get_byte + cur->inst->args[1]));
        get_byte = 0;
        memory_to_int(&get_byte, arena, adress, 4);
        cur->carry = (get_byte == 0) ? 1 : 0;
        cur->reg[cur->inst->args[2] - 1] = get_byte;      
    }
}



