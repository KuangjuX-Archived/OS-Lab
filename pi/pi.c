#include <pthread.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <sys/time.h>
long long int n,t;
long double pi;
pthread_mutex_t lock;



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
    pi=0;
    scanf("%lld %lld",&n,&t);
    //time_t start_time = time(NULL);
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

    //time_t end_time = time(NULL);
    gettimeofday(&end_time,NULL);

    printf("pi: %.10LF\n",pi);
    printf("Required time is %d.%d s\n",(int)(end_time.tv_sec-start_time.tv_sec),(int)(end_time.tv_usec-start_time.tv_usec));

    return 0;
    
}