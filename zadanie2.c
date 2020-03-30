/*
Politechnika Białostocka,
Informatyka, PS2,
Grupa: Bartłomiej Umiński, Dominik Borowski, Michał Wysocki
*/

// Kompilacja: gcc zadanie2.c -o zadanie2 -pthread
// Wykonanie: ./zadanie2

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// struktura do przechowywania informacji z wątków
struct funkcja_watek_struct
{
    int nr_watku;
    long long liczba_iteracji;
};

// funkcja wykonywana w wątkach
void* funkcja_watek(void* arg)
{
    struct funkcja_watek_struct* arg_struct = (struct funkcja_watek_struct*) arg;
    arg_struct->liczba_iteracji = rand()%10000;
    
    // PONIŻEJ TEST DLA MNIEJSZYCH  DANYCH
    /*arg_struct->liczba_iteracji = rand()%3+1;
    printf("LICZBA ITERACJI WATKU %d = %lld\n", arg_struct->nr_watku, 
    arg_struct->liczba_iteracji);*/

    for(long long k = 0; k < arg_struct->liczba_iteracji; k++)
    {
        printf("Watek %d iteracja %lld\n", arg_struct->nr_watku, k);
    }

    // skończenie działania wątku
    pthread_exit(0);
}

int main()
{
    // N - liczba wątków
    int N = 10;

    // tworzenie struktur na dane z wątków
    struct funkcja_watek_struct args[N];

    // tablica ID wątków
    pthread_t watek[N];

    // ustawienie ziarna do generowania liczb losowych
    srand(time(NULL));

    // utworzenie wątkow
    for(int i = 0; i < N; i++)
    {
        args[i].nr_watku = i;

        // ustawienie domyślnych atrybutów wątków
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        pthread_create(&watek[i], &attr, funkcja_watek, &args[i]);
    }

    long long lacznie_iteracji = 0;

    // czekanie na zakończenie wszystkich wątków
    for(int i = 0; i < N; i++)
    {
        pthread_join(watek[i], NULL);
        lacznie_iteracji += args[i].liczba_iteracji;
    }

    // wypisanie liczby iteracji w wątkach
    for(int i = 0; i < N; i++)
    {
        printf("Liczba iteracji w wątku %d: %lld\n", args[i].nr_watku
        , args[i].liczba_iteracji);
    }

    // wypisane łącznej liczby iteracji we wszystkich wątkach
    printf("Laczna liczba iteracji: %lld\n", lacznie_iteracji);

    return 0;
}