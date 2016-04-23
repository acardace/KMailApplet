#include <argParser.hpp>
#include <argp.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <limits>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

/* global variables for the argp lib */
const char *argp_program_version = APPNAME;
const char *argp_program_bug_address = AUTHOR_EMAIL;
/* private static Members */
constexpr const char ArgParser::doc[];
constexpr const struct argp_option  ArgParser::options[];
std::vector<std::string> ArgParser::argList;  /* arguments list */
constexpr const struct argp ArgParser::argp;  /* structure for argp parser */
constexpr const char ArgParser::delimiter;
const string ArgParser::mailKey = "mail";
string ArgParser::configFile = "";

using namespace std;
namespace fs = boost::filesystem;

/* Methods implementation */
error_t ArgParser::parseCmdLine(int argc, char **argv) {
  return argp_parse(&ArgParser::argp, argc, argv, 0, NULL, NULL);
}

void ArgParser::parseConfig(){
  if( configFile == "" ){
    configFile = getenv("HOME");
    configFile.append("/.config/kmailapplet.conf");
  }
  if( fs::exists(configFile) && fs::is_regular_file(configFile) ){
    string line;
    ifstream file(configFile);
    while( getline(file, line) ){
      boost::trim(line);
      //skip comments
      if ( line.front() == '#' )
        continue;
      istringstream linestream(line);
      string key;
      if( getline(linestream, key, ArgParser::delimiter) ){
        if( key == ArgParser::mailKey ){
          line.erase(0, line.find_first_of(ArgParser::delimiter)+1 );
          //expand ~ in $HOME
          if( line.front() == '~' )
            line.replace(line.cbegin(), line.cbegin()+1, getenv("HOME"));
          ArgParser::argList.push_back( line );
        }
      }
      if( file.fail() || linestream.fail() ){
        cerr<<"Error: configuration file badly formatted"<<endl;
        break;
      }
    }
  } else {
    cerr<<"Error: configuration file does not exist"<<endl;
  }
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
  case 'c':
    if ( fs::exists(arg) && fs::is_regular_file(arg) && ArgParser::configFile == "" )
      ArgParser::configFile = arg;
    else {
      cerr<<arg<<" : no such file"<<endl;
      return 1;
    }
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}
