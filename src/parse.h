/*
Copyright 2015 Jochem Raat

This file is part of ebti.

ebti is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your
option) any later version.

ebti is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with ebti.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>

enum instruction_type
  {
    INST_MOVE = 1,
    INST_ALTER,
    INST_PRINT,
    INST_READ,
    INST_LOOP,
    INST_CLEAR
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

instruction_list *parse_brainfuck (FILE *);
void print_instructions (instruction_list *);

#endif
