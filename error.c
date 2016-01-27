#include "ft_ls.h"

void usage(void)
{
  ft_putstr("usage: ft_ls [-lRart] [file ...]");
}

void error(char *str, char c)
{
  ft_putstr(str);
  if (c)
  {
    ft_putchar(c);
  }
  ft_putchar('\n');
  usage();
  exit(EXIT_FAILURE);
}
