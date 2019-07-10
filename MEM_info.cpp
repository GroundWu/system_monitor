#include "MEM_info.h"
MEM_info::MEM_info()
{
    mem_total=0;
    mem_avail=0;
    mem_free=0;
    mem_buffer=0;
    mem_cache=0;
    mem_swapfree=0;
    mem_swaptotal=0;
}

MEM_info::~MEM_info()
{

}

MEM_info& MEM_info::operator=(const MEM_info &m)
{
    if(this!=&m)
    {
        this->mem_total = m.mem_total;
        this->mem_avail = m.mem_avail;
        this->mem_free = m.mem_free;
        this->mem_buffer = m.mem_buffer;
        this->mem_cache = m.mem_cache;
        this->mem_swapfree = m.mem_swapfree;
        this->mem_swaptotal = m.mem_swaptotal;
    }
    return *this;
}

int MEM_info::read_meminfo_file()
{
    FILE *file;
    char str[2048];
    char *temp;

    if((file = fopen(MEM_INFFO_FILE,"r"))==NULL)
    {
        return -1;
    }

    while(fgets(str, sizeof(str),file)!=NULL)
    {
        temp = strtok(str,":  ");
        if(strcmp(temp,"MemTotal")==0)
        {
            mem_total = (unsigned long)atof(strtok(NULL,":"));
        }
        else if(strcmp(temp,"MemAvailable")==0)
        {
            mem_avail = (unsigned long)atof(strtok(NULL,":  "));
        }
        else if(strcmp(temp,"MemFree")==0)
        {
            mem_free = (unsigned long)atof(strtok(NULL,":  "));
        }
        else if(strcmp(temp,"Buffers")==0)
        {
            mem_buffer = (unsigned long)atof(strtok(NULL,":  "));
        }
        else if(strcmp(temp,"Cached")==0)
        {
            mem_cache = (unsigned long)atof(strtok(NULL,":  "));
        }
        else if(strcmp(temp,"SwapTotal")==0)
        {
            mem_swaptotal = (unsigned long)atof(strtok(NULL,":  "));
        }
        else if(strcmp(temp,"SwapFree")==0)
        {
            mem_swapfree = (unsigned long)atof(strtok(NULL,":  "));
        }

    }

    fclose(file);
    return 0;
}

void MEM_info::print()
{
    printf("mem_total:%lu\nmem_avail:%lu\nmem_free:%lu\nmem_buffer:%lu\nmem_cache:%lu\nmem_swaptotal:%lu\nmem_swapfree:%lu\n",
           mem_total,mem_avail,mem_free,mem_buffer,mem_cache,mem_swaptotal,mem_swapfree);
}
