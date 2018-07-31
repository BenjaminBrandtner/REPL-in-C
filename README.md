# REPL-in-C
An exercise for myself to create a Read-Evaluate-Print-Loop and/or simple console-like program.

With some help of the tutorial at http://www.buildyourownlisp.com/ .

The basic structure is working. Even that already uses things like pointers to pointers and array of pointers, so I already learnt a lot.  
A thorough explanation of it (in German) can be found [here.](ErklärungGrundgerüst/erklärung.md)

# Installation
This program uses the editline-library for more comfortable user input. Install it using your favourite package manager:
```
sudo apt-get install libedit-dev
```
Then compile, linking the library:
```
gcc *.c -ledit
```
See [this section](http://www.buildyourownlisp.com/chapter4_interactive_prompt#editing_input) of the tutorial mentioned above for more information about using and compiling with editline.

On Windows, custom functions mimicking the libraries functionality are instead compiled, see [here](preprocessorOptions.c).
