#!/bin/bash

# FTP server details
HOST="ftp.example.com"
USER="your_username"
PASSWORD="your_password"
REMOTE_DIR="/path/to/remote/directory"
LOCAL_FILE="local_file.txt"

# FTP commands using a here-document (EOF)
ftp -inv $HOST <<EOF
user $USER $PASSWORD
cd $REMOTE_DIR
put $LOCAL_FILE
bye
EOF
