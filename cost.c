#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

void timeval_subtract (struct timeval *result, struct timeval *left, struct timeval *right) {
    if (left->tv_usec < right->tv_usec) {
        int nsec = (right->tv_usec - left->tv_usec) / 1000000 + 1;
        right->tv_usec -= 1000000 * nsec;
        right->tv_sec += nsec;
    }
    if (left->tv_usec - right->tv_usec > 1000000) {
        int nsec = (left->tv_usec - right->tv_usec) / 1000000;
        right->tv_usec += 1000000 * nsec;
        right->tv_sec -= nsec;
    }

    result->tv_sec = left->tv_sec - right->tv_sec;
    result->tv_usec = left->tv_usec - right->tv_usec;
}

int main() {
    struct  timeval before;
    struct timeval after;
    struct timeval result;

    // getpid()
    gettimeofday(&before,NULL);
    getpid();
    gettimeofday(&after,NULL);
    timeval_subtract(&result, &after, &before);
    printf("Time of the getpid: %ld.%06ld seconds\n", result.tv_sec, result.tv_usec); 

    // mkdir()
    rmdir("emre");
    gettimeofday(&before,NULL);
    mkdir("emre", 0777);
    gettimeofday(&after,NULL);
    timeval_subtract(&result, &after, &before);
    printf("Time of the mkdir: %ld.%06ld seconds\n", result.tv_sec, result.tv_usec); 
    rmdir("emre");

    int fd;

    // open()
    gettimeofday(&before,NULL);
    fd = open("emre.txt", O_RDONLY, O_CREAT);
    gettimeofday(&after,NULL);
    timeval_subtract(&result, &after, &before);
    printf("Time of the open: %ld.%06ld seconds\n", result.tv_sec, result.tv_usec); 
    close(fd);

    int bufferSize;

    // write() 100000 byte
    bufferSize = 100000;
    char buffer4[bufferSize];
    for (int i = 0; i < bufferSize; i++){
        buffer4[i] = rand()%256;
    }
    fd = open("100000byte", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    gettimeofday(&before,NULL);
    write(fd, buffer4, bufferSize);
    gettimeofday(&after,NULL);
    timeval_subtract(&result, &after, &before);
    printf("Time of the write 100000 byte: %ld.%06ld seconds\n", result.tv_sec, result.tv_usec); 
    close(fd);

    // write() 10000 byte
    bufferSize = 10000;
    char buffer3[bufferSize];
    for (int i = 0; i < bufferSize; i++){
        buffer3[i] = rand()%256;
    }
    fd = open("10000byte", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    gettimeofday(&before,NULL);
    write(fd, buffer3, bufferSize);
    gettimeofday(&after,NULL);
    timeval_subtract(&result, &after, &before);
    printf("Time of the write 10000 byte: %ld.%06ld seconds\n", result.tv_sec, result.tv_usec); 
    close(fd);

    // write() 1000 byte
    bufferSize = 1000;
    char buffer2[bufferSize];
    for (int i = 0; i < bufferSize; i++){
        buffer2[i] = rand()%256;
    }
    fd = open("1000byte", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    gettimeofday(&before,NULL);
    write(fd, buffer2, bufferSize);
    gettimeofday(&after,NULL);
    timeval_subtract(&result, &after, &before);
    printf("Time of the write 1000 byte: %ld.%06ld seconds\n", result.tv_sec, result.tv_usec); 
    close(fd);

    // write() 100 byte
    bufferSize = 100;
    char buffer1[bufferSize];
    for (int i = 0; i < bufferSize; i++){
        buffer1[i] = rand()%256;
    }
    fd = open("100byte", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    gettimeofday(&before,NULL);
    write(fd, buffer1, bufferSize);
    gettimeofday(&after,NULL);
    timeval_subtract(&result, &after, &before);
    printf("Time of the write 100 byte: %ld.%06ld seconds\n", result.tv_sec, result.tv_usec); 
    close(fd);

    // read() 100000 byte
    bufferSize = 100000;
    char buffer8[bufferSize];
    fd = open("100000byte", O_RDONLY, 0);
    gettimeofday(&before,NULL);
    read(fd, &buffer8, bufferSize);
    gettimeofday(&after,NULL);
    timeval_subtract(&result, &after, &before);
    printf("Time of the read 100000 byte: %ld.%06ld seconds\n", result.tv_sec, result.tv_usec); 
    close(fd);
 
    // read() 10000 byte
    bufferSize = 10000;
    char buffer7[bufferSize];
    fd = open("10000byte", O_RDONLY, 0);
    gettimeofday(&before,NULL);
    read(fd, &buffer7, bufferSize);
    gettimeofday(&after,NULL);
    timeval_subtract(&result, &after, &before);
    printf("Time of the read 10000 byte: %ld.%06ld seconds\n", result.tv_sec, result.tv_usec); 
    close(fd);

    // read() 1000 byte
    bufferSize = 1000;
    char buffer6[bufferSize];
    fd = open("1000byte", O_RDONLY, 0);
    gettimeofday(&before,NULL);
    read(fd, &buffer6, bufferSize);
    gettimeofday(&after,NULL);
    timeval_subtract(&result, &after, &before);
    printf("Time of the read 1000 byte: %ld.%06ld seconds\n", result.tv_sec, result.tv_usec); 
    close(fd);

    // read() 100 byte
    bufferSize = 100;
    char buffer5[bufferSize];
    fd = open("100byte", O_RDONLY, 0);
    gettimeofday(&before,NULL);
    read(fd, &buffer5, bufferSize);
    gettimeofday(&after,NULL);
    timeval_subtract(&result, &after, &before);
    printf("Time of the read 100 byte: %ld.%06ld seconds\n", result.tv_sec, result.tv_usec); 
    close(fd);

    remove("100byte");
    remove("1000byte");
    remove("10000byte");
    remove("100000byte");

    return 0;   
}

