/*
This file is part of KMailApplet.

KMailApplet is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KMailApplet is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with KMailApplet.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef __MAILAPPLET_ARGPARSER__

#define __MAILAPPLET_ARGPARSER__

#include <argp.h>
#include <string>
#include <vector>

#define AUTHOR_EMAIL "<anto.cardace@gmail.com>"
#define APPNAME "KMail Applet 1.0"

using namespace std;

class ArgParser {
public:
  static void parseConfig();
  static error_t parseCmdLine(int argc, char **argv);
  static vector<string> argList; /* arguments list */
  static string configFile;

private:
  /* Methods */
  static error_t parser_function(int key, char *arg, struct argp_state *state);
  /* Members */
  static constexpr const char doc[] =
      "KMail Applet for Maildir format"; /* program info */
  static constexpr const struct argp_option options[] =
      {/*options*/
       {"maildir", 'm', "DIR", 0, "Maildir directory to watch"},
       {"config", 'c', "FILE", 0, "Configuration file"},
       {0}};
  static constexpr const struct argp argp = {options, parser_function, NULL,
                                             doc}; /* struct for argp parser */
  /* config file parsing */
  static constexpr const char delimiter = '=';
  static const string mailKey;
};

#endif
