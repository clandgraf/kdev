/*
 *
 * File:   util.h
 * Author: Christoph Landgraf
 *
 */

#include <assert.h>
#include <stdlib.h>

#include "../src/util.h"

void test_strlen()
{
  assert(strlen("Hallo") == 5);
  assert(strlen("") == 0);
}

int main(int ac, char ** av)
{
  test_strlen();

  return EXIT_SUCCESS;
}
