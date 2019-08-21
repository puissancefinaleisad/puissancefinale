/*
 * connect.h
 *
 *  Created on: 17 mai 2019
 *      Author: isabelle
 */

#ifndef SOCKET_CLIENT_H_
#define SOCKET_CLIENT_H_
//#define TAILLE_MAX 2000

//extern int g_socket_desc;
extern int connexion (const char *, int);

extern int send_msg (int, const char *, int);
extern int receivemessage (int, char *, int);


#endif /* SOCKET_CLIENT_H_ */
