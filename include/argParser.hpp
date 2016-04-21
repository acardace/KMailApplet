#ifndef __MAILAPPLET_ARGPARSER__

#define __MAILAPPLET_ARGPARSER__

#include <argp.h>
#include <string>
#include <vector>

#define AUTHOR_EMAIL  "<anto.cardace@gmail.com>"
#define APPNAME       "KMail Applet 0.1"

using namespace std;

class ArgParser{
public:
  static error_t parse(int argc, char **argv);
  static vector<string> argList;  /* arguments list */
private:
  /* Methods */
  static error_t parser_function(int key, char *arg, struct argp_state *state);
  /* Members */
  static constexpr const char doc[] = "KMail Applet for Maildir format"; /* program info */
  static constexpr const struct argp_option options[] = { /*options*/
    {"maildir", 'm', "DIR", 0,  "Maildir directory to watch" },
    { 0 }
  };
  static constexpr const struct argp argp = {options, parser_function, NULL, doc};  /* struct for argp parser */
};

#endif
