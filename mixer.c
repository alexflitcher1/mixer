#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // для int64_t
#include <inttypes.h> // для правильного вывода int64_t в printf
int64_t filesize(const char * file_name);
int main(int argc, char **argv)
{
    char ch;
    FILE * files[argc-2];
    FILE * fpw;
    int64_t longs[argc-2];
    if (argc < 3)
    {
        fprintf(stderr, "Use the program: %s file_write file_read1 ... file_read2\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < argc-2; i++)
    {
        if (!strcmp(argv[1], argv[i+2]))
        {
            fprintf(stderr,
            "Name First File Doesn't be same read file\n");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < argc-2; i++)
    {
        if ((longs[i] = filesize(argv[i+2])) == -1)
        {
            fprintf(stderr,
            "Program has been destroyed: File Empty or Doesn't Exist\n");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < argc-2; i++)
    {
        if ((files[i] = fopen(argv[i+2], "rb")) == NULL)
        {
            fprintf(stderr,
            "Program has been destroyed: File Empty or Doesn't Exist\n");
            exit(EXIT_FAILURE);
        }
    }
    if ((fpw = fopen(argv[1], "wb")) == NULL)
    {
        fprintf(stderr,
        "Program has been destroyed: File Empty or Doesn't Exist\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < argc-2; i++)
    {
        for (int j = 0; j < longs[i]; j++)
        {
            ch = getc(files[i]);
            putc(ch, fpw);
        }
    }
    for (int i = 0; i < argc-2; i++)
    {
        if ((fclose(files[i])) != 0)
        {
            fprintf(stderr,
            "Program has been destroyed: File wasn't close\n");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

int64_t filesize(const char * file_name)
{
	int64_t _file_size = 0;
	FILE* fd = fopen(file_name, "rb");

	if(fd == NULL)
		_file_size = -1;
	else
	{
        while(getc(fd) != EOF)
            _file_size++;
		fclose(fd);
	}

	return _file_size;
}
