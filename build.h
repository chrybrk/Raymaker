#ifndef __BUILD_H__
#define __BUILD_H__

//Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

//Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

//High intensty background 
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"

//High intensty text
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"

//Bold high intensity text
#define BHBLK "\e[1;90m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define BHMAG "\e[1;95m"
#define BHCYN "\e[1;96m"
#define BHWHT "\e[1;97m"

//Reset
#define reset "\e[0m"
#define CRESET "\e[0m"
#define COLOR_RESET "\e[0m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdarg.h>
#include <stdbool.h>

#define INFO(msg) printf("%s[INFO]: %s%s%s\n", BGRN, BWHT, msg, reset);
#define WARN(msg) printf("%s[WARN]: %s%s%s\n", BYEL, BWHT, msg, reset);
#define ERROR(msg) printf("%s[ERROR]: %s%s%s\n", BRED, BWHT, msg, reset);
#define ACTION(msg) printf("%s[ACTION]: %s%s%s\n", BCYN, BBLU, msg, reset);

static inline void *__safe_callback__(void *PTR, char *F, int LINE, char *FUNCTION_NAME)
{
	if (PTR == NULL)
	{
		fprintf(stdout, "%s:%d :: In %s: \n\tExpected not NULL value, but got NULL.\n", F, LINE, FUNCTION_NAME);
		exit(EXIT_FAILURE);
	}
	
	return PTR;
}

#define safe(value)	__safe_callback__(value, (char*)__FILE__, __LINE__, (char*)__FUNCTION__)

static inline char* writef(char* s, ...)
{
    char* string;
    va_list args;
    va_start(args, s);
    vasprintf(&string, s, args);
    va_end(args);
    return string;
}

static inline char **getFilesFromDirectory(const char *path, int *count)
{
	int internalCounter = 0;
	char **buffer = (char**)safe(malloc(sizeof(char**) * internalCounter));

	DIR *dir = opendir(path);
	if (dir == NULL) return NULL;

	struct dirent *data;
	while ((data = readdir(dir)) != NULL)
	{
		// it means that the current *ptr is a file not a directory
		if (data->d_type != DT_DIR)
		{
			char *fileName = data->d_name;

			internalCounter++;
			buffer = (char**)realloc(buffer, internalCounter * sizeof(char**));

			buffer[internalCounter - 1] = fileName;
		}
	}

	*count = internalCounter;
	return buffer;
}

#endif
