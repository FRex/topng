#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_SIMD
#define STB_IMAGE_STATIC
#define STBI_WINDOWS_UTF8
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_STATIC
#define STBIW_WINDOWS_UTF8
#include "stb_image_write.h"

static int my_utf8_main(int argc, char ** argv);
#define BLA_WMAIN_FUNC my_utf8_main
#include "blawmain.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const char * filepath_to_filename(const char * path)
{
    size_t i, len, lastslash;

    len = strlen(path);
    lastslash = 0;
    for(i = 0; i < len; ++i)
        if(path[i] == '/' || path[i] == '\\')
            lastslash = i + 1;

    return path + lastslash;
}

static int print_usage(const char * argv0)
{
    argv0 = filepath_to_filename(argv0);
    fprintf(stderr, "%s - convert image to png using stb\n", argv0);
    fprintf(stderr, "Info : BLA_WMAIN_USING_WMAIN_BOOLEAN = %d\n", BLA_WMAIN_USING_WMAIN_BOOLEAN);
    fprintf(stderr, "Usage: %s input.ext [output.png]\n", argv0);
    return 1;
}

static int print_file_error(const char * msg, const char * filename)
{
    fprintf(stderr, "%s for '%s'\n", msg, filename);
    return 1;
}

static int resave_image(const char * input, const char * output)
{
    int w, h, comp;
    unsigned char * data;
    int writeresult;

    data = stbi_load(input, &w, &h, &comp, 0);
    if(data == NULL)
        return print_file_error("stbi_load returned NULL", input);

    writeresult = stbi_write_png(output, w, h, comp, data, 0);
    stbi_image_free(data);
    if(writeresult == 0)
        return print_file_error("stbi_write_png returned 0", output);

    return 0;
}

static const char * make_outpath(const char * inpath)
{
    size_t i, len, lastslash;
    char * outpath = (char *)calloc(strlen(inpath) + 10, 1);
    if(!outpath)
        return NULL;

    strcpy(outpath, inpath);
    len = strlen(outpath);
    lastslash = 0;
    for(i = 0; i < len; ++i)
        if(outpath[i] == '/' || outpath[i] == '\\')
            lastslash = i + 1;

    if(strrchr(outpath + lastslash, '.'))
        (*strrchr(outpath + lastslash, '.')) = '\0';

    strcat(outpath, ".png");
    return outpath;
}

static int my_utf8_main(int argc, char ** argv)
{
    int retcode = 0;
    const char * outpath;

    if(argc != 2 && argc != 3)
        return print_usage(argv[0]);

    if(argc == 2)
    {
        outpath = make_outpath(argv[1]);
        if(!outpath)
        {
            fputs("calloc failed\n", stderr);
            return 1;
        }
    }
    else
    {
        outpath = argv[2];
    }

    retcode = resave_image(argv[1], outpath);
    if(argc == 2)
        free((void*)outpath);

    return retcode;
}
