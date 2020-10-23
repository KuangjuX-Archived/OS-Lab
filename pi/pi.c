#include <pthread.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
long long int n,t;
long double pi;
pthread_mutex_t lock;
struct params{
    int n;
    int t;
} ;



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
    time_t start_time = time(NULL);
    pi=0;
    scanf("%lld %lld",&n,&t);
    pthread_t* threads;
    threads = (pthread_t*)malloc(sizeof(pthread_t)*t);
    int i;
    for(i=0;i<t;i++){
        pthread_create(&threads[i],NULL,thread_compute,(void*)i);
    }

    for(i=0;i<t;i++){
        pthread_join(threads[i],NULL);
    }

    time_t end_time = time(NULL);

    printf("pi: %.10LF\n",pi);
    printf("Required time is %d s\n",(int)(end_time-start_time));

    return 0;
    
}