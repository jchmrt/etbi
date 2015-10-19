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

#include "config.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#ifdef HAVE_LIBREADLINE
#    include <readline/history.h>
#    include <readline/readline.h>
static void initialize_readline (void);
#endif

#include "interactive.h"
#include "eval.h"
#include "tape.h"
#include "parse.h"
#include "optimize.h"

#define PROMPT "etbi> "

static char *prompt_for_input (char *);

void
interactive_session ()
{
  char *line;
  FILE *tmp_file;
  tape *tape = initialize_tape ();
  instruction_list *insts;

#ifdef HAVE_LIBREADLINE
  initialize_readline ();
#endif

  while ((line = prompt_for_input (PROMPT)) != NULL)
    {
      char *tmp = line;
      tmp_file = tmpfile ();

      while (*tmp != '\0')
        fputc (*(tmp++), tmp_file);

      fseek (tmp_file, 0, SEEK_SET);

      insts = parse_brainfuck (tmp_file);
      insts = optimize_brainfuck (insts);
      tape = eval_sequence (tape, insts);

      print_entire_tape (tape);

      free (line);
    }

  printf ("\n");
}

#ifdef HAVE_LIBREADLINE
static void
initialize_readline ()
{
  /* Rebind <TAB> to insert tab, instead of completing since ther is
     nothing to complete in brainfuck */
  rl_bind_key ('\t', rl_insert);
}
#endif

static char *
prompt_for_input (char* prompt)
{
  char *input;

#ifdef HAVE_LIBREADLINE
  input = readline (prompt);

  if (!input)
    return NULL;

  if (*input)
    add_history (input);
#else
  size_t nbytes = 100;
  int bytes_read;

  printf ("%s", prompt);

  input = (char *) malloc (sizeof (char) * (nbytes + 1));
  bytes_read = getline (&input, &nbytes, stdin);

  if (bytes_read == -1)
    return NULL;

  input[bytes_read-1] = '\0';
#endif

  return input;
}
