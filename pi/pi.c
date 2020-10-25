#include <pthread.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
long long int n,t;
long double pi;
pthread_mutex_t lock;
const long double TimeCovert = 1e6;

char* read(){
    char* status =(char*)(malloc)(sizeof(char)*100);
    int i;
    i=0;
    char c;
    c=getchar();
    while(c=='\n'){
        c=getchar();
        continue;
    }
    while(c!='\n' && c!=EOF){
        status[i]=c;
        i++;
        c=getchar();
    }
    status[i] = '\0';
    return status;
}

void *thread_compute(void* ID){
    int id = (int) ID;

    int length;
    length = n/t;
    int start,end;
    start = id*length;
    end = (id+1)*length;
    pthread_mutex_lock(&lock);
    
    int i;
    for(i=start+1;i<=end;i++){
        pi += (4/((1+((i+0.5)/n)*((i+0.5)/n))))*(1.0/n);
    }

    pthread_mutex_unlock(&lock);
}

int main(){
    char* status;
    printf("Please enter 'quit' if you want exit else programme "
    "continue: \n");
    status = read();

    while(strcmp(status,"quit")!=0){
    pi=0;
    printf("Please enter N and T: \n");
    scanf("%lld %lld",&n,&t);
    struct timeval start_time,end_time;
    gettimeofday(&start_time,NULL);
    pthread_t* threads;
    threads = (pthread_t*)malloc(sizeof(pthread_t)*t);
    int i;
    for(i=0;i<t;i++){
        pthread_create(&threads[i],NULL,thread_compute,(void*)i);
    }

    for(i=0;i<t;i++){
        pthread_join(threads[i],NULL);
    }

    gettimeofday(&end_time,NULL);

    printf("pi: %.10LF\n",pi);
    long long int start,end;
    start = start_time.tv_sec*TimeCovert+start_time.tv_usec;
    end = end_time.tv_sec*TimeCovert+end_time.tv_usec;
    long double span_time;
    span_time = (end-start)/(TimeCovert);

    printf("Required time is %.6LFs\n",span_time);

    //judge when end of output

    printf("Please enter 'quit' if you want exit else programme "
    "continue: \n");
    status = read();
    }

    return 0;
    
}