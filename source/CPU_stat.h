 #ifndef CPU_H
#define CPU_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <climits>

#define CPU_FILE "/proc/stat"

class CPU_stat{
public:
    int cpu_user;
    int cpu_nice;
    int cpu_system;
    int cpu_idle;
    int cpu_iowait;
    int cpu_irq;
    int cpu_softirq;

    CPU_stat();
    ~CPU_stat();
    int read_CPU_file();
    CPU_stat& operator = (const CPU_stat &c);
    void print();


};

#endif // CPU_H
