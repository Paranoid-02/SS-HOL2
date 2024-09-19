#include<stdio.h>
#include<sys/resource.h>
#include<unistd.h>

int main(){
    struct rlimit rlim;

    //iterate thru all resource types
    for(int i =0;i<RLIM_NLIMITS;i++){
        if(getrlimit(i,&rlim) == -1){
            perror("getlimit");
            return 1;
        }

        printf("Resource: %d\n",getrlimit_name(i));
        printf("Soft limit: %llu\n",rlim.rlim_cur);
        printf("Hard limit: %llu\n\n",rlim.rlim_max);
    }
    return 0;
}

const char* getrlimit_name(int resource){
    switch(resource){
        case RLIMIT_CPU: return "RLIMIT_CPU";
        case RLIMIT_FSIZE: return "RLIMIT_FSIZE";
        case RLIMIT_DATA: return "RLIMIT_DATA";
        case RLIMIT_STACK: return "RLIMIT_STACK";
        case RLIMIT_CORE: return "RLIMIT_CORE";
        case RLIMIT_RSS: return "RLIMIT_RSS";
        case RLIMIT_NPROC: return "RLIMIT_NPROC";
        case RLIMIT_NOFILE: return "RLIMIT_NOFILE";
        case RLIMIT_MEMLOCK: return "RLIMIT_MEMLOCK";
        // case RLIMIT_AS: return "RLIMIT_AS";
        // case RLIMIT_LOCKS: return "RLIMIT_LOCKS";
        // case RLIMIT_SIGPENDING: return "RLIMIT_SIGPENDING";
        // case RLIMIT_MSGQUEUE: return "RLIMIT_MSGQUEUE";
        // case RLIMIT_NICE: return "RLIMIT_NICE";
        // case RLIMIT_RTPRIO: return "RLIMIT_RTPRIO";
        // case RLIMIT_RTTIME: return "RLIMIT_RTTIME";
        default: return "Unknown";
    }
}