# KMailApplet
A Mail Applet for the system tray to watch your Maildir box and get notifications whenever there's a new mail.

![alt tag](http://imgur.com/sgBhJ57l.png)
![alt-tag](http://imgur.com/FnQ3qyUl.png)

## Compile  
`$ qmake -o Makefile build.pro`  
`$ make`

## Install
### ArchLinux
install from AUR the package `kmailapplet-git`  
`$ pacaur -S kmailapplet-git`

## Usage
The applet will autostart at login and place itself in the system tray.

## Configuration file
The default conf file will be in `~/.config/kmailapplet.conf`.  
You can get a base file from /usr/share/kmailapplet/kmailapplet.conf  
Here you can specify maildirs to be watched:  
```
#Comments
Mail=~/Maildir/
Mail=~/Maildir/.OtherMail
```

## Help
Just run:  
`$ KMailApplet --help`
