#include <iostream>
#include <string>
#include <pthread.h>
#include <algorithm>
#include <string.h>
#include <chrono>

struct local_sum_arg
{
    int* array;
    int start;
    int end;
};

void* local_sum(void* arg)
{
    local_sum_arg* part = (local_sum_arg*) arg;
    int sum = 0;
    for(int i = part->start; i < part->end; ++i)
    {
        sum += part->array[i];
    }

    return new int(sum);
}

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        std::cerr << "Not enough arguments" << std::endl;
        return -1; 
    }

    int size = std::stoi(argv[1]);
    int threads_count = std::stoi(argv[2]);
    int* array = new int[size];
    for(int i = 0; i < size; ++i)
    {
        array[i] = 3 * i;
    }

    int regular_sum = 0, thread_sum = 0;
    
    auto start = std::chrono::system_clock::now();
    for(int i = 0; i < size; ++i)
    {
        regular_sum += array[i];
    }
    auto end = std::chrono::system_clock::now();
    auto regular_spent = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    start = std::chrono::system_clock::now();
    pthread_t* threads = new pthread_t[threads_count];
    local_sum_arg** array_of_args = new local_sum_arg*[threads_count];
    for(int i = 0; i < threads_count; ++i)
    {
        array_of_args[i] = new local_sum_arg;
        array_of_args[i]->array = array;
        array_of_args[i]->start = i * (size / threads_count);
        array_of_args[i]->end = std::min(array_of_args[i]->start + (size / threads_count), size);
        int result = pthread_create(&threads[i], NULL, local_sum, array_of_args[i]);
        if(result != 0)
        {
            std::cerr << strerror(result) << std::endl;
            exit(result);
        }
    }


    for(int i = 0; i < threads_count; ++i)
    {
        void* return_value;
        int result = pthread_join(threads[i], &return_value);
        if(result != 0)
        {
       	    std::cerr << strerror(result) << std::endl;
            exit(result);
        }
        int* local_sum_result = (int*)return_value;
        thread_sum += *local_sum_result;
        delete local_sum_result;
        delete array_of_args[i];
    }
    end = std::chrono::system_clock::now();
    auto thread_spent = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    delete[] array_of_args;
    delete[] array;

    std::cout << "Time spent without threads: "<< regular_spent.count() / 1000.0 << std::endl;
    std::cout << "Time spent with " << threads_count << " threads: " << thread_spent.count() / 1000.0 <<std::endl;
    
    return 0;
}
