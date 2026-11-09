/* file_creator_sys.c */
#include <fcntl.h>    // open(), O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h>   // write(), close()
#include <string.h>   // strlen()

int main() {
    const char *text = "Hello from Operating Systems class!\n";
    const char *msg  = "File created successfully!\n";

    // 1. Open/create "output.txt"
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        const char *err = "Error opening file\n";
        write(2, err, strlen(err));
        return 1;
    }

    // 2. Write text into the file
    write(fd, text, strlen(text));

    // 3. Close the file
    close(fd);

    // 4. Print confirmation to terminal (fd 1 = stdout)
    write(1, msg, strlen(msg));
    return 0;
}
