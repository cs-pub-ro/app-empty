#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *f;
	unsigned int n = 0;
	int value;
	char *endptr;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <state_file> <value>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	value = strtol(argv[2], &endptr, 10);
	if (*endptr != '\0') {
		fprintf(stderr, "Argument must pe integer value.\n");
		exit(EXIT_FAILURE);
	}

	f = fopen(argv[1], "r+");
	if (f == NULL) {
		fprintf(stderr, "Error opening file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	fread(&n, sizeof(n), 1, f);
	n += value;
	fseek(f, 0, SEEK_SET);
	fwrite(&n, sizeof(n), 1, f);

	fclose(f);
	
	return 0;
}
