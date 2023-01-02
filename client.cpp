#include<iostream>
#include <fstream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 4444

using namespace std;

int main(int argc, char** argv) {
  int cliSockDes, readStatus, len;
  struct sockaddr_in serAddr;
  char msg[] = "Broadcast message from SLAVE TAG!!!\n";
  char buff[1024] = {0};
  
  int broadcast = 1;

  cout<<"create a socket\n";
  if((cliSockDes = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("socket creation error...\n");
    exit(-1);
  }
  
  if(setsockopt(cliSockDes, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) <0)
   {
   
    perror("socket set error...\n");
    exit(-1);
   }
 

  cout<<"server socket address\n";
  serAddr.sin_family = AF_INET;
  serAddr.sin_port = htons(PORT);
  serAddr.sin_addr.s_addr = INADDR_BROADCAST;
cout<<"sending msg now";
  sendto(cliSockDes, msg, strlen(msg)+1, 0, (struct sockaddr*)&serAddr, sizeof(serAddr));
//cout<<"send msg";
//cout<<"receving reply from server";
  readStatus = recvfrom(cliSockDes, buff, 1024, 0, (struct sockaddr*)&serAddr, (socklen_t*)&len);
  buff[readStatus] = '\0';
  cout<<buff;

  return 0;
}
