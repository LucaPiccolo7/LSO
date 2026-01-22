#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
pid_t getpid(void);
pid_t getppid(void);

uid_t getuid(void);
uid_t geteuid(void);

gid_t getgid(void);
gid_t getegid(void);
*/

int main(){

	pid_t pid, ppid;
	uid_t uid, euid;
	gid_t gid, egid;
	
	pid = getpid();
	ppid = getppid();
	
	uid = getuid();
	euid = geteuid();
	
	gid = getgid();
	egid = getegid();
	
	printf("\nPID: %d\n", pid);
	printf("\nPPID: %d\n", ppid);
	printf("\nUID: %d\n", uid);
	printf("\nEUID: %d\n", euid);
	printf("\nGID: %d\n", gid);
	printf("\nEGID: %d\n", egid);

	return 0;
}
