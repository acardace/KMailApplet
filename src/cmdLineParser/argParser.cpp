#include <argParser.h>
#include <argp.h>
#include <iostream>

/* global variables for the argp lib */
const char *argp_program_version = APPNAME;
const char *argp_program_bug_address = AUTHOR_EMAIL;

/* private members */
constexpr const char ArgParser::doc[];
constexpr const struct argp_option ArgParser::options[];
struct argp ArgParser::argp;

/* Methods implementation */
ArgParser::ArgParser(int argc, char **argv){
  this->argc = argc;
  this->argv = argv;
  this->argp = { this->options, this->parser_function, NULL, this->doc };
}

void ArgParser::parse(){
  argp_parse(&this->argp, this->argc, this->argv, 0, NULL, NULL);
}

error_t ArgParser::parser_function(int key, char *arg, struct argp_state *state){
  switch (key) {
  case 'm':
    /* TODO add Maildir to watch list */
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}
