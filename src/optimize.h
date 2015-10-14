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
#ifndef OPTIMIZE_H
#define OPTIMIZIE_H

#include "parse.h"

instruction_list *optimize_brainfuck (instruction_list *);
instruction *optimize_loop (instruction *);

#endif
