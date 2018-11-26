#include <errno.h>
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
http://man7.org/linux/man-pages/man2/inotify_add_watch.2.html

*/

#define EVENT_SIZE	(sizeof(struct inotify_event))
#define BUFFER_LEN	(1024 * (EVENT_SIZE + 16))


int notify(char *directory, int buffer_length){
	char buffer[buffer_length];
	int file_descriptor = inotify_init();
	
	if(file_descriptor < 0){
		perror("inotify_init");
	}
	int watch_descriptor = inotify_add_watch(file_descriptor,
					   	   ".", IN_MODIFY | IN_CREATE | IN_DELETE);// http://man7.org/linux/man-pages/man2/inotify_add_watch.2.html
															   // IN events are defined in inotify.h - https://code.woboq.org/qt5/include/sys/inotify.h.html
	int data_length = read(file_descriptor, buffer, buffer_length); // length of the data read for file or directory
	
	if(data_length < 0) {
		perror("read");	
	}
	
	int i = 0;
	while(i < data_length) {
		struct inotify_event *event = (struct inotify_event *) &buffer[i];
		if(event->len) {
			if(event->mask & IN_CREATE) {
				printf("%s was created.\n", event->name);	
			} else if(event->mask & IN_DELETE) {
				printf("%s was deleted.\n", event->name);	
			} else if(event->mask & IN_MODIFY) {
				printf("%s was modified.\n", event->name);	
			}
		}
		i += EVENT_SIZE + event->len;
	}
	
	(void) inotify_rm_watch(file_descriptor, watch_descriptor);
	(void) close(file_descriptor);
	
	return 0;
}


int main(int argc, char **argv){
	// Handle the arguments.
	if(argc < 2){
		printf("Not enough args. See usage: inotify directory_here");
		return -1;
	} else if(argc == 2){
		notify(argv[1], BUFFER_LEN);	
	} else{
		printf("Too many args. See usage: inotify directory_here");	
		return -1;
	}
	
}