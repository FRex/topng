# topng

Small program to convert an image file to png using two libs from [stb](https://github.com/nothings/stb).

Given two filenames it loads the image from first and saves in second. Given one filename it
will strip one extension from the first, append .png and use that name as the output. Given any
other amount of arguments it will print usage info to stderr and do nothing else.

* Written in pure C
* Handles Unicode filenames on Windows
* Tested on Windows 10 with Visual Studio 2017 and Pelles C
* Tested on Fedora 29 with GCC

If you already have ImageMagick, ffmpeg or any smilar command line tool that
can handle image conversions from many formats to many others then this program
might be of no use to you, except if you like the simpicity of invoking it or
are looking for a small self-contained C program that does this conversion.

Go to releases to download a Windows exe compiled with Pelles C with no `-O2`.

**Warning**: when using Pelles C with `-O2` a certain operation in `stb_image`
(average of two bytes in code handling average filter in png decoding) will
produce incorrect result which will cause some png images to be badly corrupted:
[Pelles C forum bug report](https://forum.pellesc.de/index.php?topic=7837.0).
