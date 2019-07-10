#include "CPU_stat.h"

CPU_stat::CPU_stat()
{
    cpu_user=0;
    cpu_nice=0;
    cpu_system=0;
    cpu_idle=0;
    cpu_iowait=0;
    cpu_irq=0;
    cpu_softirq=0;
}

CPU_stat& CPU_stat::operator=(const CPU_stat &c)
{
    if(this != &c)
    {
        this->cpu_user = c.cpu_user;
        this->cpu_nice = c.cpu_nice;
        this->cpu_system = c.cpu_system;
        this->cpu_idle = c.cpu_idle;
        this->cpu_iowait = c.cpu_iowait;
        this->cpu_irq = c.cpu_irq;
        this->cpu_softirq = c.cpu_softirq;
    }
    return *this;
}
CPU_stat::~CPU_stat()
{

}

int CPU_stat::read_CPU_file()
{
    FILE* file;

    if((file = fopen(CPU_FILE,"r"))==NULL)
    {
        return -1;
    }
    char str[2048];
    fgets(str,sizeof(str),file);

    strtok(str," ");
    this->cpu_user = atoi(strtok(NULL," "));
    this->cpu_nice = atoi(strtok(NULL," "));
    this->cpu_system = atoi(strtok(NULL," "));
    this->cpu_idle = atoi(strtok(NULL," "));
    this->cpu_iowait = atoi(strtok(NULL," "));
    this->cpu_irq = atoi(strtok(NULL," "));
    this->cpu_softirq = atoi(strtok(NULL," "));

    fclose(file);
    return 0;
}

void CPU_stat::print()
{
        printf("user:%d\nnice:%d\nsystem:%d\nidle:%d\niowait:%d\nirq:%d\nsoftirq:%d\n",
               cpu_user,cpu_nice,cpu_system,cpu_idle,cpu_iowait,cpu_irq,cpu_softirq);
}
