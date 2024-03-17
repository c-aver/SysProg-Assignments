#include <stdint.h>
#include <stdio.h>

#include "compress.h"

uint8_t compress_char(char c)
{
	if (c == EOF) return 0;
	return ~(c - '0') & 0xF;
}

uint8_t pack(char c1, char c2)
{
	return (compress_char(c1) << 4) | (compress_char(c2));
}

int compress(char *output_file_name, char *input_file_name)
{
	FILE *output, *input;
	if ((input = fopen(input_file_name, "r")) == NULL)
	{
		perror("Could not open input file for reading");
		return FALSE;
	}

	if ((output = fopen(output_file_name, "wb")) == NULL)
	{
		perror("Could not open output file for writing");
		return FALSE;
	}

	char c1;
	int done = FALSE;
	while ((c1 = getc(input)) != EOF && !done)
	{
		char c2 = getc(input);
		uint8_t packed = pack(c1, c2);
		fwrite(&packed, sizeof(packed), 1, output);
		if (c2 == EOF) done = TRUE;
	}

	fclose(input);
	fclose(output);

	return TRUE;
}

char decompress_char(uint8_t nibble)
{
	if (nibble == 0) return EOF;
	return (~nibble & 0xF) + '0';
}

void unpack(uint8_t byte, char *c1, char *c2)
{
	*c1 = decompress_char(byte >> 4);
	*c2 = decompress_char(byte & 0xF);
}

int decompress(char *output_file_name, char *input_file_name)
{
	FILE *output, *input;
	if ((input = fopen(input_file_name, "rb")) == NULL)
	{
		perror("Could not open input file for reading");
		return FALSE;
	}

	if ((output = fopen(output_file_name, "w")) == NULL)
	{
		perror("Could not open output file for writing");
		return FALSE;
	}

	uint8_t byte;
	while (fread(&byte, sizeof(byte), 1, input) != 0)
	{
		char c1, c2;
		unpack(byte, &c1, &c2);
		putc(c1, output);
		if (c2 != EOF) putc(c2, output);
	}

	fclose(input);
	fclose(output);

	return TRUE;
}
