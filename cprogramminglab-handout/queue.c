/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
         return NULL;
    } else {
        q->tail = NULL;        
        q->head = NULL;
        q->size = 0;
        return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */ 
    if (q == NULL) {
        return NULL;
    } else {
        while (q->head != NULL) {
            list_ele_t *next = (*(q->head)).next;
            free(q->head);
            q->head = next;
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (q == NULL) {
        return false;
    }
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    char *str = malloc(strlen(s) * sizeof(char) + 1);
    if (str == NULL) {
        free(newh);
        return false;
    }
    strcpy(str, s);
    newh->value = str; 
    newh->next = q->head;
    q->head = newh;
    q->size += 1;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return false;
    }
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }
    char *str = malloc(strlen(s) * sizeof(char) + 1);
    if (str == NULL) {
        free(newh);
        return false;
    }
    strcpy(str, s);
    newh->value = str;
    newh->next = NULL;
    (*(q->tail))->tail = newh;
    q->tail = newh;
    q->size += 1;
    return false;
}

void q_remove_head(queue_t *q, char *sp) {
/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
* You need to fix up this code. */
    if (q == NULL) {
        return false;
    }
    if (q->head == NULL) {
        return false;
    }
    list_ele_t *temp = q->head->next;
    strcpy(sp, q->head->value);
    free(q->head);
    q->head = temp; 
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL) {
        return NULL;
    }
    if (q->size <= 1) {
        return NULL;
    }
    list_ele_t *preHead = NULL;
    list_ele_t *currHead = q->head;
    while (currHead != NULL) {
        list_ele_t *temp = currHead->next;
        currHead->next = preHead;
        preHead = currHead;
        currHead = temp;
    }
    list_ele_t *temp = q->head;
    q->tail = q->head;
    q->head = q->tail;
}

