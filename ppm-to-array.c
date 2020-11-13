/**
 * Copyrights protected by Jaatsoft with Ja8 license...
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pixel {
	u_char r;
	u_char g;
	u_char b;
} __attribute__((packed));

int main(int argc, char **argv)
{
	FILE *fp, *header;
	u_char buf;
	char *line = NULL;
	size_t len = 0;
	size_t cols, rows, b;
	size_t maxVal;
	struct pixel pix;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s ppm-file header-file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	header = fopen(argv[2], "w");
	if (header == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	getline(&line, &len, fp);
	if (strncmp(line, "P6", 2) != 0) {
		fprintf(stderr, "%s is not a valid PPM file\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d %d\n", &cols, &rows);
	fscanf(fp, "%d\n", &maxVal);

	fprintf(header, "/**\n"
                        " #Ja8 copyright protected Jaatstuff by jaat license,\n"
                        " #Ja8 which states use it but not against my country, my people....\n"
			" */\n");

	fprintf(header, "const int PPM_ROWS = %d;\n", rows);
	fprintf(header, "const int PPM_COLS = %d;\n", cols);
	fprintf(header, "const unsigned char ppm_array[%d * %d * 3] = {\n", rows, cols);

	while (fread(&pix, sizeof(struct pixel), 1, fp) == 1) {
		fprintf(header, "0x%x, 0x%x, 0x%x, ", pix.r, pix.g, pix.b);
	}

	fprintf(header, "};");

	free(line);
	fclose(header);
	fclose(fp);
	exit(EXIT_SUCCESS);
}
