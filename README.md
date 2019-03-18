# topng

Small program to convert an image file to png using two libs from [stb](https://github.com/nothings/stb).

Given two filenames it loads the image from first and saves in second. Given one filename it
will strip extensions from the first, append .png and use that name as the output. Given any
other amount of arguments it will print usage info to stderr and do nothing else.

* Written in pure C
* Handles Unicode filenames on Windows
* Tested on Windows 10 with Visual Studio 2017 and Pelles C
* Tested on Fedora 29 with GCC

Go to releases to download a Windows exe.
