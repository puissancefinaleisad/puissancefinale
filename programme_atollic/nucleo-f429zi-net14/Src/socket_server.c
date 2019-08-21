#include<stdio.h> //printf
#include<string.h> //strcpy
#include<sys/socket.h>
#include<netdb.h>	//hostent
#include<inet.h>
#include<unistd.h>	//write
#include"socket_server.h"

#define KLISTEN_PORT 5002
#define IP_SERVEUR "10.1.0.126"
#define IP_NUCLEO "10.1.101.101"


/*fonction qui établie la connexion
 * return - 1 en cas d'erreur
 * return la new_socket quand pas d'erreur
 */
int connexion_tcp_server_wait(const char *addr, int port)
{
	int socket_desc , new_socket , c;
	struct sockaddr_in server , client;
	char *message;

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Socket ne peut se faire - le code d'erreur est (n° %d)-%s\n",
				errno, strerror(errno));
		return -1;
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( KLISTEN_PORT );

	//Bind
	int ret = bind(socket_desc,(struct sockaddr *)&server , sizeof(server));
	if(ret < 0)
	{
		printf("bind sur l'ip %s sur le port %d ne peut se faire - le code d'erreur est (n° %d)-%s\n",
				IP_SERVEUR, KLISTEN_PORT, errno, strerror(errno));
		return -1;
		close(socket_desc);
	}
	printf("Connexion avec le client qui a l'ip %s et le port %d\n", IP_SERVEUR, KLISTEN_PORT);


	//Listen
	listen(socket_desc , 3);
	printf("En listen\n");

	//Accept and incoming connection
	printf("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if( new_socket > 0 )
	{
		printf("Connection accepted\n");

	}

	if (new_socket< 0)
	{
		printf("accept failed - le code d'erreur est (n° %d)-%s\n", errno, strerror(errno));
		return -1;
		close(new_socket);
	}

	return new_socket;
}


/* Fonction qui envoie le message
 *return -1 si erreur et
*return le nombre d'octets si ok, on envoie le message du buffer
*/
int ssend_msg(int new_socket, const char *message, int in_longueur)
{
 int ret = send(new_socket , message , in_longueur , 0);
	if( ret< 0)
	{
		printf("Envoi echoue; le code d'erreur est (n° %d)-%s\n", errno, strerror(errno));
		return -1;
	}
	printf("Message envoye\n");

	return ret;
}

/* fonction qui reçoit le message d'une socket
 *return -1 si erreur et
 *return le nombre d'octets si ok, on reçoit le message du buffer
 */
int sreceivemessage (int new_socket, char *out_server_reply ,int in_longueur)
{


	int ret = recv(new_socket, out_server_reply, in_longueur-1, 0); //recv: reçoit les messages d'une socket

	if(ret>=0){
		printf("Message recu : %d\n", ret );
		out_server_reply[ret]= '\0';
		printf("%s", out_server_reply);
	}
	else if (ret < 0)
	{
		printf("Reception échouee; le code d'erreur est (n° %d)-%s\n", errno, strerror(errno));
		return -1;
	}

	printf("Bonne reception \n");
	printf(out_server_reply);

	return ret;
}
