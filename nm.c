#include "defs.h"
#include "nm_api.h"


int main(int argc, char *argv[])
{
	int status = 0;

	/* parse command line arguments */
	if (parse_cmd(argc, argv) < 0) {
		manual();
		return EXIT_FAILURE;
	}

	/* initialize library */
	if (ELF_libelf_init() < 0)
		errx(EXIT_FAILURE, "Failed to initialize library");

	/* open an ELF object file */
	if (ELF_open() < 0)
		errx(EXIT_FAILURE, "Failed to open an ELF file");

	/* dump symbol table */
	status = ELF_dump_symtab();
	if (status < 0) {
		fprintf(stderr, "Failed to dump symbol table\n");
		ELF_close();
		return EXIT_FAILURE;
	}

	else if (status == 0) {
		fprintf(stderr, "No symbol table found\n");
		ELF_close();
		return EXIT_SUCCESS;
	}

	ELF_close();
	return EXIT_SUCCESS;
}