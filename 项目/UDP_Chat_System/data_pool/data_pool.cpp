#include "data_pool.h"

data_pool::data_pool(const int _size)
    :pool_size(_size)
    ,pool(_size)
{
    sem_init(&space_sem, 0, pool_size);
    sem_init(&data_sem, 0, 0);

    space_step = 0;
    data_step = 0;
}

data_pool::~data_pool()
{
    sem_destroy(&space_sem);
    sem_destroy(&data_sem);
}

int data_pool::get_msg(std::string& msg)
{
    sem_wait(&data_sem);
    msg = pool[data_step];
    data_step = (++data_step)%pool_size;
    sem_post(&space_sem);
}

int data_pool::put_msg(const std::string& msg)
{
    sem_wait(&space_sem);
    pool[space_step] = msg;
    space_step = (++space_step)%pool_size;
    sem_post(&data_sem);
}

#ifdef _DATAPOOL_MAIN_
int main()
{
    data_pool pool;
    pool.put_msg("hello");
    std::string out;
    pool.get_msg(out);
    std::cout<<out<<std::endl;

    return 0;
}
#endif





