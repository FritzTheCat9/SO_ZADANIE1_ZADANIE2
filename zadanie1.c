// Kompilacja: gcc zadanie1.c -o zadanie1 -pthread
// Wykonanie: ./zadanie1

// Kompilacja: gcc zadanie1.c -o zadanie1 -pthread -O3
// Wykonanie: ./zadanie1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// zmienna globalna - licznik
long long licznik = 0;

// funkcja wykonywana w wątku1 - wypisuje wartość zmiennej globalnej licznik
void* funkcja_watek1(void* arg)
{
    while(1)
    {
        printf("Watek1 - Licznik: %lld\n", licznik);
    }

    // skończenie działania wątku
    pthread_exit(0);
}

// funkcja wykonywana w wątku2 - inkrementuje zmienną globalną licznik
void* funkcja_watek2(void* arg)
{
    while(1)
    {
        //printf("Watek2 - Inkrementacja licznika");
        licznik++;
    }

    // skończenie działania wątku
    pthread_exit(0);
}

int main()
{
    // N - liczba wątków
    int N = 2;

    // tablica ID wątków
    pthread_t watek[N];

    // ustawienie domyślnych atrybutów wątków
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // utworzenie wątkow
    pthread_create(&watek[0], &attr, funkcja_watek1, NULL);
    pthread_create(&watek[1], &attr, funkcja_watek2, NULL);

    // czekanie na zakończenie wszystkich wątków
    for(int i = 0; i < N; i++)
    {
        pthread_join(watek[i], NULL);
    }

    return 0;
}