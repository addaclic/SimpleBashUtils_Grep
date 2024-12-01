#include "My_grep.h"

int main(int argc, char *argv[]) {
  my_grep_opt opt = {0};
  if (argc == 1) {
    fprintf(stderr, NO_PARAMS_MASSAGE);
  } else {
    if (!(parse_opts(argc, argv, &opt))) {
      output_file(argc, argv, opt);
    }
  }
  return 0;
}

int parse_opts(int argc, char *argv[], my_grep_opt *opt) {
  int back_char;
  while ((back_char = getopt_long(argc, argv, "inhlce:vf:", NULL, NULL)) !=
         -1) {
    switch (back_char) {
      case 'i':
        opt->i = 1;
        break;
      case 'n':
        opt->n = 1;
        break;
      case 's':
        opt->s = 1;
        break;
      case 'h':
        opt->h = 1;
        break;
      case 'v':
        opt->v = 1;
        break;
      case 'l':
        opt->l = 1;
        break;
      case 'c':
        opt->c = 1;
        break;
      case 'e':
        opt->e = 1;
        e_template(optarg, opt);
        break;
      case 'f':
        opt->f = 1;
        f_template(optarg, opt);
        break;
      case 'o':
        opt->o = 1;
        break;
      default:
        fprintf(stderr, "grep: illegal option -- %c\n", back_char);
        return 1;
    }
  }
  if (!opt->template_count) {
    strcat(opt->template_str, argv[optind++]);
    ++(opt->template_count);
  }
  return 0;
}

void e_template(char *optarg, my_grep_opt *opt) {
  if (opt->template_count) strcat(opt->template_str, "|");
  strcat(opt->template_str, optarg);
  ++(opt->template_count);
}

void f_template(char *optarg, my_grep_opt *opt) {
  FILE *template_file;
  if ((template_file = fopen(optarg, "r")) == NULL) {
    fprintf(stderr, "grep: %s: No such file or directory\n", optarg);
  } else {
    char template_str[BUFF_SIZE];
    while (fgets(template_str, BUFF_SIZE, template_file) != NULL) {
      if (opt->template_count) strcat(opt->template_str, "|");
      if (template_str[0] == '\n')
        strcat(opt->template_str, ".");
      else {
        if (template_str[strlen(template_str) - 1] == '\n')
          template_str[strlen(template_str) - 1] = '\0';
        strcat(opt->template_str, template_str);
      }
      ++(opt->template_count);
    }
  }
}

void output_file(int argc, char *argv[], my_grep_opt opt) {
  for (int i = optind; i < argc; ++i) {
    FILE *file_name;
    if ((file_name = fopen(argv[i], "r")) == NULL) {
      if (!opt.s)
        fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
    } else {
      grep_magic(file_name, argc, argv[i], opt);
    }
  }
}

void grep_magic(FILE *file_name, int argc, char *name_of_file,
                my_grep_opt opt) {
  regex_t template_struct = {0};
  regmatch_t match = {0};
  int reg_param = REG_EXTENDED;
  if (opt.i) reg_param = REG_EXTENDED | REG_ICASE;
  regcomp(&template_struct, opt.template_str, reg_param);
  char file_str[BUFF_SIZE];
  int str_num = 1;
  int count_match = 0;
  while (fgets(file_str, BUFF_SIZE, file_name) != NULL) {
    if (file_str[strlen(file_str) - 1] == '\n')
      file_str[strlen(file_str) - 1] = '\0';
    int res_of_match = regexec(&template_struct, file_str, 1, &match, 0);
    if (opt.v) res_of_match = !res_of_match;
    if (!res_of_match) {
      ++count_match;
      if (!opt.c && !opt.l) {
        if (!opt.h && argc - optind > 1) printf("%s:", name_of_file);
        if (opt.n) printf("%d:", str_num);
        printf("%s\n", file_str);
      }
    }
    ++str_num;
  }
  if LC_CASE {
    if (!opt.h && argc - optind > 1) printf("%s:", name_of_file);
    printf("%d\n", count_match);
  }
  if (opt.l && count_match) printf("%s\n", name_of_file);

  regfree(&template_struct);
  fclose(file_name);
}
