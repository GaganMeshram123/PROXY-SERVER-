#include "proxy_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define MAX_CLIENTS  4091
#define MAX_CLIENTS 10
typedef struct cache_element cache_element;

struc cache_element{
    char* date;
    int len;
    char*url;
    time_t lru_time_track;
    cache_element* next;

};
cache_element* find(char* url);
int add_cache_element(char* data, int size, char* url);
void remove_cache_element();

int port_number = 8000;
int proxy_socketId;
pthread_t tid[MAX_CLIENTS];
sem_t semaphore // it has the multiple values mea
//ns it can take it 
pthread_mutex_t lock;

cache_element* head;
int cache_size;


void *thread_fn(void *socketNew){
   sem_wait(&semaphore);
    int p;
    sem_getvalue(&semaphore, p);
    printf(:semaphore value is: %d\n,p);
    int *t = (int*) socketNew;
    int socket =*t; // pointer something banavtoy apan ithe
    int bytes_send_client, len;

    char*buffer =(char*)calloc(MAX_BYTES, sizeof(char));
    bzero(buffer, MAX_BYTES);
    bytes_send_client = recv(socket , buffer, MAX_BYTES, 0);


    while(bytes_send_client > 0 ){
      len = strlen(buffer);
      if(strstr(buffer,"\r\n\r\n") == NULL){
         bytes_send_client = recv(socket, buffer + len,  MAX_BYTES_len, 0); 
      }
      else{
         break;
      }(
    } 
   
   char *tempReq = (char *)malloc(strlen(buffer)*sizeof(char)+ 1));
   for( int i = 0 ; i< strlen(buffer) ; i++){
      tempReq[i] = buffer[i];
   }
   struct cache_element*temp = find(tempReq);
   if(temp != NULL)
   {
      int size =temp->len/sizeof(char);
   };
   

}

int main(int argc, char* argv[]){
    int client_socketId, client_len;
    struct sockaddr server_addr,client_addr;
    sem_init(&semaphore, MAX_CLIENTS);
    pthread_mutex_init(&lock, NULL);
     if(argv == 2){
        port_number = atoi(argv[1]);
     }else{
        printf("too few arguments\n");
        exit(1);
     }
     printf("starting proxy server at port: %d\n, port_number");
     proxy_socketId = socket(Af_inet, SOCK_STREAM, 0);
     IF(proxy_socketId <0){
        perror("Failed to create a socket\n");
        exit(1);
     }

     int reuse = 1;
     if(setsocket(proxy_socketId, SQL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse))<0){
        perror("setSockopt failed\n");
     }

     bzero((char*)&server_addr, size_of(server_addr));
     server_addr.sin_family = AF_INET;
     server_addr.sin_port = htons(port_number);
     server_addr.sin_addr.s_addr = INADDR_ANY;
     if(bind(proxy_socketId, (struct sockaddr*) &server_addr, sizeof(server_addr)<0)){
        perror("port is not avaiabe\n");
        exit(1);
     }
     printf("Binding on port %d\n", port_number);
     int listen_status = listen (proxy_socketId, MAX_CLIENTS);
     if(listen_status < 0 ){
         perror ("error in listening\n");
         exit(1);
     }
      int i = 0;
      int connected_socketId[MAX_CLIENTS];
      while(1){
        bzero((char *)&client_addr , sizeof(client_addr));
        client_len = sizeof(client_addr);
        client_socketId = accept(proxy_socketId, (struct *sockaddr)&client_addr,(socklen_t*) &client_len);
// typecasting nahi hoti apne ko karna padhat ahai 
        if(client_socketId<0){
            printf("Not able to connect");
            exit(1);
        }
        else{
            connected_socketId[i] = client_socketId;
        }
        struct sockaddr_in = client_pt ={ struct sockaddr_in *}&client_addr;
        struct in_addr * client_pt->sin_addr;
        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_inet, &ip_addr, str, INET_ADDRSTRLEN);
        printf("client is connected with port number %d and ip address is %\n,ntohs(client_addr)");

        pthread_create(&tid[i],NULL, thread_fn, (void*)&connected_socketId[i]);
       i++;
      }
close(proxy_socketId);
return 0;
   
}
