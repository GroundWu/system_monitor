#ifndef MEMINFO_H
#define MEMINFO_H

#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<climits>

#define MEM_INFFO_FILE "/proc/meminfo"

class MEM_info
{
public:
    unsigned long mem_total;
    unsigned long mem_avail;
    unsigned long mem_free;
    unsigned long mem_buffer;
    unsigned long mem_cache;
    unsigned long mem_swaptotal;
    unsigned long mem_swapfree;

    MEM_info();
    ~MEM_info();
    MEM_info& operator=(const MEM_info &m);
    int read_meminfo_file();
    void print();
};

#endif // MEMINFO_H
