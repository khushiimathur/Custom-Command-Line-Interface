# Custom Command Line Interface


##Overview
This custom-built Command Line Interface (CLI) tool is designed for Linux systems. It provides a set of useful commands to perform common file operations, email handling, and more. The CLI is lightweight, efficient, and easy to use, providing functionalities that simplify file management, email communication, and data manipulation directly from the terminal.


##Features
The following commands are available in this CLI tool:
* list: List the contents of a directory.
* change_dir: Change the directory
* make_dir: Create a new directory.
* remove_dir: Remove an existing directory.
* date: Display the current system date and time.
* display: Display the contents of a file.
* cut_paste: Move a file from one location to another.
* copy_paste: Copy a file from one location to another.
* send-email: Send an email via the terminal.
* convert: Convert files into different formats.


##How to run 
To compile the code run make 
To run the shell run make run


##Commands 

###Internal Commands

 ####working_dir
 -L Display the logical current working directory
 -P Display the physical current working directory 
Warnings Command-line option not recognized 


####echo 
-n do not output the trailing newline 
-E disable interpretation of backslash escapes 
Assumption For this the command line option at the very end will be considered 


####change_dir
 -L Handle the operand dot-dot logically
 -P Handle the operand dot-dot physically 

 
###External Commands 

####list
 -a do not ignore entries starting with . 
-A do not list implied . and .. 
Warnings No such file or directory 


####date
no argument shows local date and time
-u shows the GMT time 
-R output date and time in RFC 5322 format 


####remove_dir
-f ignore nonexistent files and arguments, never prompt 
-i prompt before every removal 
Warnings Missing operands File doesn't exist 


####display
 -E display $ at end of each line 
-n number all output lines 
Warning File name not entered File doesn't exist 


####make_dir
-v print a message for each created directory 
-p no error if existing, make parent directories as needed 
Warning Directory name not entered Unable to create the directory


###New Commands

####copy_paste
* Prompts the user to enter the source file path & Destination directory
* Displays an error if the source file does not exist or cannot be opened.Also, handle cases where the destination directory is invalid.
* Confirms successful file copy with the source and destination paths.


####cut_paste
* Prompts the user to enter the source file path & Destination directory
* Displays an error if the source file does not exist or cannot be opened. Also, handle cases where the destination directory is invalid.
* Confirms successful file move with the source and destination paths.


####send-email
* Enables users to send emails directly from the command-line interface using Python-C integration, streamlining communication within the terminal environment.
* Allows users to specify sender email, recipient email, subject, and message body as command-line inputs, ensuring flexibility and ease of use.
* Includes robust error handling to validate email addresses and provides user feedback on successful or failed email transmissions.


convert
* Allows users to convert files between different formats: plain text to binary, binary to plain text, plain text to hexadecimal, and plain text to Base64.
* Each conversion mode processes the file content line by line or byte by byte, making it suitable for files of various sizes.
* The program checks for errors in file opening (e.g., missing files or permissions) and ensures appropriate messages are displayed to guide the user.
* Confirms successful conversion of the file. 

