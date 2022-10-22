// 78. В одномерном массиве чисел найти индекс максимального и индекс минимального элемента.

// Подключаем заголовки библиотек для дальнейшего использования их функций
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// Определяем структуру данных для взаимодействия с потоками
struct thread_data {
   int *data;
   int n;
   int result;
};

typedef struct thread_data thread_data;

// Функция потока по поиску индекса максимального элемента
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

// Функция потока по поиску индекса минимального элемента
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

// Главная функция - корневой поток
int main()
{
    pthread_t thread_1_id, thread_2_id;
    thread_data tdata_max, tdata_min;
    int N = 0;
    
    // Просим пользователя ввести количество элементов в массиве
    printf("Enter number elements:");
    int res = scanf("%d", &N);

    // Запрашиваем память под массив из N целых чисел
    int *data = (int *)malloc(N * sizeof(int));

    // Заполняем массив чисел с клавиатуры
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
    
    // Создаем два потока, каждый для своей задачи
    pthread_create(&thread_1_id, NULL, maxElementIndex, (void *)&tdata_max);
    pthread_create(&thread_2_id, NULL, minElementIndex, (void *)&tdata_min);
    
    // Ожидаем окончания работы потоков
    pthread_join(thread_1_id, NULL);
    pthread_join(thread_2_id, NULL);
    
    // Выводим результаты поиска
    printf("Maximum element index: %d\n", tdata_max.result);
    printf("Minimum element index: %d\n", tdata_min.result);

    // Освобождаем память, занятую массивом целых чисел
    free(data);
    
    return 0;
}
