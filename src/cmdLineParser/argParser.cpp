#include <argParser.hpp>
#include <argp.h>
#include <iostream>
#include <unistd.h>
#include <boost/filesystem.hpp>

/* global variables for the argp lib */
const char *argp_program_version = APPNAME;
const char *argp_program_bug_address = AUTHOR_EMAIL;
/* private static Members */
constexpr const char ArgParser::doc[];
constexpr const struct argp_option  ArgParser::options[];
std::vector<std::string> ArgParser::argList;  /* arguments list */
constexpr const struct argp ArgParser::argp;  /* structure for argp parser */

using namespace std;
namespace fs = boost::filesystem;

/* Methods implementation */
error_t ArgParser::parse(int argc, char **argv) {
  return argp_parse(&ArgParser::argp, argc, argv, 0, NULL, NULL);
}

error_t ArgParser::parser_function(int key, char *arg, struct argp_state *state){
  switch (key) {
  case 'm':
    if ( fs::exists(arg) && fs::is_directory(arg) && !fs::is_empty(arg) )
      ArgParser::argList.push_back(arg);
    else {
      cerr<<arg<<" : no such file or directory"<<endl;
      return 1;
    }
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}
