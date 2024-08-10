#define VERSION 0.0.1
#define LIB_PATH "lib/"
#define SRC_PATH "src/"
#define BIN_PATH "bin/"
#define SRC_INCLUDE "src/include"
#define LIB_NAME "libraymaker"
#define EXEC_NAME "main"

// ---------------- USER DEFINE ENDS HERE ------------------ //

#include "build.h"

void handleLib();
void handleMain();
void handleAll();
void handleTest();

int main()
{
	INFO("-------------------------------");
	INFO("\tSTARTING BUILD\t");
	INFO("-------------------------------");

	handleAll();
	handleTest();

	INFO("-------------------------------");
	INFO("\tBUILD COMPLETED\t");
	INFO("-------------------------------");

	return 0;
}

void handleLib()
{
	int c;

	ACTION("Reading files from directory");
	char **buffer = safe(getFilesFromDirectory(LIB_PATH, &c));
	ACTION("Reading completed");

	int cC = c;

	while (c > 0)
	{
		c--; char *b = buffer[c]; size_t length = strlen(b);

		ACTION(writef("[completed :: %.0f%%] - Working on `%s`", (float)(100 - ((float)c / cC * 100)), b));

		if (b[length - 1] == 'c')
		{
			int s = system(writef("cc -c %s%s -I%s -o %s%s%s.o", LIB_PATH, b, LIB_PATH, BIN_PATH, LIB_PATH, b));

			if (s != 0)
			{
				ERROR("Failed to build.");
				exit(EXIT_FAILURE);
			}
		}
		else if (b[length - 1] == 'h')
		{
			int s = system(writef("cp %s%s %s%s", LIB_PATH, b, SRC_PATH, LIB_PATH));

			if (s != 0)
			{
				ERROR("Failed to build.");
				exit(EXIT_FAILURE);
			}
		}
	}

	ACTION("Writing static library");
	system(writef("ar r %s%s%s.a %s%s*.o", BIN_PATH, LIB_PATH, LIB_NAME, BIN_PATH, LIB_PATH));
}

void handleMain()
{
	ACTION("Working on executable.");
	int s = system(
			writef(
				"cc -I%s -I%s -I%s %s/*.c -L%s%s -L%sraylib/lib/ -l:libraymaker.a -l:libraylib.a -lm -o %s%s%s",
				SRC_INCLUDE,
				SRC_PATH,
				LIB_PATH,
				SRC_PATH,
				BIN_PATH,
				LIB_PATH,
				LIB_PATH,
				BIN_PATH,
				SRC_PATH,
				EXEC_NAME
			)
	);

	if (s != 0)
	{
		ERROR("Failed to build.");
		exit(EXIT_FAILURE);
	}
}

void handleAll()
{
	handleLib();
	handleMain();
}

void handleTest()
{
	ACTION("Working on test executable.");

	int s = system(
			writef(
				"cc -I%s %s/*.c -L%sraylib/lib/ -l:libraylib.a -lm -o %s%s",
				LIB_PATH,
				"test/",
				LIB_PATH,
				BIN_PATH,
				"test/test"
			)
	);

	if (s != 0)
	{
		ERROR("Failed to build.");
		exit(EXIT_FAILURE);
	}
}
