#ifndef DISK_STATS_H
#define DISK_STATS_H
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<climits>
#define DISK_STAT_FILE "/proc/diskstats"
//Maybe there are disks more than one. Specify the device name and can new other "disk_stat" class represented other disk devices
#define DEVICE_NAME "sda"
class disk_stat
{
public:
    int readios;
    int readsectors;
    int writeios;
    int writesectors;

    disk_stat();
    ~disk_stat();
    disk_stat& operator=(const disk_stat&d);
    int read_diskestats_file();
    void print();
};

#endif // DISK_STATS_H
