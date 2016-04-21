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

    string mailToWatch;

    explicit MailWatcher(QSystemTrayIcon* sysTrayIcon);
    bool addMailDirs(QStringList& qList);
    QSystemTrayIcon* sysTrayIcon;

public slots:
  	void slotDirectoryChanged(const QString& path);

private:
    bool isMailDir(std::string& path);
};

#endif
