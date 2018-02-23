/*
Copyright 2015, 2018 Jochem Raat

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
#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

static void interactive_notice ();
static void interactive_help (char *);

static tape *process_input (tape *, char *);
static tape *process_brainfuck (tape *, char *);
static tape *process_command (tape *, char *);
static char *split_word (char **);

static void read_tape_help ();
static tape *read_tape (char *);

static char *prompt_for_input (char *);


/**
 * Start a interactive etbi session.
 */
void
interactive_session ()
{
  char *line;
  tape *tape = initialize_tape ();

#ifdef HAVE_LIBREADLINE
  initialize_readline ();
#endif

  interactive_notice ();

  while ((line = prompt_for_input (PROMPT)) != NULL)
    {
      tape = process_input (tape, line);
      free (line);
    }

  printf ("\n");
}

/**
 * Print the start notice for an interactive session
 */
static void
interactive_notice ()
{
  printf (PACKAGE_STRING "\n"
          COPYRIGHT_STRING "\n"
          "etbi comes with ABSOLUTELY NO WARRANTY.\n"
          "This program is free software, and you are welcome to redistribute it\n"
          "under certain conditions; type the file `COPYING' for details.\n"
          "\n"
          "Enter `!help' for help\n");
}

/**
 * Process the help with the argument ARG.
 */
static void
interactive_help (char *arg)
{
  if (arg == NULL)
    {
      printf
        ("You can execute brainfuck code by typing it in and hitting enter, after\n"
         "which you are shown the new state of the tape or you can use one of the\n"
         "commands listed below.\n"
         "\n"
         "Available commands:\n"
         "\n");
      printf
        (" !preview CODE    - Preview the optimized code generated from CODE\n"
         " !verbose CODE    - Print the optimized code generated from CODE before\n"
         "                    executing it\n"
         " !read-tape TAPE  - Set the tape to the state read from TAPE\n"
         " !clear           - Reset the tape to the initial state of only zeroes\n"
         " !help [COMMAND]  - Print this help message or if given an argument,\n"
         "                    print the help for COMMAND if it exists\n");
    }
  else
    {
      if (strcmp (arg, "read-tape") == 0)
        read_tape_help ();
      else
        printf ("No help available for %s\n", arg);

    }
}



/**
 * Process the INPUT with the CURRENT_TAPE and return the new state of
 * the tape.
 */
static tape *
process_input (tape *current_tape, char *input)
{
  if (*input == '!')
      return process_command (current_tape, input+1);
  else
    return process_brainfuck (current_tape, input);
}

/**
 * Process INPUT as brainfuck code with CURRENT_TAPE and return the
 * new state of the tape.
 */
static tape *
process_brainfuck (tape *current_tape, char *input)
{
  char *tmp = input;
  instruction_list *insts;

  insts = parse_brainfuck_string (tmp);
  insts = optimize_brainfuck (insts);
  current_tape = eval_sequence (current_tape, insts);

  free_instruction_list (insts);

  print_entire_tape (current_tape);

  return current_tape;
}

/**
 * Process COMMAND as a command with the CURRENT_TAPE and return the
 * new state of the tape.
 */
static tape *
process_command (tape *current_tape, char *command)
{
  char *first = split_word (&command);
  instruction_list *insts;

  if (strcmp (first, "preview") == 0)
    {
      if (command)
        {
          insts = parse_brainfuck_string (command);
          insts = optimize_brainfuck (insts);
          printf ("instructions generated:\n");
          print_instructions (insts);
        }
      else
        printf ("Preview needs one argument\n");
    }
  else if (strcmp (first, "verbose") == 0)
    {
      if (command)
        {
          insts = parse_brainfuck_string (command);
          insts = optimize_brainfuck (insts);
          printf ("instructions generated:\n");
          print_instructions (insts);
          printf("\n");
          current_tape = eval_sequence (current_tape, insts);
          print_entire_tape (current_tape);
        }
      else
        printf ("Verbose needs one argument\n");
    }
  else if (strcmp (first, "clear") == 0)
    {
      free_tape (current_tape);
      current_tape = initialize_tape ();
      print_entire_tape (current_tape);
    }
  else if (strcmp (first, "read-tape") == 0)
    {
      if (command)
        {
          tape *tmp_tape = read_tape (command);
          if (tmp_tape)
            {
              free_tape (current_tape);
              current_tape = tmp_tape;
              print_entire_tape (current_tape);
            }
        }
      else
        printf ("Read-tape needs a tape as argument, see !help read-tape\n");
    }
  else if (strcmp (first, "help") == 0)
    interactive_help (command);
  else
    printf ("Not a valid command: %s\n", first);

  free (first);

  return current_tape;
}

/**
 * Split COMMAND into the first word and the rest. The first word is
 * returned and COMMAND is set to point to the rest.
 */
static char *
split_word (char **command)
{
  char *first, *all = *command;
  int size = 0;

  for (; **command != ' '; (*command)++, size++)
    if (**command == '\0')
      {
        *command = NULL;
        break;
      }

  if (*command)
    (*command)++;

  first = (char *) malloc (sizeof (char) * (size+1));

  strncpy (first, all, size);
  first[size] = '\0';

  return first;
}



/**
 * Print the help message for !read-tape
 */
static void
read_tape_help ()
{
  printf
    ("Usage: !read-tape TAPE\n"
     "Read a new tape from TAPE and set it as the current tape.\n"
     "\n");
  printf
    ("The tape should be a list of numbers seperated by blanks, which represent the\n"
     "cells in the tape. The current cell should be wrapped in < and >."
     "\n");
  printf
    ("Example usage:\n"
     "  etbi> !read-tape 18 0 255 12 <28> 5 0 0 29 0 1\n"
     "  ⇒ ... 18 0 255 12 <28> 5 0 0 29 0 1 ...\n");
}

/**
 * Read the tape from TAPE_STR and return the read tape
 */
static tape *
read_tape (char *tape_str)
{
  tape *tmp_tape = NULL, *current_tape = NULL;
  int
    is_current = 0,
    in_number = 0,
    value = 0,
    cell_index = 0;

  while (1)
    {
      if (*tape_str == '<')
        {
          if (current_tape)
            {
              printf ("read-tape: Unexpected '<', there already is a current cell\n");
              return NULL;
            }
          else
            is_current = 1;
        }
      else if (is_current && *tape_str == '>')
        ;
      else if (isdigit (*tape_str))
        {
          if (!in_number)
            {
              in_number = 1;
              value = 0;
            }
          value = (value * 10) + (*tape_str - '0');
        }
      else if (isblank (*tape_str) || *tape_str == '\0')
        {
          if (!in_number)
            {
              if (*tape_str == '\0')
                break;
              tape_str++;
              continue;
            }

          if (!tmp_tape)
            tmp_tape = initialize_tape ();

          if (cell_index > TAPE_SEGMENT_SIZE-1)
            {
              tmp_tape = tape_right (tmp_tape);
              cell_index = 0;
            }

          if (0 <= value && value <= 255)
            tmp_tape->cells[cell_index] = value;
          else
            {
              printf ("read-tape: %d doesn't fit in a cell\n", value);
              return NULL;
            }

          in_number = 0;

          if (is_current)
            {
              current_tape = tmp_tape;
              current_tape->current_cell = cell_index;
              is_current = 0;
            }

          if (*tape_str == '\0')
            break;

          cell_index++;
        }
      else
        {
          printf
            ("read-tape: Unexpected input at '%c', see !help read-tape\n",
             *tape_str);
          return NULL;
        }

      tape_str++;
    }

  if (!tmp_tape)
    {
      printf ("read-tape: No tape input supplied, see !help read-tape\n");
      return NULL;
    }

  if (!current_tape)
    {
      printf ("read-tape: No current cell given, see !help read-tape\n");
      return NULL;
    }

  return current_tape;
}



#ifdef HAVE_LIBREADLINE
/**
 * Generate commands matching with TEXT.
 */
static char *
command_generator (const char *text, int state)
{
  static int i, len;
  char *name;
  char *commands[] =
    {
      "!preview",
      "!verbose",
      "!clear",
      "!read-tape",
      "!help",
      NULL
    };

  /*
   * STATE = 0 if this is the first time we have been called with this
   * TEXT for the first time, so we do some initialization.
   */
  if (!state)
    {
      i = 0;
      len = strlen (text);
    }

  /* Find the next matching command */
  while ((name = commands[i]))
    {
      i++;

      if (strncmp (name, text, len) == 0)
        return strdup (name);
    }

  return NULL;
}

/**
 * Complete the TEXT iff the word is at the start of the line.
 */
static char **
command_completion (const char *text, int start, int end)
{
  char **matches = NULL;

  if (start == 0)
    matches = rl_completion_matches (text, command_generator);

  return matches;
}

/**
 * Generate no matches in the default case, which happens when we try
 * to complete in the middle of a line.
 */
static char *
no_matches_generator (const char *text, int state)
{
  return NULL;
}

/**
 * Initialize readline, only callable if readline is available
 */
static void
initialize_readline ()
{
  /* Set up completion functions: */
  rl_attempted_completion_function = command_completion;
  rl_completion_entry_function = no_matches_generator;
}
#endif  /* HAVE_LIBREADLINE */

/**
 * Prompt for input using readline and add it to history if readline
 * is available, else print the prompt using printf and get a line
 * with getline. Return the input as a string without the '\n'.
 */
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
