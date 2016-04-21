#include <argParser.hpp>
#include <mailWatcher.hpp>
#include <iostream>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QIcon>

int main(int argc, char *argv[]) {
  /* parse cmd line args */
  if( ArgParser::parse(argc, argv) ){
    exit(1);
  }
  QApplication app(argc, argv);
  /* create the system tray applet */
  if ( !QSystemTrayIcon::isSystemTrayAvailable() ){
    cerr<<argv[0]<<": System tray not available, exiting..."<<endl;
    return 1;
  }
  QSystemTrayIcon sysTrayIcon(QIcon(QString::fromStdString(MailWatcher::NO_MAIL_ICON_PATH)));
  /* construct list of maildir to be watched */
  QStringList qArgList;
  for(auto& v: ArgParser::argList){
    qArgList.append(QString::fromStdString(v));
  }
  MailWatcher mailWatcher(&sysTrayIcon);
  if( !mailWatcher.addMailDirs(qArgList) ){
    cerr<<argv[0]<<": this is not a Maildir directory"<<endl;
    return 1;
  }
  sysTrayIcon.show();
  return app.exec();
}
