#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

int
main(int argc, char *argv[])
{
	(void)argv;

	if (argc != 3) {
		fprintf(stderr, "usage: bbcp <src> <dest>\n");
		return EXIT_FAILURE;
	}

	int fd1, fd2;

	if ((fd1 = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "open failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	
	fd2 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);

	if (fd2 < 0) {
		if (errno == EISDIR) {
			DIR *dirp;
			if ((dirp = opendir(argv[2])) == NULL) {
				fprintf(stderr, "opendir failed: %s\n", strerror(errno));
				return EXIT_FAILURE;
			}
			char *path = strcat(argv[2], argv[1]);
			if ((fd2 = open(path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0) {
				fprintf(stderr, "open failed: %s\n", strerror(errno));
				return EXIT_FAILURE;
			}

		} else {
			fprintf(stderr, "open failed: %s\n", strerror(errno));
			return EXIT_FAILURE;
		}
	}

	char buf[BUFSIZ];
	ssize_t bytes;

	while ((bytes = read(fd1, buf, BUFSIZ)) > 0) {
		if (write(fd2, buf, bytes) != bytes) {
			fprintf(stderr, "write failed: %s\n", strerror(errno));
			return EXIT_FAILURE;
		}
	}

	if (bytes < 0) {
		fprintf(stderr, "read failed: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	(void)close(fd1);
	(void)close(fd2);

	return EXIT_SUCCESS;
}
