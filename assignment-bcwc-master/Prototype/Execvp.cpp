#include <unistd.h>

int main() {
	const char* argv[] = {"ls", "-a", nullptr};
	execvp("ls",(char* const*) argv);

	return 0;
}

