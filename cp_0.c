#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//	int open(const char *pathname, int flags);
//	int open(const char *pathname, int flags, mode_t mode);

//	int creat(const char *pathname, mode_t mode);	//	open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode)
	
#define CREAT_MODE 0644
#define BUF_SIZE 4096

//	cp argv[1] argv[2]
int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("cp sourceFile targetFile\n");
		exit(1);	
	}
	
	int sourceFd = open(argv[1], O_RDONLY);
	if (sourceFd == -1)
	{
		printf("open %s failed\n", argv[1]);	
	}
	
	int targetFd = creat(argv[2], CREAT_MODE);
	if (targetFd == -1)
	{
		printf("create(open) %s failed\n", argv[2]);	
	}
	
	char buf[BUF_SIZE];
	int size = 0;
	while (size = read(sourceFd, buf, BUF_SIZE))
	{
		printf("size = %d\n", size);
		
		if (write(targetFd, buf, size) < size)
		{
			printf("write error\n");
			exit(1);	
		}	
	}
	
	close(sourceFd);
	close(targetFd);
	
	return 0;	
}
