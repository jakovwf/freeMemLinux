#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

//PROGRAM KOJI IZBACUJE KOLIKO JE TACNO SLOBODNE MEMROIJE NA LINUXU
//POTREBNO JE DA SE PROGRAM KOMPAJLIRA - gcc main.c -o <ime-fajla>
//KADA SE KOMPAJLIRA POTREBNO JE DA SE NAPISE SLEDECA KOMANDA
// sudo mv <ime-fajla> /usr/local/bin/ 
//POSLE TOGA OTVORI TERMINAL I UKUCAJ <ime-programa> 



int main() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        // CHILD
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execl("/bin/df", "df", "-B1", NULL);
        perror("execl");
        exit(1);
    }

    // PARENT
    close(fd[1]);

    FILE *stream = fdopen(fd[0], "r");
    char line[512];
    unsigned long long total_free = 0;

    // preskačemo header
    fgets(line, sizeof(line), stream);

    while (fgets(line, sizeof(line), stream)) {
        char fs[128], mount[128];
        unsigned long long size, used, avail;
        int usep;

        sscanf(line, "%s %llu %llu %llu %d%% %s",
               fs, &size, &used, &avail, &usep, mount);

        total_free += avail;
    }

    fclose(stream);
    wait(NULL);

    // ispis u GB
    printf("Ukupno slobodno: %.2f GB\n",
           total_free / (1024.0 * 1024 * 1024));

    return 0;
}
