#include "defs.h"
#include <gelf.h>
#include <unistd.h>

/*
** Data type containing relevant informaction
** about symbol table
*/
typedef struct ELF_symtab {
	Elf_Scn		*section;
	GElf_Shdr	header;
	size_t		n_entries;
} ELF_symtab_t;


/*
** Prints manual
*/
extern void manual(void);

/*
** Parses command line
** returns -1 on error
*/
extern int parse_cmd(int argc, char **argv);

/*
** Initializes libelf library
** Must be called before calling any ELF_* function
** returns -1 on error
*/
extern int ELF_libelf_init(void);

/*
** Opens an ELF object file
** returns -1 on error
*/
extern int ELF_open(void);

/*
** Closes an ELF object file
*/
extern void ELF_close(void);

/*
** Dumps symbol table
** returns -1 on error
*/
extern int ELF_dump_symtab(void);