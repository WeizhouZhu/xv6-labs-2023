#include "kernel/types.h"
#include "user/user.h"


void helper(int pipe_read, int pipe_wirte){
    char check_list[34];
    read(pipe_read, check_list, 34);

    int p = -1;
    for(int i=0; i<34; i++){
        if(check_list[i] == '0'){
            fprintf(0, "prime %d\n", i+2);
            p = i + 2;
            check_list[i] = '1';
            break;
        }
    }
    if(p == -1){
        exit(0);
    }
    
    for(int i=p-2; i<34; i+=p){
        check_list[i] = '1';
    }

    int pid = fork();

    if(pid > 0){
        write(pipe_wirte, check_list, 34);
        wait(0);
    }
    else{
        helper(pipe_read, pipe_wirte);
    }
}

int
main(int argc, char *argv[])
{
    char total_num[34];
    for(int i=0; i<34; i++){
        total_num[i] = '0';
    }

    int fd[2];
    pipe(fd);

    int pid = fork();

    if(pid > 0){
        write(fd[1], total_num, 34);
        wait(0);
    }
    else{
        helper(fd[0], fd[1]);
        wait(0);
    }

    exit(0);
}
