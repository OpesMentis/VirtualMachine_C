#include <netdb.h>
#include "config.h"

int connectServer(char *hostname, struct sockaddr_in *server, struct hostent *hote);
void getAnswer(message *msg,int sock,int *cont);
int recvImage(int sock, char * filename);
void clean(char *str, int length);
