#define IMPLEMENT_BUILD_C

#include "build.h"

// #define CFLAGS  "-O3", "-Wall", "-Werror", "-Wpedantic", "-Wshadow", "-ggdb"
#define CFLAGS  "-O3", "-Wall", "-ggdb"

bool exec_do_need_to_compile = false;

void build_lib();
void build_exec();
void build_test();

int main(int argc, char *argv[])
{
	build_lib();
	build_exec();
	build_test();

	if (!state_of_rebuilds)
		INFO("No build requires. Everythings seems to be updated.");

	return 0;
}

void build_lib()
{
	int number_of_files;
	char **collection_of_files = safe(get_files_from_directory("lib/", &number_of_files));

	if (needs_recompilation("bin/lib/libraymaker.a", (const char**)collection_of_files, number_of_files))
	{
		INFO("Building lib.");
		exec_do_need_to_compile = true;

		for (int i = 0; i < number_of_files; ++i)
		{
			char *file = collection_of_files[i];
			size_t len = strlen(file);

			ACTION("COMPLETED :: %.1f => Working on `%s`", (float)(((float)(i + 1) / number_of_files * 100)), file);

			const char *buffer[] = { file };
			switch (file[len - 1]) {
				case 'h':
					{
						if (needs_recompilation(writef("src/%s", file), buffer, 1))
							CMD("cp", file, "src/lib/");

						break;
					}
				case 'c':
					{
						if (needs_recompilation(writef("bin/%s.o", file), buffer, 1))
							CMD("cc", CFLAGS, "-c", file, "-I./lib/", "-o", writef("./bin/%s.o", file));

						break;
					}
			};
		}

		ACTION("Creating `libraymaker.a`.");
		CMD("ar rc ./bin/lib/libraymaker.a ./bin/lib/*.o");
	}
}

void build_exec()
{
	int file_count;
	char **files_of_source = get_files_from_directory("./src/", &file_count);

	if (needs_recompilation("./bin/src/main", (const char**)files_of_source, file_count) || exec_do_need_to_compile)
	{
		INFO("Building exec.");
		CMD(
				"cc", 
				"src/*.c",
				CFLAGS, 
				"-Isrc/", 
				"-Isrc/lib/", 
				"-Isrc/include/", 
				"-Ilib/",
				"-Lbin/lib",
				"-Llib/raylib/lib",
				"-l:libraymaker.a",
				"-l:libraylib.a",
				"-lm",
				"-o",
				"bin/src/main"
		 );
	}
}

void build_test()
{
	int file_count;
	char **files_of_source = get_files_from_directory("test/", &file_count);

	if (needs_recompilation("bin/test/test", (const char**)files_of_source, file_count))
	{
		INFO("Building test.");
		CMD("cc", "test/*.c", "-Itest/", "-Llib/raylib/lib", "-l:libraylib.a", "-lm", "-o", "bin/test/test");
	}
}
