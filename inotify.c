#include <stdio.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>

/*
We will be using the inotify function in Linux to monitor changes in a directory, and store them in a log.
Changes we will monitor: file creation, deletions, and, renamkes under the directory named in its command-line argument.
Program will run in the background and monitor/write events to log.

http://man7.org/linux/man-pages/man7/inotify.7.html
https://stackoverflow.com/questions/13351172/inotify-file-in-c
*/

#DEFINE EVENT_SIZE	(sizeof(struct inotify_event))
#DEFINE BUFFER_LEN	(1024 * (EVENT_SIZE + 16))


int inotify(char *directory){
	
}

int main(){int argc, char **argv){
	// Handle the arguments.
	if(argc < 2){
		printf("Not enough args. See usage: inotify directory_here");
		exit()
	} else if(argc == 2){
		inotify(argv[1]);	
	} else{
		print("Too many args. See usage: inotify directory_here");	
	}
	
}