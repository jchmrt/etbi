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
#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>

enum instruction_type
  {
    /* Move by ARG cells */
    INST_MOVE = 1, /* move instruction   argument: int */

    /* Alter current cell by ARG */
    INST_ALTER,    /* alter instruction  argument: int */

    /* Print the current cell */
    INST_PRINT,    /* print instruction  argument: none */

    /* Read into the current cell */
    INST_READ,     /* read instruction   argument: none */

    /* Loop the ARG while current cell isn't zero */
    INST_LOOP,     /* loop instruction   argument: instruction_list */

    /* Clear the current cell */
    INST_CLEAR,    /* clear instruction  argument: none */

    /* Scan for a zero cell to the left if ARG is negative and to the
       right if ARG is positive */
    INST_SCAN      /* scan instruction   argument: int */
  };

typedef struct instruction_list_t
{
  struct instruction_t *inst;
  struct instruction_list_t *rest;
} instruction_list;

typedef struct instruction_t
{
  enum instruction_type type;
  union
  {
    int value;
    instruction_list *insts;
  } argument;
} instruction;

instruction_list *parse_brainfuck_string (char *);
instruction_list *parse_brainfuck (FILE *);
void print_instructions (instruction_list *);

#endif
