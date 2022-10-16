// 78. В одномерном массиве чисел найти индекс максимального и индекс минимального элемента.

#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct thread_data {
   int *data;
   int n;
   int result;
};

typedef struct thread_data thread_data;

void *maxElementIndex(void *arg)
{
    thread_data *tdata = (thread_data *)arg;

    int maxElementValue = INT32_MIN;
    int maxElementIndex = 0;

    for (int i = 0; i < tdata->n; i++)
    {
        if (tdata->data[i] > maxElementValue)
        {
            maxElementValue = tdata->data[i];
            maxElementIndex = i;
        }
    }

    tdata->result = maxElementIndex;

    pthread_exit(NULL);
}

void *minElementIndex(void *arg)
{
    thread_data *tdata = (thread_data *)arg;

    int minElementValue = INT32_MAX;
    int minElementIndex = 0;

    for (int i = 0; i < tdata->n; i++)
    {
        if (tdata->data[i] < minElementValue)
        {
            minElementValue = tdata->data[i];
            minElementIndex = i;
        }
    }

    tdata->result = minElementIndex;

    pthread_exit(NULL);
}

int main()
{
    pthread_t thread_1_id, thread_2_id;
    thread_data tdata_max, tdata_min;
    int N = 0;
    
    printf("Enter number elements:");
    int res = scanf("%d", &N);

    int *data = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        int e = 0;
        int res = scanf("%d", &e);
        data[i] = e;
    }

    tdata_max.data = data;
    tdata_max.n = N;
    tdata_min.data = data;
    tdata_min.n = N;
    
    pthread_create(&thread_1_id, NULL, maxElementIndex, (void *)&tdata_max);
    pthread_create(&thread_2_id, NULL, minElementIndex, (void *)&tdata_min);
    
    pthread_join(thread_1_id, NULL);
    pthread_join(thread_2_id, NULL);
    
    printf("Maximum element index: %d\n", tdata_max.result);
    printf("Minimum element index: %d\n", tdata_min.result);

    free(data);
    
    return 0;
}