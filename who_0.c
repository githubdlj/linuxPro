#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utmp.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//int open(const char *pathname, int flags);
//int open(const char *pathname, int flags, mode_t mode);

//ssize_t read(int fd, void *buf, size_t count);

//	struct utmp
//               short   ut_type;              /* Type of record */
//               pid_t   ut_pid;               /* PID of login process */
//               char    ut_line[UT_LINESIZE]; /* Device name of tty - "/dev/" *//               char    ut_id[4];             /* Terminal name suffix,
//                                                or inittab(5) ID */
//               char    ut_user[UT_NAMESIZE]; /* Username */
//               char    ut_host[UT_HOSTSIZE]; 

int main()
{
	int utmpFd = open("/var/run/utmp", O_RDONLY);
	if (utmpFd == -1)
	{
		perror("open failed");
		exit(1);
	}
	
	struct utmp record;	
	int recLen = sizeof(record);

	while (read(utmpFd, &record, recLen) == recLen)
	{
		if (record.ut_type == USER_PROCESS)
		{
			printf("%d\t%s\t%s\t%s\t%s\n", 
				record.ut_pid, record.ut_line, record.ut_id, 
				record.ut_user, record.ut_host);
		}
	}
	
	if (close(utmpFd) == -1)
	{
		perror("close failed\n");
	}

	return 0;
}

