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
#include <QApplication>
#include <QIcon>
#include <QSystemTrayIcon>
#include <QtDebug>
#include <argParser.hpp>
#include <iostream>
#include <mailWatcher.hpp>

int main(int argc, char *argv[]) {
  /* parse cmd line args */
  if (ArgParser::parseCmdLine(argc, argv)) {
    return 1;
  }
  /* parse config file */
  ArgParser::parseConfig();
  if (ArgParser::argList.empty()) {
    qCritical() << argv[0] << ": no Maildirs provided";
    return 1;
  }
  QApplication app(argc, argv);
  /* create the system tray applet */
  if (!QSystemTrayIcon::isSystemTrayAvailable()) {
    qCritical() << argv[0] << "System tray not available, exiting...";
    return 1;
  }
  auto sysTrayIcon = make_shared<QSystemTrayIcon>(
      QIcon(QString::fromStdString(MailWatcher::NO_MAIL_ICON_PATH)));
  /* construct list of maildir to be watched */
  QStringList qArgList;
  for (auto &v : ArgParser::argList) {
    qArgList.append(QString::fromStdString(v));
  }
  MailWatcher mailWatcher(sysTrayIcon);
  if (!mailWatcher.addMailDirs(qArgList)) {
    qCritical() << argv[0] << ": this is not a Maildir directory";
    return 1;
  }
  // check if there are unread mails
  if (mailWatcher.checkMails()) {
    sysTrayIcon->setIcon(
        QIcon(QString::fromStdString(MailWatcher::NEW_MAIL_ICON_PATH)));
  }
  sysTrayIcon->show();
  return app.exec();
}
