/*
 * message_queue.h contains the implementation of the methods used 
 * to manage scada messages received from the Data Acquisition Daemon.
 *
 * Creator: Marco
 * Created: 3/27/2015
 * Last modified: 3/27/2015
 */

#include <stdio.h>
#include <stdlib.h>
#include "message_queue.h"

int size = 0;
queue_node *head = NULL;
queue_node *tail = NULL;

int Enqueue(scada_message *m) {
  if(size >= QUEUE_SIZE)
    return -1;

  queue_node *temp = (queue_node *)malloc(sizeof(queue_node));
  temp->mess = m;

  if(size == 0)
    head = temp;
  else
    tail->next = temp;

  tail = temp;
  tail->next = NULL;
  size++;

  return 0;
}

scada_message *Dequeue() {
  if(size <= 0)
    return NULL;

  queue_node *temp = head;
  scada_message *m = temp->mess;

  if(head == tail)
    tail = NULL;

  head = head->next;
  free(temp);
  size--;

  return m;
}

scada_message *Top() {
  if(size <= 0)
    return NULL;

  return head->mess;
}
