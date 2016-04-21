#include <mailWatcher.hpp>
#include <QFileSystemWatcher>
#include <QStringList>
#include <QString>
#include <QSystemTrayIcon>
#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace std;

const string MailWatcher::NEW_MSG = "New Mail!";
const string MailWatcher::SYSTRAY_NAME = "KMailApplet";
const string MailWatcher::CUR_DIR_NAME = "cur";
const string MailWatcher::NEW_DIR_NAME = "new";
const string MailWatcher::NO_MAIL_ICON_PATH = "images/mail.png";
const string MailWatcher::NEW_MAIL_ICON_PATH = "images/newmail.png";
string mailToWatch;

MailWatcher::MailWatcher(QSystemTrayIcon* sysTrayIcon){
  connect(this, SIGNAL(directoryChanged(const QString)), this, SLOT(slotDirectoryChanged(const QString)));
  this->sysTrayIcon = sysTrayIcon;
}

void MailWatcher::slotDirectoryChanged(const QString& path){
  fs::path pathToWatch(mailToWatch);
  if( fs::is_empty(pathToWatch) ){
    sysTrayIcon->setIcon(QIcon(QString::fromStdString(MailWatcher::NO_MAIL_ICON_PATH)));
  }
  else{
    sysTrayIcon->setIcon(QIcon(QString::fromStdString(MailWatcher::NEW_MAIL_ICON_PATH)));
    sysTrayIcon->showMessage(MailWatcher::SYSTRAY_NAME.c_str(),
      MailWatcher::NEW_MSG.c_str(), QSystemTrayIcon::Information, 10000);
  }
}

bool MailWatcher::isMailDir(std::string& path){
  bool cur_dir = false;
  bool new_dir = false;
  fs::path p(path);
  for(fs::directory_iterator iter(p); iter != fs::directory_iterator(); ++iter){
    if( iter->path().filename().string() == MailWatcher::CUR_DIR_NAME )
      cur_dir = true;
    else if( iter->path().filename().string() == MailWatcher::NEW_DIR_NAME )
      new_dir = true;
  }
  return (new_dir && cur_dir);
}

bool MailWatcher::addMailDirs(QStringList& qList){
  qList.removeDuplicates();
  for(int i=0; i < qList.size(); ++i){
    mailToWatch = qList.at(i).toStdString();
    //check if this is a real Maildir
    if(!isMailDir(mailToWatch))
      return false;
    mailToWatch += MailWatcher::NEW_DIR_NAME.c_str();
    this->addPath( QString::fromStdString(mailToWatch) );
  }
  return true;
}
