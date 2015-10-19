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
nalong with etbi.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include "eval.h"

static tape *eval_instruction (tape *, instruction *);
static tape *eval_loop (tape *, instruction_list *);

/**
 * Evaluate a list of brainfuck instructions, taking input from stdin
 * and pushing output to stdout. Return the end state of the tape.
 */
tape *
eval_brainfuck (instruction_list *insts)
{
  tape *tape = initialize_tape ();

  tape = eval_sequence (tape, insts);

  return tape;
}

/**
 * Evaluate a list of brainfuck instructions with as initial tape TAPE
 * and return the end state of the tape.
 */
tape *
eval_sequence (tape *tape, instruction_list *insts)
{
  for (; insts; insts = insts->rest)
    tape = eval_instruction (tape, insts->inst);

  return tape;
}

/**
 * Evaluate a single brainfuck instruction with TAPE and return the
 * next state of the tape.
 */
static tape *
eval_instruction (tape *tape, instruction *inst)
{
  char c;
  
  switch (inst->type)
    {
    case INST_MOVE:
      return move_tape (tape, inst->argument.value);
    case INST_ALTER:
      alter_tape (tape, 0, inst->argument.value);
      return tape;
    case INST_PRINT:
      putchar(get_tape (tape, 0));
      return tape;
    case INST_READ:
      c = getchar();
      if (c == EOF)
        return tape;
      set_tape (tape, 0, c);
      return tape;
    case INST_LOOP:
      return eval_loop (tape, inst->argument.insts);
    case INST_CLEAR:
      set_tape (tape, 0, 0);
      return tape;
    case INST_SCAN:
      tape = scan_tape (tape, inst->argument.value);
      return tape;
    }

  return tape;
}

/**
 * Evaluate a loop of instructions with the body INSTS and with the
 * tape TAPE, return the end state of the tape.
 */
static tape *
eval_loop (tape *tape, instruction_list *insts)
{
  while (get_tape (tape, 0))
    tape = eval_sequence (tape, insts);

  return tape;
}
