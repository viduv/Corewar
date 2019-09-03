/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viduvern <viduvern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 09:10:29 by viduvern          #+#    #+#             */
/*   Updated: 2019/09/02 19:54:04 by viduvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

/*
** OP_Code Number 6;
** Change carry if the result is null
** Usage : ARG_1(REG/IND/DIR) ARG2(REG/IND/DIR) ARG3(REG)
** Applies & (bitwise and) on ARG_1 & ARG_2 and stores the result in ARG_3 reg
*/
static void		inst_and(t_player *cur, t_arena *arena)
{
    int result;

    result = cur->inst->args[0] & cur->inst->args[1];
    cur->carry = (result == 0 )? 1 : 0;
    cur->reg[cur->inst->args[2] - 1] = result;
}