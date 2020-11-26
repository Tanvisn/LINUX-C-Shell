Different functionalities associated with shell:
1.pwd: Prints the current working directory.
The corresponding code is present in pwd.c

2.echo: Prints the given input on terminal.
The corresponding code is present in echo.c

3.cd: Changes the directory depending on the flag inputs

Flag specific functionalities:
cd . : Stays in same directory
cd .. : Goes to the parent directory
cd ~ : Goes to the home directory
cd <directory name> : Goes to the inputted directory

If 'cd ..' is inputted in home directory(~), no change in directory.
The path of the directory from which the shell is invoked, is printed.

The corresponding code is present in cd.c

4.ls: Lists the contents of a specific directory based on the flag inputs

Flag specific functionalities:
ls : lists contents of current directory
ls -a : lists contents of current directory (even '.' and '..' are displayed)
ls -l : A detailed description about each file/directory is displayed
ls .. : lists contents of parent directory

The '-a' and '-l' files can be used together that is '-al' or '-la', 
which executes the functions of both the flags.

The corresponding code is present in ls.c

5.Background and Foreground processes:
Processes that run simultaneuosly without interrupting the terminal can be
executed using '<process name> &' input, eg. emacs &

The corresponding code is present in background.c

Processes that require the terminal to wait till the execution is completed can
be executed using '<process name>' input, eg. vi,emacs

6.pinfo: Lists the details of a specific process, has two variations
pinfo : Displays the details of currently running process
pinfo <pid> : Displays the details of process with given process id.

The corresponding code is present in pinfo.c

7. main.c is the file from where specific functions are called according to input.
prompt.c contains the prompt to be printed.

8.Input and output redirection:
The input output redirection for the commands executed using execvp is in foreground.c code.
For rest of the commands, the redirection is in the respective files. Do not create a file with name "sameFileHandling.txt" as the file with this name is used as a buffer when both input and output redirected files are same and file is to be overwritten.

9.Command pipeline:
The code for pipeline is present in pipeline.c

10.User defined commands:-
a.The code for for setenv is in settingenv.c and unsetenv is present in unsettingenv.c
b.code for jobs command is present in jobs.c
c.code for kjob command is present in kjob.c
d. For fg and bg, the codes are in fg.c and bg.c respectively.
e.overkill.c contains the code for overkill
f. code regarding quit and ctrl+d is in commands.c

11.Signal handling:
Code corresponding to this is present in main.c

12.executecom.c contains the code corresponding to detecting whether pipe or background process is present and commands.c contains the function for calling respective commands to be executed
 
13.To run the shell, run
a. make
b. ./a.out











