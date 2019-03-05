#include "nm_api.h"

static char *file;
static int file_fd;
static Elf *elf_file;

/*
** Fetches the symbol table
** returns -1 on error and the ELF_symtab_t t is undefined
*/
static int ELF_fetch_symtab(ELF_symtab_t *t);

/*
** Prints manual
*/
extern void manual(void)
{
	printf("./nm elf_file\n"
		   "nm supports both 32 and 64 bit elf\n"
		   "output format: [value | bind | type | name]\n");
}

/*
** Parses command line
** returns -1 on error
*/
extern int parse_cmd(int argc, char **argv)
{
	if (argc != 2)
		return -1;

	file = argv[1];
	return 1;
}

/*
** Initializes libelf library
** Must be called before calling any ELF-related function
** returns -1 on error
*/
extern int ELF_libelf_init(void)
{
	return (elf_version(EV_CURRENT) == EV_NONE) ? -1 : 1;
}

/*
** Opens an ELF object file
** returns -1 on error
*/
extern int ELF_open(void)
{
	Elf_Kind	ek;

	if ((file_fd = open(file, O_RDONLY)) < 0)
		return -1;

	if ((elf_file = elf_begin(file_fd, ELF_C_READ, NULL)) == NULL) {
		close(file_fd);
		return -1;
	}

	ek = elf_kind(elf_file);

	if (ek != ELF_K_ELF) {
		close(file_fd);
		return -1;
	}

	return 1;
}

/*
** Closes an ELF object file
*/
extern void ELF_close(void)
{
	elf_end(elf_file);
	close(file_fd);
}

/*
** Fetches the symbol table
** returns -1 on error and the ELF_symtab_t t is undefined
*/
static int ELF_fetch_symtab(ELF_symtab_t *t)
{
    Elf_Scn			*scn = NULL;
    GElf_Shdr		shdr;
	
	/* Iterate through sections */
	while ((scn = elf_nextscn(elf_file, scn)) != NULL)
	{
		/* Fetch section header */
        gelf_getshdr(scn, &shdr);

        /* Determine section type */
        if (shdr.sh_type == SHT_SYMTAB)
        	break;
    }

    if (!scn)
    	return -1;

    t->section		= scn;
    t->header		= shdr;
    t->n_entries	= shdr.sh_size / shdr.sh_entsize;

    return 1;
}

/*
** Dumps symbol table
** returns 0 if symboltab is not present
** returns -1 on error
*/
extern int ELF_dump_symtab(void)
{
	ELF_symtab_t	t;
	Elf_Data		*data;

	if (ELF_fetch_symtab(&t) < 0)
		return 0;

	/* Fetch symbol table entries */
	data = elf_getdata(t.section, NULL);

	/* Dump entries */
	for (size_t i = 0; i < t.n_entries; i++)
	{
		GElf_Sym sym;
		gelf_getsym(data, i, &sym);

		char *name = elf_strptr(elf_file, t.header.sh_link, sym.st_name);
		if (!name)
			return -1;

		if (*name)
		{
			/* Print value */
			printf("%016lx  ", sym.st_value);
			/* Print binding */
			printf("%d  ", GELF_ST_BIND(sym.st_info));
			/* Print type */
			printf("%d  ", GELF_ST_TYPE(sym.st_info));
			/* Print name */
			printf("%s", name);
			/* Fold line */
			putchar('\n');
		}
	}

	return 1;
}