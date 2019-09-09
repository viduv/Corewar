/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viduvern <viduvern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 01:22:26 by viduvern          #+#    #+#             */
/*   Updated: 2019/09/08 20:06:08 by viduvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/vm.h"

/*
*  Op Code number 11; T_REG | T_DIR | T_IND, T_DIR | T_REG;
*  Take The value of the first Arg and write it to the cell of the (PC + (arg[1] + arg[2] % IDX_MOD))
*  Change The carry --> 1 if 0 ; 0 if 1.
*/

static  void        write_data(t_player *cur, t_arena *arena)
{
    int i;
    int adress;
    int data;

    adress = cur->write_addr;
    i = 24;
    data = cur->reg[cur->inst->args[0] - 1];
    while (i >= 0)
    {
        adress = (adress == MEM_SIZE) ? 0 : adress;     
        arena->memory[adress] = (unsigned char)(data >> i);
        i -= 8;
        adress++;        
    } 
}

void         inst_sti(t_player *cur, t_arena *arena)
{
    int a; 
    int args;
    int result;

    args = 0;
    a = 4;
    while(a > 0 && ++args)
    {
        if ((cur->inst->ebyte >> a & 3) == REG_CODE)
            cur->inst->args[args] = cur->reg[cur->inst->args[args] - 1];
        else if ((cur->inst->ebyte >> a & 3) == IND_CODE)
        {
            result = get_addr_value(cur, (-cur->inst->size));
            cur->write_addr = get_addr_value(cur, cur->inst->args[args] % IDX_MOD + result);
            memory_to_int(&cur->inst->args[args], arena, cur->write_addr, 4);
        }
        a -= 2;
    }
    result = ((cur->inst->args[1] + cur->inst->args[2]) % IDX_MOD);
    cur->write_addr = get_addr_value(cur, (-cur->inst->size) + result);
     cur->write_bl = 1;
    write_data(cur, arena);
}
