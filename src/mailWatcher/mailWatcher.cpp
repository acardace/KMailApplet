#include <mailWatcher.hpp>
#include <QFileSystemWatcher>
#include <QStringList>
#include <QString>
#include <QSystemTrayIcon>
#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace std;

const string MailWatcher::NEW_MSG = "New Mail in ";
const string MailWatcher::SYSTRAY_NAME = "KMailApplet";
const string MailWatcher::CUR_DIR_NAME = "cur";
const string MailWatcher::NEW_DIR_NAME = "new";
const string MailWatcher::NO_MAIL_ICON_PATH = "/usr/share/kmailapplet/images/mail.png";
const string MailWatcher::NEW_MAIL_ICON_PATH = "/usr/share/kmailapplet/images/newmail.png";
string mailToWatch;

MailWatcher::MailWatcher(QSystemTrayIcon* sysTrayIcon){
  connect(this, SIGNAL(directoryChanged(const QString)), this, SLOT(slotDirectoryChanged(const QString)));
  this->sysTrayIcon = sysTrayIcon;
}

void MailWatcher::slotDirectoryChanged(const QString& path){
  fs::path pathToWatch(path.toStdString());
  pathToWatch = *find(mailsToWatch.begin(), mailsToWatch.end(), pathToWatch);
  if( fs::is_empty(pathToWatch) ){
    sysTrayIcon->setIcon(QIcon(QString::fromStdString(MailWatcher::NO_MAIL_ICON_PATH)));
  }
  else{
    string msgText = pathToWatch.parent_path().filename().string();
    //strip first dot if present
    if ( msgText.front() == '.' )
      msgText.erase(0, 1);
    msgText.insert(0, MailWatcher::NEW_MSG);
    sysTrayIcon->setIcon(QIcon(QString::fromStdString(MailWatcher::NEW_MAIL_ICON_PATH)));
    sysTrayIcon->showMessage(MailWatcher::SYSTRAY_NAME.c_str(),
      msgText.c_str(), QSystemTrayIcon::Information, 10000);
  }
}

void MailWatcher::checkMails(){
  for(vector<fs::path>::iterator iter = mailsToWatch.begin(); iter != mailsToWatch.end(); ++iter){
    slotDirectoryChanged(QString::fromStdString(iter->string()));
  }
}

bool MailWatcher::isMailDir(fs::path& p){
  bool cur_dir = false;
  bool new_dir = false;
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
    mailsToWatch.push_back( fs::path( qList.at(i).toStdString() ) );
    //check if this is a real Maildir
    if(!isMailDir(mailsToWatch.back()))
      return false;
    mailsToWatch.back().append( MailWatcher::NEW_DIR_NAME );
    this->addPath( QString::fromStdString(mailsToWatch.back().string()) );
  }
  return true;
}
