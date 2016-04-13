#include <argParser.h>
#include <iostream>

int main(int argc, char *argv[]) {
  ArgParser argParser(argc, argv);
  argParser.parse();
  return 0;
}
