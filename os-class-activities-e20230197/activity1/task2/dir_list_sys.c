/* dir_list_sys.c */
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>    // only for snprintf to format numbers into strings

int main() {
    char buffer[512];

    // 1. Open current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        const char *err = "Error opening directory\n";
        write(2, err, strlen(err));
        return 1;
    }

    struct dirent *entry;
    struct stat fileStat;

    // 2. Print header using write()
    snprintf(buffer, sizeof(buffer), "%-30s %10s\n", "Filename", "Size (bytes)");
    write(1, buffer, strlen(buffer));
    snprintf(buffer, sizeof(buffer), "%-30s %10s\n",
             "------------------------------", "----------");
    write(1, buffer, strlen(buffer));

    // 3-5. Loop through entries, get size with stat(), print with write()
    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {
            snprintf(buffer, sizeof(buffer), "%-30s %10ld\n",
                     entry->d_name, (long)fileStat.st_size);
            write(1, buffer, strlen(buffer));
        }
    }

    // 6. Close directory
    closedir(dir);
    return 0;
}
