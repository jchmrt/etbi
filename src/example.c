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
#include <string.h>
#include <glob.h>

#include "example.h"

/**
 * Return the full path to the example called NAME.
 */
char *
example_path (char *name)
{
  char *example_file_name
    = (char *) malloc (strlen (EXAMPLE_PATH) + strlen (name)
                       + strlen (BF_SUFFIX) + 2);
  strcpy (example_file_name, EXAMPLE_PATH);
  strcat (example_file_name, "/");
  strcat (example_file_name, name);
  strcat (example_file_name, BF_SUFFIX);

  return example_file_name;
}

/**
 * Return a list of all available examples by their name.
 */
char **
example_names ()
{
  glob_t result;
  char **examples;
  int i;

  glob (EXAMPLE_PATH "/*" BF_SUFFIX, 0, NULL, &result);

  examples = (char **) malloc (sizeof (char *) * (result.gl_pathc+1));

  for (i = 0; i < result.gl_pathc; i++)
    {
      int                     /* -1 for the '/' after the directory */
        directory_length = strlen (EXAMPLE_PATH) + 1,
        name_length = (strlen (result.gl_pathv[i])
                       - directory_length
                       - strlen (BF_SUFFIX));
      examples[i] = (char *) malloc (sizeof (char) * name_length);
      strncpy (examples[i], result.gl_pathv[i] + directory_length,
               name_length);
    }

  examples[i] = NULL;

  return examples;
}
