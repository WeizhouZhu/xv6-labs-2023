#include "kernel/types.h"
#include "user/user.h"

void
int2str(char *buf, int val)
{   
    int i = 0;
    while(val != 0){
        buf[i] = '0' + val % 10;
        val /= 10;
        i += 1;
    }
    buf[i] = '\0';

    int n = (i >> 1);
    for(i=0; i<n; i++){
        char tem = buf[i];
        buf[i] = buf[n-i];
        buf[n-i] = tem;
    }
}

int
main(int argc, char *argv[])
{
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);

    char *buf = "a";
    
    if(fork() == 0){
        read(p1[0], buf, 1);

        int child_pid = getpid();
        char pid_num[1000];
        int2str(pid_num, child_pid);
        fprintf(0, pid_num);
        fprintf(0, ": received ping\n");

        write(p2[1],"a",1);
    }
    else{
        write(p1[1],"a",1);
        read(p2[0], buf, 1);

        int fa_pid = getpid();
        char pid_num[1000];
        int2str(pid_num, fa_pid);
        fprintf(0, pid_num);
        fprintf(0, ": received pong\n");
    }
    exit(0);
}
