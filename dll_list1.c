#include <stdio.h>
#include <stdlib.h>

// Step 1 - Create the struct for dll_node
typedef struct dll_node{

  // Step 2-1 - Create a int to hold data
	int data;

  // Step 2-2 - Create a struct to hold pointer to prev node
	struct dll_node* prev_node;

  // Step 2-2 - Create a struct to hold pointer to next node
	struct dll_node* next_node;

}dll_node;


// Step 3 - Create the struct for dllist
typedef struct dllist{

  // Make the dll_node member called head_node
	struct dll_node* head_node;

  // Make the dll_node member called tail_node
	struct dll_node* tail_node;

}dllist;


// Step 8 - Function to insert in the front of doubly linked list
void push_front( dllist* the_list, int the_value ){

	// Create a dll_node pointer called insert_node
	dll_node* insert_node = (dll_node*)malloc( sizeof(dll_node) );

	// Set the insert_node's data to the_value and next_node and prev_node to NULL
	insert_node->data = the_value;
	insert_node->prev_node = NULL;
	insert_node->next_node = NULL;

	//Check if head is NULL
	if( the_list->head_node == NULL ){

		// Set the head node and tail node equal to insert_node
		the_list->head_node = insert_node;
		the_list->tail_node = insert_node;

    //And return
		return;
	}

	// Otherwise, we perform the pointer arithmetic
  // make a reference ptr to the head_node
	dll_node* reference = the_list->head_node;

	// Set the head_node to the new insert_node
	the_list->head_node = insert_node;

	// Set the new head_node's next to the reference (old head node)
	// and reference's (old head node) prev to new head node
	the_list->head_node->next_node = reference;
	reference->prev_node = the_list->head_node;

}
// Step 9 - Function to insert in the back of doubly linked list
void push_back( dllist* the_list, int the_value ){

	// Create a dll_node pointer called insert_node
	dll_node* insert_node = (dll_node*)malloc( sizeof(dll_node) );

	// Set the insert_node's data to the_value and next_node and prev_node to NULL
	insert_node->data = the_value;
	insert_node->prev_node = NULL;
	insert_node->next_node = NULL;

	// Check if the list is empty
	if( the_list->tail_node == NULL ){

		// Set the head node and tail node equal to insert_node
		the_list->head_node = insert_node;
		the_list->tail_node = insert_node;

		// And return
		return;
	}

	//Now we just need to use a reference pointer and put them in the back
	dll_node* reference = the_list->tail_node;

	// Set the tail_node to the new node
	the_list->tail_node = insert_node;

	// Set the new tail_node's prev to the reference and old 
	// tail node's (reference) next to new tail node
	the_list->tail_node->prev_node = reference;
	reference->next_node = the_list->tail_node;

}


// Step 12 - Print the Doubly Linked List
void print_list( dll_node* head_node ){

	dll_node* curr_ptr = head_node;
	while( curr_ptr != NULL ){

		fprintf( stdout, "Node Base Address: %p\n", curr_ptr );
		fprintf( stdout, "Data Value: %d\n", curr_ptr->data );
		fprintf( stdout, "Location of Prev Node: %p\n", &(curr_ptr->prev_node) );
		fprintf( stdout, "Value of Prev Node: %p\n", curr_ptr->prev_node );
		fprintf( stdout, "Location of Next Node: %p\n", &(curr_ptr->next_node) );
		fprintf( stdout, "Value of Next Node: %p\n\n", curr_ptr->next_node );

		// Iterate through the next node
		curr_ptr = curr_ptr->next_node;

	}
	fprintf( stdout, "\n" );

}


// Step 10 - Free all the elements
void destructor( dll_node* curr_ptr ){
  //Create a temporary pointer to hold the current pointer
  struct dll_node* tmp;

  // Check if curr_ptr is not NULL
  while (curr_ptr != NULL) {  
    
    // Set temporary pointer to current pointer
    tmp = curr_ptr;

    //Set the current pointer to point to the next pointer in the list
    curr_ptr = curr_ptr->next_node;

    //Free the temporary pointer
    free(tmp);
  }

  return;
}



int main( const int argc, const char* argv[] ){

	// Step 4 - Dynamically allocate a dllist
	dllist* the_list = (dllist *)malloc( sizeof( dllist ) );

	// Step 4-1 - Set the head_node and tail_node to NULL
	the_list->head_node = NULL;
	the_list->tail_node = NULL;

	fprintf( stdout, "Base Addresses: %p %p\n", &the_list, the_list );

	//Step 6 - Read values from file to insert into doubly linked list
	FILE* ifptr = fopen("input.txt", "r");
	if (ifptr == NULL) {
		
		printf("File does not exist!");
		return 0;
		
	}
	int iter, the_value, num_values;
	fscanf(ifptr,"%d", &num_values);

	// Step 7 - Call insert with as many as we want to insert
  char push;
	for( iter = 0; iter < num_values; ++iter ){

		fscanf( ifptr,"%d %c", &the_value, &push);
			
		if ( push == 'F') {
			push_front( the_list, the_value );
		}
		else {
			push_back( the_list, the_value );
		}

	}
	

	fprintf( stdout, "Head Node Addresses: %p %p\n", &(the_list->head_node), the_list->head_node );
	fprintf( stdout, "Tail Node Addresses: %p %p\n\n", &(the_list->tail_node), the_list->tail_node );

	// Step 13 - Call the print in main
	print_list( the_list->head_node );

	// Step 11 - Call the destructor
	destructor( the_list->head_node );

	// Step 5 - Free the dllist
	free( the_list );

	return EXIT_SUCCESS;
}
