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

static void print_cells (char *, int, char *);

static char *first_non_zero (char *, size_t);
static char *last_non_zero (char *, size_t);

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
 * Print CURRENT_TAPE from the leftmost non-zero cell or the current
 * cell, whichever comes first, to the rightmost non-zero cell or the
 * current cell, whichever comes last.
 */
void
print_entire_tape (tape *current_tape)
{
  tape *begin_tape = current_tape, *end_tape = current_tape;
  char
    *begin_cell,
    *end_cell,
    *current_cell = current_tape->cells + current_tape->current_cell;
  int
    begin_offset,
    end_offset,
    begin_is_current = 0,
    end_is_current = 0;

  /* Get the beginning of non-zero cells */
  while (begin_tape->left)
    begin_tape = begin_tape->left;

  while ((begin_cell
          = first_non_zero (begin_tape->cells, TAPE_SEGMENT_SIZE))
         == NULL)
    {
      if (begin_tape == current_tape)
        {
          begin_is_current = 1;
          break;
        }
      else if (begin_tape->right)
        begin_tape = begin_tape->right;
      else
        {
          printf ("... 0 ...\n");
          return;
        }
    }


  if (begin_is_current)
    begin_offset = current_tape->current_cell;
  else
    begin_offset = begin_tape == current_tape
      ? ((begin_cell - current_tape->cells) < current_tape->current_cell
         ? begin_cell - current_tape->cells : current_tape->current_cell)
      : begin_cell - begin_tape->cells;

  /* Get the end of non-zero cells */
  while (end_tape->right)
    end_tape = end_tape->right;

  while ((end_cell
          = last_non_zero (end_tape->cells, TAPE_SEGMENT_SIZE))
         == NULL)
    {
      if (end_tape == current_tape)
        {
          end_is_current = 1;
          break;
        }
      else if (end_tape->left)
        end_tape = end_tape->left;
      else
        {
          printf ("... 0 ...\n");
          return;
        }
    }

  end_offset = end_is_current
    ? current_tape->current_cell
    : ((end_cell - end_tape->cells) > current_tape->current_cell
       ? end_cell - end_tape->cells : current_tape->current_cell);
  if (end_is_current)
    end_offset = current_tape->current_cell;
  else
    end_offset = end_tape == current_tape
      ? ((end_cell - current_tape->cells) > current_tape->current_cell
         ? end_cell - current_tape->cells : current_tape->current_cell)
      : end_cell - end_tape->cells;


  /* Print the non-zero cells */
  printf ("... ");
  if (begin_tape != end_tape)
    {
      print_cells (begin_tape->cells + begin_offset,
                   TAPE_SEGMENT_SIZE - begin_offset,
                   current_cell);

      begin_tape = begin_tape->right;
      while (begin_tape != end_tape)
        {
          print_cells (begin_tape->cells, TAPE_SEGMENT_SIZE, current_cell);
          begin_tape = begin_tape->right;
        }

      print_cells (end_tape->cells,
                   end_offset + 1,
                   current_cell);

      printf ("...\n");
    }
  else                          /* begin_tape == end_tape */
    {
      print_cells (begin_tape->cells + begin_offset,
                   end_offset - begin_offset + 1,
                   current_cell);
      printf ("...\n");
    }
}

/**
 * Print N cells starting from CELLS, printing the value of the
 * current cell in the special form "<value> ".
 */
static void
print_cells (char *cells, int n, char *current)
{
  for (; n > 0; n--, cells++)
    if (cells == current)
      printf ("<%u> ", (unsigned char) *cells);
    else
      printf ("%u ", (unsigned char) *cells);
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



/**
 * Return a pointer to the first non-zero char in the N chars pointed
 * to by S.
 */
static char *
first_non_zero (char *s, size_t n)
{
  for (; n > 0; s++, n--)
    if (*s)
      return s;

  return NULL;
}

/**
 * Return the a pointer to the last non-zero char in the N chars
 * pointed to by S.
 */
static char *
last_non_zero (char *s, size_t n)
{
  for (s += n-1; n > 0; s--, n--)
    if (*s)
      return s;

  return NULL;
}
