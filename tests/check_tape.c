/*
Copyright 2015, 2016 Jochem Raat

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
#include "../src/tape.h"

#include "check_tape.h"

START_TEST (initial_tape_test)
{
  tape *t = initialize_tape ();
  ck_assert_uint_eq (0, get_tape (t, 0));
  free_tape (t);
}
END_TEST

START_TEST (get_right_test)
{
  tape *t = initialize_tape ();
  ck_assert_uint_eq (0, get_tape (t, 5));
  free_tape (t);
}
END_TEST

START_TEST (get_left_test)
{
  tape *t = initialize_tape ();
  ck_assert_uint_eq (0, get_tape (t, -5));
  free_tape (t);
}
END_TEST

START_TEST (get_right_almost_next_test)
{
  tape *t = initialize_tape ();
  ck_assert_uint_eq (0, get_tape (t, 49));
  free_tape (t);
}
END_TEST

START_TEST (get_left_almost_next_test)
{
  tape *t = initialize_tape ();
  ck_assert_uint_eq (0, get_tape (t, -50));
  free_tape (t);
}
END_TEST

START_TEST (get_right_next_test)
{
  tape *t = initialize_tape ();
  ck_assert_uint_eq (0, get_tape (t, 50));
  free_tape (t);
}
END_TEST

START_TEST (get_left_next_test)
{
  tape *t = initialize_tape ();
  ck_assert_uint_eq (0, get_tape (t, -51));
  free_tape (t);
}
END_TEST



START_TEST (set_current_test)
{
  tape *t = initialize_tape ();
  set_tape (t, 0, 8);
  ck_assert_uint_eq (8, get_tape (t, 0));
  free_tape (t);
}
END_TEST

START_TEST (set_right_test)
{
  tape *t = initialize_tape ();
  set_tape (t, 5, 14);
  ck_assert_uint_eq (14, get_tape (t, 5));
  free_tape (t);
}
END_TEST

START_TEST (set_left_test)
{
  tape *t = initialize_tape ();
  set_tape (t, -12, 4);
  ck_assert_uint_eq (4, get_tape (t, -12));
  free_tape (t);
}
END_TEST

START_TEST (set_right_almost_next_test)
{
  tape *t = initialize_tape ();
  set_tape (t, 49, 5);
  ck_assert_uint_eq (5, get_tape (t, 49));
  free_tape (t);
}
END_TEST

START_TEST (set_left_almost_next_test)
{
  tape *t = initialize_tape ();
  set_tape (t, -50, 5);
  ck_assert_uint_eq (5, get_tape (t, -50));
  free_tape (t);
}
END_TEST

START_TEST (set_right_next_test)
{
  tape *t = initialize_tape ();
  set_tape (t, 120, 8);
  ck_assert_uint_eq (8, get_tape (t, 120));
  free_tape (t);
}
END_TEST

START_TEST (set_left_next_test)
{
  tape *t = initialize_tape ();
  set_tape (t, -123, 8);
  ck_assert_uint_eq (8, get_tape (t, -123));
  free_tape (t);
}
END_TEST

START_TEST (set_far_right_test)
{
  tape *t = initialize_tape ();
  set_tape (t, 2345, 8);
  ck_assert_uint_eq (8, get_tape (t, 2345));
  free_tape (t);
}
END_TEST

START_TEST (set_far_left_test)
{
  tape *t = initialize_tape ();
  set_tape (t, -3456, 8);
  ck_assert_uint_eq (8 , get_tape (t, -3456));
  free_tape (t);
}
END_TEST

START_TEST (set_double_test)
{
  tape *t = initialize_tape ();
  set_tape (t, 0, 8);
  set_tape (t, 0, 20);
  ck_assert_uint_eq (20, get_tape (t, 0));
  free_tape (t);
}
END_TEST



START_TEST (move_right_test)
{
  tape *t = initialize_tape ();
  set_tape (t, -5, 8);
  t = move_tape (t, 4);
  ck_assert_uint_eq (8, get_tape (t, -9));
  free_tape (t);
}
END_TEST

START_TEST (move_left_test)
{
  tape *t = initialize_tape ();
  set_tape (t, -8, 8);
  t = move_tape (t, -13);
  ck_assert_uint_eq (8, get_tape (t, 5));
  free_tape (t);
}
END_TEST

START_TEST (move_right_almost_next_test)
{
  tape *t = initialize_tape ();
  set_tape (t, 53, 8);
  t = move_tape (t, 49);
  ck_assert_uint_eq (8, get_tape (t, 4));
  free_tape (t);
}
END_TEST

START_TEST (move_left_almost_next_test)
{
  tape *t = initialize_tape ();
  set_tape (t, -55, 8);
  t = move_tape (t, -50);
  ck_assert_uint_eq (8, get_tape (t, -5));
  free_tape (t);
}
END_TEST

START_TEST (move_right_next_test)
{
  tape *t = initialize_tape ();
  set_tape(t, 0, 8);
  t = move_tape (t, 103);
  ck_assert_uint_eq (8, get_tape (t, -103));
  free_tape (t);
}
END_TEST

START_TEST (move_left_next_test)
{
  tape *t = initialize_tape ();
  set_tape (t, 0, 8);
  t = move_tape (t, -108);
  ck_assert_uint_eq (8, get_tape (t, 108));
  free_tape (t);
}
END_TEST

START_TEST (move_far_right_test)
{
  tape *t = initialize_tape ();
  set_tape (t, 0, 8);
  t = move_tape (t, 1234);
  ck_assert_uint_eq (8, get_tape (t, -1234));
  free_tape (t);
}
END_TEST

START_TEST (move_far_left_test)
{
  tape *t = initialize_tape ();
  set_tape (t, 0, 8);
  t = move_tape (t, -2345);
  ck_assert_uint_eq (8, get_tape (t, 2345));
  free_tape (t);
}
END_TEST

START_TEST (move_right_left_test)
{
  tape *t = initialize_tape ();
  set_tape (t, 10, 8);
  t = move_tape (t, 240);
  t = move_tape (t, -340);
  ck_assert_uint_eq (8, get_tape (t, 110));
  free_tape (t);
}
END_TEST



START_TEST (alter_up_test)
{
  tape *t = initialize_tape ();
  alter_tape (t, 0, 5);
  ck_assert_uint_eq (5, get_tape (t, 0));
  free_tape (t);
}
END_TEST

START_TEST (alter_down_test)
{
  tape *t = initialize_tape ();
  set_tape (t, 0, 50);
  alter_tape (t, 0, -8);
  ck_assert_uint_eq (42, get_tape (t, 0));
  free_tape (t);
}
END_TEST

START_TEST (alter_up_down_test)
{
  tape *t = initialize_tape ();
  alter_tape (t, 0, 80);
  alter_tape (t, 0, -20);
  ck_assert_uint_eq (60, get_tape (t, 0));
  free_tape (t);
}
END_TEST



START_TEST (scan_right_test)
{
  tape *t = initialize_tape ();
  int i;

  for (i = 0; i < 45; i++)
    set_tape (t, i, 5);

  t = scan_tape (t, 5);

  ck_assert_uint_eq (0, get_tape (t, 0));
  ck_assert_uint_eq (5, get_tape (t, -1));

  free_tape (t);
}
END_TEST

START_TEST (scan_left_test)
{
  tape *t = initialize_tape ();
  int i;

  for (i = 0; i < 45; i++)
    set_tape (t, -i, 5);

  t = scan_tape (t, -1);

  ck_assert_uint_eq (0, get_tape (t, 0));
  ck_assert_uint_eq (5, get_tape (t, 1));

  free_tape (t);
}
END_TEST

START_TEST (scan_right_next_test)
{
  tape *t = initialize_tape ();
  int i;

  for (i = 0; i < 80; i++)
    set_tape (t, i, 5);

  t = scan_tape (t, 1);

  ck_assert_uint_eq (0, get_tape (t, 0));
  ck_assert_uint_eq (5, get_tape (t, -1));

  free_tape (t);
}
END_TEST

START_TEST (scan_left_next_test)
{
  tape *t = initialize_tape ();
  int i;

  for (i = 0; i < 80; i++)
    set_tape (t, -i, 5);

  t = scan_tape (t, -1);

  ck_assert_uint_eq (0, get_tape (t, 0));
  ck_assert_uint_eq (5, get_tape (t, 1));

  free_tape (t);
}
END_TEST

START_TEST (scan_far_right_test)
{
  tape *t = initialize_tape ();
  int i;

  for (i = 0; i < 1234; i++)
    set_tape (t, i, 5);

  t = scan_tape (t, 1);

  ck_assert_uint_eq (0, get_tape (t, 0));
  ck_assert_uint_eq (5, get_tape (t, -1));

  free_tape (t);
}
END_TEST

START_TEST (scan_far_left_test)
{
  tape *t = initialize_tape ();
  int i;

  for (i = 0; i < 1234; i++)
    set_tape (t, -i, 5);

  t = scan_tape (t, -1);

  ck_assert_uint_eq (0, get_tape (t, 0));
  ck_assert_uint_eq (5, get_tape (t, 1));

  free_tape (t);
}
END_TEST

START_TEST (scan_current_zero_test)
{
  tape *t = initialize_tape ();
  int i;

  for (i = 1; i < 1234; i++)
    set_tape (t, i, 5);

  t = scan_tape (t, 1);

  ck_assert_uint_eq (0, get_tape (t, 0));
  ck_assert_uint_eq (5, get_tape (t, 1));

  free_tape (t);
}
END_TEST



Suite *
tape_suite (void)
{
  Suite *s = suite_create ("tape");
  TCase *tc_get = tcase_create ("get"),
    *tc_set = tcase_create ("set"),
    *tc_move = tcase_create ("move"),
    *tc_alter = tcase_create ("alter"),
    *tc_scan = tcase_create ("scan");

  tcase_add_test (tc_get, initial_tape_test);
  tcase_add_test (tc_get, get_right_test);
  tcase_add_test (tc_get, get_left_test);
  tcase_add_test (tc_get, get_right_almost_next_test);
  tcase_add_test (tc_get, get_left_almost_next_test);
  tcase_add_test (tc_get, get_right_next_test);
  tcase_add_test (tc_get, get_left_next_test);

  tcase_add_test (tc_set, set_current_test);
  tcase_add_test (tc_set, set_right_test);
  tcase_add_test (tc_set, set_left_test);
  tcase_add_test (tc_set, set_right_almost_next_test);
  tcase_add_test (tc_set, set_left_almost_next_test);
  tcase_add_test (tc_set, set_right_next_test);
  tcase_add_test (tc_set, set_left_next_test);
  tcase_add_test (tc_set, set_far_right_test);
  tcase_add_test (tc_set, set_far_left_test);
  tcase_add_test (tc_set, set_double_test);

  tcase_add_test (tc_move, move_right_test);
  tcase_add_test (tc_move, move_left_test);
  tcase_add_test (tc_move, move_right_almost_next_test);
  tcase_add_test (tc_move, move_left_almost_next_test);
  tcase_add_test (tc_move, move_right_next_test);
  tcase_add_test (tc_move, move_left_next_test);
  tcase_add_test (tc_move, move_far_right_test);
  tcase_add_test (tc_move, move_far_left_test);
  tcase_add_test (tc_move, move_right_left_test);

  tcase_add_test (tc_alter, alter_up_test);
  tcase_add_test (tc_alter, alter_down_test);
  tcase_add_test (tc_alter, alter_up_down_test);

  tcase_add_test (tc_scan, scan_right_test);
  tcase_add_test (tc_scan, scan_left_test);
  tcase_add_test (tc_scan, scan_right_next_test);
  tcase_add_test (tc_scan, scan_left_next_test);
  tcase_add_test (tc_scan, scan_far_right_test);
  tcase_add_test (tc_scan, scan_far_left_test);
  tcase_add_test (tc_scan, scan_current_zero_test);

  suite_add_tcase (s, tc_get);
  suite_add_tcase (s, tc_set);
  suite_add_tcase (s, tc_move);
  suite_add_tcase (s, tc_alter);
  suite_add_tcase (s, tc_scan);

  return s;
}
