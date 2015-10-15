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
#ifndef EVAL_H
#define EVAL_H

#include "parse.h"
#include "tape.h"

tape *eval_brainfuck (instruction_list *);
static tape *eval_sequence (tape *, instruction_list *);
static tape *eval_instruction (tape *, instruction *);
static tape *eval_loop (tape *, instruction_list *)

#endif
