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
#ifndef TAPE_H
#define TAPE_H

#define TAPE_SEGMENT_SIZE 100

typedef struct tape_t
{
  struct tape_t *left;
  struct tape_t *right;
  unsigned int current_cell;
  char *cells;
} tape;

tape *initialize_tape (void);

tape *move_tape (tape *, int);
void alter_tape (tape *, int, char);
void set_tape (tape *, int, char);
char get_tape (tape *, int);
tape *scan_tape (tape *, int);

tape *tape_left (tape *);
tape *tape_right (tape *);

void print_entire_tape (tape *);

#endif
