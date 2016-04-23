# KMailApplet  
A Mail Applet for the system tray to watch your Maildir box and get notifications whenever there's a new mail.

## Compile  
`qmake -o Makefile build.pro`  
`make`

## Configuration file
The default conf file will be in `~/.config/kmailapplet.conf`.  
Here you can specify maildirs to be watched:
`mail=~/Maildir/`(case insensitive)

## Help  
Just run:  
`KMailApplet --help`  
