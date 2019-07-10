#ifndef NET_STAT_H
#define NET_STAT_H
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<climits>
#define NET_STAT_FILE "/proc/net/dev"
class net_stat
{
public:
    int in_bytes;
    int in_packets;
    int out_bytes;
    int out_packets;

    net_stat();
    ~net_stat();
    net_stat& operator=(const net_stat &n);
    int read_net_stat_file();
    void print();

};


#endif // NET_STAT_H
