#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main() {
 

    // Get the hostname
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("gethostname");
        return 1;
    }

    printf("Hostname for user : %s\n" , hostname);

    return 0;
}