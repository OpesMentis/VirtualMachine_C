#include <unistd.h>
#include "client.h"

int main (int argc, const char* argv[] ){
	
	if(argc<2){
		printf("Missing argument.\nUsage: ./client [server_name]\n");
		return 0;
	}

	// Structure de communication
	message* msg = malloc(sizeof(message));
	// Variables du programme
	int cont = 1;
	struct hostent * hote = NULL;
	struct sockaddr_in server;
	
	// Connection au serveur et création des répertoires d'images
	int sock = connectServer((char*) argv[1], &server, hote);
	mkdir(REP,S_IRWXU);
	mkdir(IM_C,S_IRWXU);
	
	while(cont){
		printf(">> ");
		char line[2*NAME_L];
		char *tmp;
		// Récupération de la ligne entrée
		fgets(line,2*NAME_L,stdin);
		// Décomposition dans la structure de communication
		if((tmp=strtok(line," "))!=NULL){
			strncpy(msg->cmd, tmp,CMD_L);
			if((tmp=strtok(NULL," "))!=NULL){
				strncpy(msg->enc, tmp,CMD_L);
			}
			if((tmp=strtok(NULL," "))!=NULL){
				strncpy(msg->img, tmp,NAME_L);
			}
			clean(msg->cmd,CMD_L);
			clean(msg->enc,CMD_L);
			clean(msg->img,NAME_L);
			// Envoi du message et attente de la réponse
			if(msg->cmd[0]!='\0'){
				send(sock,msg,sizeof(message),MSG_EOR);
				getAnswer(msg,sock,&cont);
			}
		}
	}
	
	// Déconnection du serveur et désallocation de la mémoire
	printf("Disconnecting...\n");
	free(msg);
	close(sock);
	printf("Shutting down now !\n");
	return 0;
}

// Connection au serveur
int connectServer(char *hostname, struct sockaddr_in *server, struct hostent *hote){
	printf("Establishing connection with %s...\n",hostname);
	int sock;
	//Recuperation du nom du serveur
	hote = gethostbyname(hostname);
	// Configuration de l'adresse du futur serveur
	server->sin_family=AF_INET;
	server->sin_port=htons(PORT);
	bcopy(hote->h_addr,&(server->sin_addr.s_addr),hote->h_length);
	//Creation du socket client
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("Socket creation error");
        exit(1);
    }
    //Connection au serveur
	if(connect(sock,(struct sockaddr *)server,sizeof(*server))==-1){
		perror("Connection error");
		exit(1);
	}
	printf("Connected !\n\n\
--------------------------------------------------------------------------------");
	return sock;
}

void getAnswer(message *msg,int sock,int *cont){
	// Réception et traitement du message d'en-tête
	recv(sock,msg,sizeof(message),0);
	char answer[MSG_L];
	switch(msg->info){
		case 0: // Réception d'une chaîne de caractères
			recv(sock,answer,MSG_L,0);
			if(answer[0]!='K'){
				printf("%s",answer);
			}
			else{
				*cont =0;
			}
			break;
		case 1: // Réception d'une image
			printf("Downloading...\n");
			recvImage(sock,msg->img);
			break;
		case 2:// Réception d'une liste d'images
			printf("List of images :\n\n");
			// Affichage direct des données reçues
			while(recv(sock, answer, MSG_L, 0)==MSG_L){
				printf("%s",answer);
			}
	}
}

// Fonction de reception et d'ecriture d'images dans un header.
int recvImage(int sock, char * filename){
	char * fullPath = malloc(2*NAME_L);
	getFullPath(fullPath, REP, filename);
	FILE * image = fopen(fullPath,"wb");
	unsigned char buffer[MSG_L];
	if(!image){
		printf("Problem while creating file.\n");
		return -1;
	}
	fseek(image, 0, SEEK_SET);
	/* Ecriture en boucle des données reçues dans le fichier jusqu'à réception 
	du message de fin qui n'a pas la même taille*/
	while(recv(sock, buffer, MSG_L, 0)==MSG_L){
		fwrite(buffer, MSG_L, 1, image);
	}
	fclose(image);
	printf("Image received.\n");
	// Affichage de l'image reçue
	char *buf = calloc(3*NAME_L,1);
	strcat(buf, "eog ");
	strcat(buf, fullPath);
	strcat(buf," &");
	system(buf);
	free(buf);
	free(fullPath);
	return 0;
}

// Permet d'effacer les \n d'un chaîne de caractères
void clean(char *str, int length){
	int i;
	for(i =0; i<length; i++){
		if(str[i]=='\n'){
			str[i]='\0';
		}
	}
}
