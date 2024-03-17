#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "compress.h"

typedef enum {
	COMPRESS,
	DECOMPRESS
} mode;

char *get_file_extension(char *file_name)
{
	while (*file_name != '.' && *file_name != '\0')	file_name += 1;
	if (*file_name == '\0')
		return NULL;
	return file_name;
}

size_t get_file_name_len(char *file_name)
{
	char *file_extension = get_file_extension(file_name);
	if (!file_extension)
		return 0;
	return file_extension - file_name;
}

int main(int argc, char **argv)
{
	char *program = argv[0];
	if (argc < 3)
	{
		fprintf(stderr, "Error: not enough arguments provided\n"
						"Usage: %s [OPTION] [FILE]\n"
						"Options:\n"
						"\t-c\tcompress a .txt file to a .bin file\n"
						"\t-d\tdecompress a .bin file to a .txt file\n"
				, program);
		return 1;
	}
	char *option = argv[1];
	char *input_file_name = argv[2];
	char *file_extension = get_file_extension(input_file_name);
	if (!file_extension) 
	{
		fprintf(stderr, "Error: Provided file does not have an extension\n"
						"Must provide a file with a .bin or .txt extension\n"
				);
		return 1;
	}
	char *input_file_extension, *output_file_extension;
	mode m;
	if (strcmp(option, "-c") == 0)
	{
		input_file_extension = ".txt";
		output_file_extension = ".bin";
		m = COMPRESS;
	}
	else if (strcmp(option, "-d") == 0)
	{
		input_file_extension = ".bin";
		output_file_extension = ".txt";
		m = DECOMPRESS;
	}
	else
	{
		fprintf(stderr, "Error: Unkown option: \"%s\"\n"
						"Available options are \"-c\" for compression and \"-d\" for decompression\n",
				option);
		return 1;
	}
	if (strcmp(file_extension, input_file_extension) != 0)
	{
		fprintf(stderr, "Error: Incorrect file extension for mode \"%s\", must be \"%s\", got \"%s\"\n", option, input_file_extension, file_extension);
		return 1;
	}

	size_t file_name_len = get_file_name_len(input_file_name);
	char *output_file_name = malloc(sizeof(char) * (file_name_len + 5));	// 5 for ".abc\0"
	snprintf(output_file_name, file_name_len + 1, "%s", input_file_name);
	snprintf(output_file_name + file_name_len, 5, "%s", output_file_extension);

	if (m == COMPRESS)
	{
		compress(output_file_name, input_file_name);
	}
	else if (m == DECOMPRESS)
	{
		decompress(output_file_name, input_file_name);
	}
	else
	{
		assert(0 && "Unknown mode");
	}

	free(output_file_name);
	return 0;
}
