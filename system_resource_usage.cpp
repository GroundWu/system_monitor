#include "system_resouce_usage.h"

sys_usage::sys_usage()
{
    cpu_usage = 0;
    mem_usage = 0;
    disk_usage = 0;
    net_usage = 0;

    old_cpu = new CPU_stat();
    new_cpu = new CPU_stat();
    old_cpu->read_CPU_file();
    new_cpu->read_CPU_file();

    old_mem = new MEM_info();
    new_mem = new MEM_info();
    old_mem->read_meminfo_file();
    new_mem->read_meminfo_file();

    old_disk = new disk_stat();
    new_disk = new disk_stat();
    old_disk->read_diskestats_file();
    new_disk->read_diskestats_file();

    old_net = new net_stat();
    new_net = new net_stat();
    old_net->read_net_stat_file();
    new_net->read_net_stat_file();

}

sys_usage::~sys_usage()
{
    delete old_cpu;
    delete new_cpu;
    delete old_mem;
    delete new_mem;
    delete old_net;
    delete new_net;
    delete old_disk;
    delete new_disk;
}

float sys_usage::get_cpu_usage()
{
    *old_cpu = *new_cpu;
    new_cpu->read_CPU_file();
    //compute the CPU Usage
    int total_old = old_cpu->cpu_user+old_cpu->cpu_nice+old_cpu->cpu_system+old_cpu->cpu_idle+old_cpu->cpu_iowait+old_cpu->cpu_irq+old_cpu->cpu_softirq;
    int total_new = new_cpu->cpu_user+new_cpu->cpu_nice+new_cpu->cpu_system+new_cpu->cpu_idle+new_cpu->cpu_iowait+new_cpu->cpu_irq+new_cpu->cpu_softirq;

    int t1_t2_total = total_new - total_old;

    int idle_old = old_cpu->cpu_idle;
    int idle_new = new_cpu->cpu_idle;
    int t1_t2_idle = idle_new - idle_old;
    printf("%d %d ",t1_t2_idle,t1_t2_total);
    cpu_usage = 1.0f - static_cast<float>(t1_t2_idle)/static_cast<float>(t1_t2_total);
    return cpu_usage;

}

float sys_usage::get_mem_usage()
{
    *old_mem = *new_mem;
    new_mem->read_meminfo_file();
    unsigned long mem_used = new_mem->mem_total-(new_mem->mem_free+new_mem->mem_buffer);
    mem_usage = static_cast<float>(mem_used)/static_cast<float>(new_mem->mem_total);
    return mem_usage;
}

float sys_usage::get_net_usage()
{
    *old_net = *new_net;
    new_net->read_net_stat_file();
    int old_total_bytes = old_net->in_bytes+old_net->out_bytes;
    int new_total_bytes = new_net->in_bytes+new_net->out_bytes;
    net_usage = static_cast<float>(new_total_bytes-old_total_bytes)/1024.0f; //KB
    return net_usage;
}

float sys_usage::get_disk_usage()
{
    *old_disk = *new_disk;
    new_disk->read_diskestats_file();
    float disk_speed = (static_cast<float>(new_disk->readsectors+new_disk->writesectors)-static_cast<float>(old_disk->readsectors+old_disk->writesectors))*512.0f/1024.0f;
    return disk_speed;
}
