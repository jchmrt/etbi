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

#include "parse.h"
#include <stdlib.h>

static void print_instructions_inner (instruction_list *);

/**
 * Parse a brainfuck instruction_list from a FILE f, while the data is
 * parsed, similar instructions are merged immediatly.
 */
instruction_list *
parse_brainfuck (FILE *f)
{
  instruction_list *begin, *current;
  int c;

  begin = NULL;
  current = begin;


  while ((c = fgetc (f)) != EOF)
    {
      int num_arg = 1;
      instruction *current_inst = malloc (sizeof (instruction));
      switch (c)
        {
        case '<':
          num_arg = -1;
        case '>':
          current_inst->type = INST_MOVE;
          current_inst->argument.value = num_arg;
          break;
        case '-':
          num_arg = -1;
        case '+':
          current_inst->type = INST_ALTER;
          current_inst->argument.value = num_arg;
          break;
        case '.':
          current_inst->type = INST_PRINT;
          break;
        case ',':
          current_inst->type = INST_READ;
          break;
        case '[':
          current_inst->type = INST_LOOP;
          current_inst->argument.insts = parse_brainfuck (f);
          break;
        case ']':
          return begin;
        default:
          continue;
        }

      if (begin == NULL)
        {
          begin = (instruction_list *)
            malloc (sizeof (instruction_list));
          current = begin;
          current->inst = current_inst;
          current->rest = NULL;
        }
      else if ((current->inst->type == current_inst->type)
               && ((current_inst->type == INST_MOVE)
                   || (current_inst->type == INST_ALTER)))
        {
          current->inst->argument.value
            += current_inst->argument.value;
          free (current_inst);
        }
      else
        {
          instruction_list *next = malloc (sizeof (instruction_list));
          next->inst = current_inst;
          next->rest = NULL;
          current->rest = next;
          current = next;
        }
    }

  return begin;
}

/**
 * Print the instruction_list to stdout
 */
void
print_instructions (instruction_list *list)
{
  print_instructions_inner (list);
  printf ("\n");
}

static void
print_instructions_inner (instruction_list *list)
{
  for (; list; list = list->rest)
    {
      switch (list->inst->type)
        {
        case INST_MOVE:
          printf (">:%d ", list->inst->argument.value);
          break;
        case INST_ALTER:
          printf ("+:%d ", list->inst->argument.value);
          break;
        case INST_PRINT:
          printf ("print ");
          break;
        case INST_READ:
          printf ("read ");
          break;
        case INST_LOOP:
          printf ("[ ");
          print_instructions_inner (list->inst->argument.insts);
          printf ("] ");
          break;
        case INST_CLEAR:
          printf ("clear ");
        }
    }
}
