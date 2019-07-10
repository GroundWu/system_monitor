#include "disk_stats.h"
disk_stat::disk_stat()
{
    readios = 0;
    readsectors = 0;
    writeios = 0;
    writesectors = 0;
}

disk_stat::~disk_stat()
{

}

disk_stat& disk_stat::operator=(const disk_stat &d)
{
    if(this != &d)
    {
        this->readios = d.readios;
        this->readsectors = d.readsectors;
        this->writeios = d.writeios;
        this->writesectors = d.writesectors;
    }
    return *this;
}

int disk_stat::read_diskestats_file()
{
    FILE *file;
    char str[2048];
    char *temp;
    char tempstr[13][16];
    int count = 0;
    if((file = fopen(DISK_STAT_FILE,"r"))==NULL)
    {
         return -1;
    }

    while(fgets(str,sizeof(str),file)!=NULL)
    {
        if((temp = strstr(str,"sda"))!=NULL)
        {
            temp=strtok(str," ");
            while(temp!=NULL)
            {
                strcpy(tempstr[count],temp);
                count++;
                temp = strtok(NULL," ");
            }
            break;
        }
    }
    readios = atoi(tempstr[3]);
    readsectors = atoi(tempstr[5]);
    writeios = atoi(tempstr[7]);
    writesectors = atoi(tempstr[9]);
    return 0;

}
void disk_stat::print()
{
    printf("readios:%s\treadsectors:%s\twriteios:%s\twritesector:%s\n",readios,readsectors,writeios,writesectors);
}
