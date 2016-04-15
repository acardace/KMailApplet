#ifndef __MAILAPPLET_ARGPARSER__

#define __MAILAPPLET_ARGPARSER__

#include <argp.h>
#include <string>
#include <vector>

#define AUTHOR_EMAIL  "<anto.cardace@gmail.com>"
#define APPNAME       "Plasma Mail Applet 0.1"

class ArgParser{
public:
  static void parse(int argc, char **argv);
private:
  /* Methods */
  static error_t parser_function(int key, char *arg, struct argp_state *state);
  /* Members */
  static std::vector<std::string> argList;  /* arguments list */
  /* program info */
  static constexpr const char doc[] = "Plasma Mail Applet for Maildir format";
  /*options*/
  static constexpr const struct argp_option options[] = {
    {"maildir", 'm', "DIR", 0,  "Maildir directory to watch" },
    { 0 }
  };
  static constexpr const struct argp argp = {options, parser_function, NULL, doc};  /* structure for argp parser */

};

#endif
