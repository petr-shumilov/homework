#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <netinet/tcp.h>   
#include <netinet/ip.h>   
#include <sys/socket.h>
#include <arpa/inet.h>


#define BUFFER_SIZE 65536

char * append(const char * str, char c)
{
    char * new_string = malloc(strlen(str)+2);  
    int i;
    for (i = 0; i < strlen(str); ++i)
        new_string[i] = str[i];
    new_string[strlen(str)] = c;
    new_string[strlen(str) + 1] = '\0'; 
    return new_string;
}

const char* print_payload(char* data , int Size)
{
    int i, j;
    char *payload = "";
    for(i = 0; i < Size; ++i)
    {
        if (i != 0 && i % 16 == 0)   
        {
            for(j = i - 16; j <  i; ++j)
            {
                if ((data[j] >= 32 && data[j] <= 128) || data[j] == 10)
                {
                    payload = append(payload, data[j]);
                }
            }
        } 
        
        if (i == Size - 1) 
        {
            for(j = i - i % 16; j <= i; ++j)
            {
                if ((data[j] >= 32 && data[j] <= 128) || data[j] == 10)
                {
                    payload = append(payload, data[j]);
                }
            }
        }
    }
    return payload;
}

void print_http(char* buffer, int size)
{     
    struct iphdr *iph = (struct iphdr *)buffer;
    if (iph->protocol != 6)
        return ;
    
    struct tcphdr *tcph = (struct tcphdr*)(buffer + (unsigned  int)(iph->ihl * 4));

    struct sockaddr_in src, dest;
    
    memset(&src, 0, sizeof(src));
    src.sin_addr.s_addr = iph->saddr;

     
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = iph->daddr;

   
    if (ntohs(tcph->source) == 80)
    {
        printf("<----------PACKET_BEGIN---------->\n");
        printf("<------INFO_BEGIN------>\n");
        printf("Packet Length: %d  bytes\n", ntohs(iph->tot_len));
        printf("Src IP:        %s\n", inet_ntoa(src.sin_addr));
        printf("Src port:      %u\n", ntohs(tcph->source));
        printf("Dest port:     %u\n", ntohs(tcph->dest));
        printf("Dest IP:       %s\n", inet_ntoa(dest.sin_addr));
        printf("<------INFO_END------>\n");
        printf("%s", print_payload(buffer + iph->ihl * 4 + tcph->doff * 4, (size - tcph->doff * 4 - iph->ihl * 4)));
        printf("<----------PACKET_END---------->\n\n\n");
    }
}

int main(int argc, char *argv[])
{
    int raw_sock = socket(AF_INET , SOCK_RAW , IPPROTO_TCP);
    if(raw_sock < 0)
    {
        printf("Socket Error\n");
        return 1;
    }

    socklen_t saddr_size; int data_size;
    struct sockaddr saddr;
    char *buffer = (char *)malloc(BUFFER_SIZE);
        
    while(1)
    {
        saddr_size = sizeof(saddr);
        data_size = recvfrom(raw_sock, buffer , BUFFER_SIZE , 0 , &saddr , &saddr_size);
        if(data_size < 0)
        {
            printf("Failed to get packets\n");
            return 1;
        }
        print_http(buffer, data_size);
    }

    return 0;
}