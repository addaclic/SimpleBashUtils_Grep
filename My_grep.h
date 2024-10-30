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

typedef struct {
  char pattern_str[BUFF_SIZE];
  int pattern_count;
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

int parse_opts(int, char *[], my_grep_opt *);
void e_pattern(char *, my_grep_opt *);
void f_pattern(char *, my_grep_opt *);
void output_file(int, char *[], my_grep_opt);
void grep_magic(FILE *, int, char *, my_grep_opt);

#endif  // MY_GREP_H