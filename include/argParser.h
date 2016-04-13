#ifndef __MAILAPPLET_ARGPARSER__

#define __MAILAPPLET_ARGPARSER__

#include <argp.h>

#define AUTHOR_EMAIL  "<anto.cardace@gmail.com>"
#define APPNAME       "Plasma Mail Applet 0.1"

class ArgParser{
public:
  ArgParser(int argc, char **argv);
  void parse();
private:
  /* Members */
  int argc;
  char **argv;
  /* program info */
  static constexpr const char doc[] = "Plasma Mail Applet for Maildir format";
  /*options*/
  static constexpr const struct argp_option options[] = {
    {"maildir", 'm', "DIR", 0,  "Maildir directory to watch" },
    { 0 }
  };
  /* structure for argp parser */
  static struct argp argp;
  
  /* Methods */
  static error_t parser_function(int key, char *arg, struct argp_state *state);
};

#endif
