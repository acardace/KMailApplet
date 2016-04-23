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
#ifndef __MAILAPPLET_WATCHER__

#define __MAILAPPLET_WATCHER__

#include <QFileSystemWatcher>
#include <QStringList>
#include <QString>
#include <QSystemTrayIcon>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace std;

class MailWatcher :public QFileSystemWatcher {
  Q_OBJECT
public:
    static const string NEW_MSG;
    static const string SYSTRAY_NAME;
    static const string CUR_DIR_NAME;
    static const string NEW_DIR_NAME;
    static const string NO_MAIL_ICON_PATH;
    static const string NEW_MAIL_ICON_PATH;

    vector<fs::path> mailsToWatch;

    explicit MailWatcher(QSystemTrayIcon* sysTrayIcon);
    bool addMailDirs(QStringList& qList);
    QSystemTrayIcon* sysTrayIcon;
    bool checkMails();

public slots:
  	bool slotDirectoryChanged(const QString& path);

private:
    bool isMailDir(fs::path& p);
};

#endif
