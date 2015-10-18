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
#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tape.h"

static tape *initialize_tape_segment (tape *, tape *);
static char *cell_at(tape *, int);
static tape *tape_left (tape *);
static tape *tape_right (tape *);

/**
 * Return a new initialized tape.
 */
tape *
initialize_tape ()
{
  tape *tape = initialize_tape_segment (NULL, NULL);
  tape->current_cell = TAPE_SEGMENT_SIZE / 2;
  return tape;
}



/**
 * Move TAPE by OFFSET and return the new tape.
 */
tape *
move_tape (tape *tape, int offset)
{
  if ((tape->current_cell + offset >= 0)
      && (tape->current_cell + offset < TAPE_SEGMENT_SIZE))
    tape->current_cell += offset;
  else if (offset < 0)          /* move left */
    {
      offset += tape->current_cell;
      tape = tape_left (tape);

      while (offset < -TAPE_SEGMENT_SIZE)
        {
          offset += TAPE_SEGMENT_SIZE;
          tape = tape_left (tape);
        }

      tape->current_cell = TAPE_SEGMENT_SIZE + offset;
    }
  else                          /* move right */
    {
      offset -= TAPE_SEGMENT_SIZE - tape->current_cell;
      tape = tape_right (tape);

      while (offset > TAPE_SEGMENT_SIZE)
        {
          offset -= TAPE_SEGMENT_SIZE;
          tape = tape_right (tape);
        }

      tape->current_cell = offset;
    }
  return tape;
}

/**
 * Alter the cell in TAPE at OFFSET from the current cell by CHANGE
 * amount.
 */
void
alter_tape (tape *tape, int offset, char change)
{
  char *cell = cell_at (tape, offset);
  *cell += change;
}

/**
 * Set the cell in TAPE at OFFSET from the current cell to VALUE.
 */
void
set_tape (tape *tape, int offset, char value)
{
  char *cell = cell_at (tape, offset);
  *cell = value;
}

/**
 * Return the value of the cell at OFFSET from the current cell in
 * TAPE.
 */
char
get_tape (tape *tape, int offset)
{
  char *cell = cell_at (tape, offset);
  return *cell;
}

/**
 * Return the TAPE moved towards the first cell set to 0 in DIRECTION.
 */
tape *
scan_tape (tape *tape, int direction)
{
  char *cell;

  if (tape->cells[tape->current_cell] == 0)
    return tape;
  else if (direction > 0)            /* right */
    {
      cell = memchr (tape->cells + tape->current_cell, 0,
                     TAPE_SEGMENT_SIZE - tape->current_cell);

      while (!cell)
        {
          tape = tape_right (tape);
          cell = memchr (tape->cells, 0, TAPE_SEGMENT_SIZE);
        }

      tape->current_cell = cell - tape->cells;
      return tape;
    }
  else                          /* left */
    {
      cell = memrchr (tape->cells, 0, tape->current_cell);
      while (!cell)
        {
          tape = tape_left (tape);
          cell = memrchr (tape->cells, 0, TAPE_SEGMENT_SIZE);
        }

      tape->current_cell = cell - tape->cells;
      return tape;
    }
}



/**
 * Return a new initialized tape segment, with left set to LEFT and
 * right set to RIGHT. The cells are initialized to 0, but
 * current_cell is undefined.
 */
static tape *
initialize_tape_segment (tape *left, tape *right)
{
  tape *segment = (tape *) malloc (sizeof (tape));

  segment->left = left;
  segment->right = right;
  segment->cells = (char *) calloc (TAPE_SEGMENT_SIZE, sizeof (char));

  return segment;
}

/**
 * Return a pointer to the cell at OFFSET of the current cell in
 * TAPE.
 */
static char *
cell_at (tape *tape, int offset)
{
  if ((tape->current_cell + offset >= 0)
      && (tape->current_cell + offset < TAPE_SEGMENT_SIZE))
    return &(tape->cells[tape->current_cell + offset]);
  else if (offset < 0)          /* move left */
    {
      offset += tape->current_cell;
      tape = tape_left (tape);

      while (offset < -TAPE_SEGMENT_SIZE)
        {
          offset += TAPE_SEGMENT_SIZE;
          tape = tape_left (tape);
        }

      return &(tape->cells[TAPE_SEGMENT_SIZE + offset]);
    }
  else                          /* move right */
    {
      offset -= TAPE_SEGMENT_SIZE - tape->current_cell;
      tape = tape_right (tape);

      while (offset > TAPE_SEGMENT_SIZE)
        {
          offset -= TAPE_SEGMENT_SIZE;
          tape = tape_right (tape);
        }

      return &(tape->cells[offset]);
    }
}

/**
 * Return the tape segment left of the current in TAPE, if it doesn't
 * exist yet create it.
 */
static tape *
tape_left (tape *tape)
{
  if (tape->left == NULL)
    tape->left = initialize_tape_segment(NULL, tape);

  return tape->left;
}

/**
 * Return the tape segment right of the current in TAPE, if it doesn't
 * exist yet create it.
 */
static tape *
tape_right (tape *tape)
{
  if (tape->right == NULL)
    tape->right = initialize_tape_segment(tape, NULL);

  return tape->right;
}
