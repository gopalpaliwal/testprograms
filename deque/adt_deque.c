// Write a deque structure and deque functions that support the following
// // signatures. Deques allow for pushing and popping on both ends of
// // a sequence-like ADT in O(1). This implementation is specialized for ints.
// //
// // Feel free to create helper structures or functions, but do not change the
// // interface used by |main|. If you would like to document any additional
// // interface behavior, please point it out. Use of reasonable assertions is
// // encouraged.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/*
 * doubly linked-list
 */
typedef struct Node {
    int      data;
    struct   Node *prev;
    struct   Node *next;
} Node;

/* 
 * deque adt structure
 */
struct deque {
    size_t  size;
    Node    *front;
    Node    *back;
};

typedef struct deque Deque;


/*
 * Allocate a new deque on the heap and return it.
 */
struct deque *deque_new() {
   
    Deque *d = (Deque *)malloc (sizeof(Deque));
    if (d == NULL) {
        printf("%s: Malloc fail. Initialization failed",__FUNCTION__); 
        assert(0);
    }

    /*
     * initialize
     */
    d->size  = 0;
    d->front = NULL;
    d->back  = NULL;

    return d;
}


/*
 * Free all the memory associated with a deque that has been created via
 * `deque_new`.
 */
void deque_delete(struct deque *d) {
	
    Node *tmp_node = NULL;
    
    if (d == NULL)
        return;

    while (d->front != NULL) {
        tmp_node = d->front;
        d->front = d->front->next;
        free(tmp_node);
        d->size--;
    }

    /*
     * sanity check for size == 0
     */
    assert (d->size == 0);
    
    d->front = NULL;
    d->back  = NULL;
    
    free(d);
    d = NULL;
}


/* 
 * Append the value to the end of the deque. O(1) complexity.
 */
void deque_push_back(struct deque *d, int value) {

    Node *new_node;

    if (d == NULL) {
        printf("%s: deque pointer null", __FUNCTION__);
        assert(0);
    }

	new_node = (Node *) malloc(sizeof(Node));
    
    new_node->data = value;
    new_node->prev = new_node->next = NULL;

    /*
	 * check if the deque is empty
	 */
    if (d->size == 0) {
        d->front = d->back = new_node;
        d->front->prev = d->front->next = NULL;
        d->back->prev = d->back->next = NULL;
        d->size++;
        return;
    }

    new_node->prev = d->back;
    d->back->next = new_node;
    d->back = new_node;

    d->size++;
}


/*
 * Prepend the value to the front of the deque. O(1) complexity.
 */
void deque_push_front(struct deque *d, int value) {

    Node *new_node;

    if (d == NULL) {
        printf("%s: deque pointer null", __FUNCTION__);
        assert(0);
    }

    new_node = (Node *) malloc(sizeof(Node));
    new_node->data = value;
    new_node->prev = new_node->next = NULL;

    /*
	 * check if the deque is empty
	 */
    if (d->size == 0) {
        d->front = d->back = new_node;
        d->front->prev = d->front->next = NULL;
        d->back->prev = d->back->next = NULL;

        d->size++;
        return;
    }

    new_node->next = d->front;
    d->front->prev = new_node;
    d->front = new_node;

    d->size++;
}

/*
 * Remove the last value off of a deque and return it. O(1) complexity.
 */
int deque_pop_back(struct deque *d) {
	
    Node *tmp_node;
    int  value = 0;
   
    if (d == NULL) {
        printf("%s: deque pointer null", __FUNCTION__);
        assert(0);
    }

    if (d->size == 0) {
        printf("%s: Error. 0 elements in deque",__FUNCTION__);
        assert(0);
    }

    tmp_node = d->back;
    d->back  = d->back->prev;
    if (d->back) d->back->next = NULL;
    
    value = tmp_node->data;
    free(tmp_node);
	
    d->size--;

    if (d->size == 0) {
        d->front = d->back = NULL;
    }

    return value;
}

/*
 * Remove the first value off of a deque and return it. O(1) complexity.
 */
int deque_pop_front(struct deque *d) {

    Node *tmp_node;
    int value = 0;

    if (d == NULL) {
        printf("%s: deque pointer null", __FUNCTION__);
        assert(0);
    }

    if (d->size == 0) {
        printf("%s: Error. 0 elements in deque", __FUNCTION__);
        assert(0);
    }

    tmp_node = d->front;
    d->front = d->front->next;
    if(d->front) d->front->prev = NULL;

    value = tmp_node->data;
    free(tmp_node);

    d->size--;

    if (d->size == 0) {
        d->front = d->back = NULL;
    }		

    return value;
}

// Return the number of values placed in the deque. O(1) complexity.
size_t deque_size(struct deque *d) {

    if (d == NULL) {
        printf("%s: deque pointer null", __FUNCTION__);
        assert(0);
    }

    return d->size;
}

// Example usage.
int main() {
	long long int i = 1;
	long long int sum = 0;
	struct timeval t1, t2;
	double elapsedTime;

	struct deque *d = deque_new(); // { }

	assert(d);

	gettimeofday(&t1, NULL);
	while( i <= 10000000) {
		deque_push_back(d, i);
		i++;
	}
	i = 1;
	while(i <= 10000000) {
		sum += deque_pop_back(d);
		i++;
	}
	gettimeofday(&t2, NULL);

	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;


	printf("sum is %lld %f  milli-secs\n\n", sum, elapsedTime);

	assert(0 == deque_size(d));
	deque_delete(d);
	return 0;

}
