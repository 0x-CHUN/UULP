#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <utmp.h>

#define SHOWHOST

void show_info(struct utmp *utbufp);

int main(int argc, char const *argv[]) {
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);
    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE);
        _exit(1);
    }
    while (read(utmpfd, &current_record, reclen) == reclen) {
        show_info(&current_record);
    }
    close(utmpfd);
    return 0;
}

void show_info(struct utmp *u) {
    printf("%-8.8s", u->ut_user); // Username
    printf(" ");
    printf("%-8.8s", u->ut_line); // Device name of tty
    printf(" ");
    printf("%-8d", u->ut_tv.tv_sec); // ut_time
    printf(" ");
#ifdef SHOWHOST
    printf("%-8s", u->ut_host); // host name for remote login
    printf(" ");
#endif
    printf("\n");
}