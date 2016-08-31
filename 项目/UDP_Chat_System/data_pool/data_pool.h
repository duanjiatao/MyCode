#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <semaphore.h>

using namespace std;

#define POOL_SIZE 512

class data_pool
{
    public:
        data_pool(const int _size = POOL_SIZE);
        ~data_pool();

        int get_msg(std::string& msg);
        int put_msg(const std::string& msg);

    private:
        const int pool_size;
        std::vector<std::string> pool;

        sem_t space_sem;
        sem_t data_sem;

        int space_step;
        int data_step;

};
