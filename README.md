# Uterminal

## UTerminal is open source command line tool consisting of various useful commands.

## Hello!! Thank you for checking out this command line tool.

Before using UTerminal it is important to add to the path of the Environment Variables

Add the Path of the folder where UTerminal is to the path.

1. Search 'Environment Variables' in windows.
2. Go to 'Environment Variables' on the opened window.
3. Under 'User Variables' go to 'path' and click 'Edit'.
4. click on 'New' and paste the path to 'Uterminal.exe'.

Alternatively you can just use './uterminal' before any command if you dont want to set up path but './uterminal' will not work on CMD and will require Windows PowerShell.

---

Note: To run a command use: (if path is not added then use ./uterminal instead of uterminal AND use PowerShell)

uterminal [commandname] [arguments]

---

## Commands:

1. read:
   uterminal read [filename.extention]
   eg. uterminal read file.txt

---

2. search:
   uterminal search [filename.extention] [Word to Search]
   eg. uterminal search file.txt hello

---

3. write:
   uterminal write
   eg. uterminal write

//when Give a file name is prompted, giving an extention is not necessary.
//when using werite enter 'STOP' to exit.

---

4. delete/remove/rm:
   uterminal delete [filename.extention]
   eg. uterminal delete file.txt

//no need to add any extention to delete a folder.
eg. uterminal delete foldername

---

5. append/app:
   a. uterminal append [filename.extention] [filename.extention]
   eg. uterminal append file1.txt file2.txt

//Contents of File2 will be appended to File 1

b. uterminal append [filename.extention]
eg. uterminal append file1.txt

//User will be prompted to write text to be appended in the file.
//enter "STOP" to exit.

---

6. list/ls:
   a. uterminal list
   eg. uterminal list

//lists all files and directories in the current directory

b. uterminal list [.extetion]
eg. uterminal list .exe

//lists all files in the current directory with the specified extention only.

---

7. create:
   uterminal create [directoryName]
   e.g uterminal create Folder

---

8. curl_get
   uterminal curl_get [url] [filename.extension]
   eg. uterminal curl_get https://images.com/catimage.png catImage.png

//curl_get command is used to download files over the internet. head over to curl.se to learn more about curl.

---

9. pwd
   uterminal pwd
   eg. uterminal pwd

//get the present working directory.

---

10. random
    uterminal random [number] [number]
    eg. uterminal random 1 100

//returns a random number from the range of provided numbers.
//only returns integers ( even if float are provided they are rounded off to the nearest integer).
//order of numbers does not matter ( n1 can be less or greater than n2).

---

NOTE:

> uterminal and filenames are NON-CASE SENISITIVE

> command names and words to be searched are CASE SENSITIVE
