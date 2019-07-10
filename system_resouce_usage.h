#ifndef SYSTEM_RESOUCE_USAGE_H
#define SYSTEM_RESOUCE_USAGE_H
#include "CPU_stat.h"
#include "MEM_info.h"
#include "disk_stats.h"
#include "net_stat.h"
class sys_usage
{
public:
    float cpu_usage;
    float mem_usage;
    float disk_usage;
    float net_usage;
    CPU_stat *old_cpu, *new_cpu;
    MEM_info *old_mem, *new_mem;
    disk_stat *old_disk, *new_disk;
    net_stat *old_net, *new_net;

    sys_usage();
    ~sys_usage();
    float get_cpu_usage();
    float get_mem_usage();
    float get_disk_usage();
    float get_net_usage();
    void print();
};

#endif // SYSTEM_RESOUCE_USAGE_H
