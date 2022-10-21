// Вычислить  f(x)dx на интервале [a, b], используя метод трапеций. 
// Производить вычисление с некоторым шагом, интервал разделить между несколькими потоками.
// Входные данные:
// - числа a и b, функция f(x) 
// - определяется с помощью программной функции.

#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_THREADS 10

// Определяем структуру данных для взаимодействия с потоками
struct thread_data {
   double from;
   double to;
   long int steps;
   double result;
};

typedef struct thread_data thread_data;

void *trapIntegrateThread(void *arg);
double f(double x);
double integrate(double from, double to, long int steps);

// Главная функция - корневой поток
int main()
{
    pthread_t threads[NUM_THREADS];
    thread_data tdata[NUM_THREADS];
        
    double a, b;
    long int N;

    // Просим пользователя ввести нижнюю границу интегрирования
    printf("Enter lower bound (a):");
    int res = scanf("%lf", &a);

    // Просим пользователя ввести верхнюю границу интегрирования
    printf("Enter upper bound (b):");
    res = scanf("%lf", &b);

    // Просим пользователя ввести количество интервалов интегриования
    printf("Enter steps count (N):");
    res = scanf("%ld", &N);

    // Выводим значение интеграла полученное последовательным алгоритмом
    printf("Serial test: [%.3lf, %.3lf] -> %.3lf\n", a, b, integrate(a, b, N*NUM_THREADS));  

    // Создаем потоки каждый для своей части интеграла
    double distance = (b - a) / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        tdata[i].from = a + i * distance;
        tdata[i].to = a + (i+1) * distance;
        tdata[i].steps = N;

        pthread_create(&threads[i], 
                       NULL, 
                       trapIntegrateThread, 
                       (void *)&tdata[i]
        );
    }

    // Ожидаем окончания работы потоков
    double integralValue = 0;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);

        // Суммируем общее значение интеграла
        integralValue += tdata[i].result;
    }
    
    // Выводим значение интеграла параллельным алгоритмом
    printf("Parallel integral value: %.3lf\n", integralValue);

    return 0;
}

// Функция потока по вычислению частей интеграла
void *trapIntegrateThread(void *arg)
{
    struct thread_data *tdata = (thread_data *)arg;

    tdata->result = integrate(
                                tdata->from,
                                tdata->to, 
                                tdata->steps
                    );

    pthread_exit(NULL);
}

// Интегрируемая функция  
double f(double x)
{
    return x * x;
}

// Function to evaluate the value of integral with trapezoidal rule
double integrate(double from, double to, long int steps)
{
    // Grid spacing
    double h = (to - from) / steps;

    // Computing sum of first and last terms
    // in above formula
    double s = f(from) + f(to);

    // Adding middle terms in above formula
    for (long int i = 1; i < steps; i++)
    {
        s += 2 * f(from + i*h);
    }

    // h/2 indicates (b-a)/2n. Multiplying h/2
    // with s.
    return (h/2)*s;
}