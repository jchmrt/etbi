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
#include <getopt.h>
#include <string.h>

#include "parse.h"
#include "optimize.h"
#include "eval.h"
#include "tape.h"

void usage (void);
void version (void);

static int verbose_flag;

int
main (int argc, char **argv)
{
  struct option long_options[] =
    {
      {"verbose", no_argument, &verbose_flag, 1},
      {"version", no_argument, NULL, 'v'},
      {"help", no_argument, NULL, 'h'},
      {"example", required_argument, NULL, 'e'},
      {0, 0, 0, 0}
    };

  int c, option_index = 0;
  char *input_file_name = NULL;

  while ((c = getopt_long (argc, argv, "he:",
                           long_options, &option_index))
         != -1)
    {
      switch (c)
        {
        case 0:
          break;
        case 'v':
          version();
          break;
        case 'h':
          usage ();
          break;
        case 'e':
          input_file_name
            = (char *) malloc (strlen (EXAMPLE_PATH) + strlen (optarg)
                               + strlen (BF_SUFFIX) + 2);
          strcpy (input_file_name, EXAMPLE_PATH);
          strcat (input_file_name, "/");
          strcat (input_file_name, optarg);
          strcat (input_file_name, BF_SUFFIX);
          break;
        case '?':
          break;
        default:
          abort ();
        }
    }

  if (optind < argc)
    input_file_name = argv[optind];

  FILE *input;
  if (input_file_name)
    input = fopen (input_file_name, "r");
  else
    input = stdin;

  if (!input)
    {
      perror(PACKAGE);
      return 1;
    }


  instruction_list *insts = parse_brainfuck (input);
  insts = optimize_brainfuck (insts);
  if (verbose_flag)
    print_instructions (insts);

  eval_brainfuck (insts);

  return 0;
}

/**
 * Print usage message and exit normally
 */
void
usage ()
{
  puts ("usage: etbi [OPTION]... [FILE]");
  exit(0);
}

/**
 * Print version message and exit normally
 */
void
version ()
{
  puts (PACKAGE_STRING);
  puts ("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>");
  puts ("This is free software: you are free to change and redistribute it.");
  puts ("There is NO WARRANTY, to the extent permitted by law.");
  exit(0);
}
