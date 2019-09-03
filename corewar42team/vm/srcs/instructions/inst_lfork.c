/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viduvern <viduvern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 10:34:12 by viduvern          #+#    #+#             */
/*   Updated: 2019/09/02 15:00:25 by viduvern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

/* 
**	opcode 0x0f
**  usage : lfork ARG_1(D2)
**	same as fork but without % IDX_MOD
**	creates a new process to be placed at the adress (PC + (ARG_1)
**	the new process inherits every state from the father
*/
void		inst_lfork(t_player *cur, t_arena *arena)
{
    return ;
}