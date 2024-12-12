/**
 * \mainpage The **grep utility** is used to concatenate and display the
 * contents of one or more files.
 *
 * \author Andrey addaclic
 * \copyright MIT License
 */

#ifndef MY_GREP_H
#define MY_GREP_H

#ifdef __linux__
#define LC_CASE (opt.c && !opt.l)
#else
#define LC_CASE (opt.c)
#endif

#ifdef __linux__
#define NO_PARAMS_MASSAGE                                                   \
  "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more " \
  "information.\n"
#else
#define NO_PARAMS_MASSAGE                                             \
  "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "    \
  "[-C[num]]\n        [-e pattern] [-f file] [--binary-files=value] " \
  "[--color=when]\n        [--context[=num]] [--directories=action] " \
  "[--label] [--line-buffered]\n        [--null] [pattern] [file ...]\n"
#endif

#define BUFF_SIZE 4092

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Struct for storing options conditions reading from the command line,
 * template count and string with templates
 */
typedef struct {
  char template_str[BUFF_SIZE];
  int template_count;
  char i;
  char n;
  char s;
  char h;
  char v;
  char o;
  char l;
  char c;
  char e;
  char f;
} my_grep_opt;

/**
 * @brief Function for parsing options from the command line
 * @param int first argument of the function argc
 * @param char_ptr second argument of the function argv
 * @param my_cat_opt third argument of the function that contains options
 * @return a condition of success or failure
 */
int parse_opts(const int, char *[], my_grep_opt *);
void e_template(const char *, my_grep_opt *);
void f_template(const char *, my_grep_opt *);

/**
 * @brief Read and print file
 * @param int first argument of the function argc
 * @param char_ptr second argument of the function argv
 * @param my_cat_opt third argument of the function that contains options
 */

void output_file(const int, char *[], my_grep_opt);
void grep_magic(FILE *, const int, const char *, my_grep_opt);

#endif  // MY_GREP_H