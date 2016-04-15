#include <argParser.h>
#include <argp.h>
#include <iostream>

/* global variables for the argp lib */
const char *argp_program_version = APPNAME;
const char *argp_program_bug_address = AUTHOR_EMAIL;
/* private static Members */
constexpr const char ArgParser::doc[];
constexpr const struct argp_option  ArgParser::options[];
std::vector<std::string> ArgParser::argList;  /* arguments list */
constexpr const struct argp ArgParser::argp;  /* structure for argp parser */

/* Methods implementation */
void ArgParser::parse(int argc, char **argv) {
  argp_parse(&ArgParser::argp, argc, argv, 0, NULL, NULL);
}

error_t ArgParser::parser_function(int key, char *arg, struct argp_state *state){
  switch (key) {
  case 'm':
    /* TODO add Maildir to watch list */
    // ArgParser::argList.push_back(arg);
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}
