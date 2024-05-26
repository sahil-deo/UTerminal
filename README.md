# Uterminal
UTerminal is open source command line tool consisting of various useful commands.
------------------------------------------------------------------------------
Hello!! Thank you for checking out this command line tool.
------------------------------------------------------------------------------

It is recommended to use Windows PowerShell (or any better terminal like GIT Bash or Msys2 terminals) when using UTerminal as command prompt does not support './'.

To run a command use:
./uterminal [commandname] [arguments]

Commands:
1. Read:
./uterminal read [filename.extention]
eg. ./uterminal read file.txt

2. Search:
./uterminal search [filename.extention] [Word to Search]
eg. ./uterminal search file.txt hello


3. Write:
./uterminal write
eg. ./uterminal write


//when Give a file name is prompted, giving an extention is not necessary.
//when using werite enter 'STOP' to exit.

4. Delete:
./uterminal delete [filename.extention]
eg. ./uterminal delete file.txt


5. Append:
a. ./uterminal append [filename.extention] [filename.extention] 
eg. ./uterminal append file1.txt file2.txt

//Contents of File2 will be appended to File 1

b. ./uterminal append [filename.extention]
eg. ./uterminal append file1.txt

//User will be prompted to write text to be appended in the file.
//enter "STOP" to exit.


NOTE:
> uterminal and filenames are NON-CASE SENISITIVE

> command names and words to be searched are CASE SENSITIVE
