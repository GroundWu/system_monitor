#include "net_stat.h"

net_stat::net_stat()
{
    in_bytes = 0;
    in_packets = 0;
    out_bytes = 0;
    out_packets = 0;
}

net_stat::~net_stat()
{

}

net_stat& net_stat::operator=(const net_stat &n)
{
    if(this!=&n)
    {
        this->in_bytes = n.in_bytes;
        this->in_packets = n.in_packets;
        this->out_bytes = n.out_bytes;
        this->out_packets = n.out_packets;
    }

    return *this;
}

int net_stat::read_net_stat_file()
{
    FILE *file;
    char str[2048];
    char *temp;
    char tempstr[16][16]={0};
    int count=0;
    if((file=fopen(NET_STAT_FILE,"r"))==NULL)
    {
        return -1;
    }

    while(fgets(str,sizeof(str),file)!=NULL)
    {
        if((temp=strstr(str,"ens33"))!=NULL || (temp=strstr(str,"eth"))!=NULL)
        {
            temp = strtok(str," ");
            while(temp!=NULL)
            {
                strcpy(tempstr[count],temp);
                temp = strtok(NULL," ");
                count++;
            }
            in_bytes = atoi(tempstr[1]);
            in_packets = atoi(tempstr[2]);
            out_bytes = atoi(tempstr[9]);
            out_packets = atoi(tempstr[10]);

        }
    }

    fclose(file);
    return 1;
}

void net_stat::print()
{
    printf("in_bytes:%d\tin_packets:%d\tout_bytes:%d\tout_packets%d\n",in_bytes,in_packets,out_bytes,out_packets);

}
