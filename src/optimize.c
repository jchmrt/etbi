/*
Copyright 2015 Jochem Raat

This file is part of etbi.

etbi is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your
option) any later version.

etbi is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with etbi.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "optimize.h"
#include <stdlib.h>

static instruction *optimize_loop (instruction *);

/**
 * Take a instruction_list and return a version which is optimized by
 * removing empty instructions and replacing clearing loops by CLEAR
 * instructions.
 *
 * NOTE: this function is pretty limited, it doesn't remove empty
 * instructions at the end of the list and it doesn't merge
 * instructions after it removed an empty one in between them. This
 * shouldn't be too much of a problem, because for these situations
 * dont normally arise in bf code.
 */
instruction_list *
optimize_brainfuck (instruction_list *lst)
{
  instruction_list *current;

  for (current = lst; current; current = current->rest)
    {
      switch (current->inst->type)
        {
        case INST_MOVE:
        case INST_ALTER:
          if ((current->inst->argument.value == 0)
              && (current->rest != NULL))
            {
              instruction_list *next = current->rest->rest;
              free (current->inst);
              current->inst = current->rest->inst;
              free (current->rest);
              current->rest = next;
            }
          break;
        case INST_LOOP:
          current->inst = optimize_loop (current->inst);
          break;
        }
    }

  return lst;
}

/**
 * Optimize a LOOP instruction, if it is a clearing loop (for example
 * '[-]'), change it into a CLEAR instruction. Otherwise optimize the
 * inner instructions with optimize_brainfuck and return the
 * instruction.
 */
static instruction *
optimize_loop (instruction  *loop)
{
  instruction_list *loop_insts = loop->argument.insts;
  // Is the loop just a ALTER instruction, if it is that means that
  // the only way in which it can end is clearing the current cell.
  int is_clear_loop = (loop_insts->inst->type == INST_ALTER)
    && (loop_insts->rest == NULL);

  if (is_clear_loop)
    {
      loop->type = INST_CLEAR;
      free (loop_insts->inst);
      free (loop_insts);
    }
  else
    loop->argument.insts = optimize_brainfuck (loop_insts);

  return loop;
}
