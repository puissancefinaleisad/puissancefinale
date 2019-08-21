/*
 * malloc.c
 *
 *  Created on: 16 mai 2019
 *      Author: isabelle
 */

#include<stdlib.h>
#include "FreeRTOS.h"
#include <task.h> // pvxxxMalloc
#include <portable.h> // pvxxxMalloc
#include <string.h> // memset

void *malloc (size_t size) {
/* Call the FreeRTOS version of malloc. */
return pvPortMalloc( size );
}
void *calloc (size_t nmemb, size_t size) {
/* Call the FreeRTOS version of calloc. */
void * p= pvPortMalloc( size );
return memset(p,0,size);
}
void free (void *ptr) {
	vPortFree( ptr );
}
