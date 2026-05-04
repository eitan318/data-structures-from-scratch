#include "singly_linked_list.h"

Node* getNodeByIdx(Node* head, int idx);
Node* getNodeByData(Node** head, void* data, size_t data_size, int (*cmp_func)(void*, void*));

Node* create_node(void* data, size_t data_size) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = (void*)malloc(sizeof(data_size));
	new_node->next = NULL;

	memcpy(new_node->data, data, data_size);
	return new_node;
}

Node* create_int(int value) {
	return create_node(&value, sizeof(int));
}

Node* create_float(float value) {
	return create_node(&value, sizeof(float));
}
	

Node* create_char(Node** head, char value) {
	return create_node(&value, sizeof(char));
}

void add_node_start(Node** head, void* data, size_t data_size ) {
	Node* new_node = create_node(data, data_size);
	new_node->next = *head;
	*head = new_node;
}

void print_list(Node* head, void (*print_func)(void*)) {
	Node* curr = head;
	while (curr) {
		print_func(curr->data);
		curr = curr->next;
	}
}


void remove_node(Node** head, void* data, size_t data_size, int (*cmp_func)(void*, void*)) {
	if (*head == NULL) {
		return; // List is empty
	}

	Node* curr = *head;
	Node* prev = NULL;

	// If the head needs to be removed
	if (cmp_func(curr->data, data) == 0) {
		*head = curr->next;
		free(curr->data);
		free(curr);
		return;
	}

	// Traverse the list to find the node to remove
	while (curr != NULL && cmp_func(curr->data, data) != 0) {
		prev = curr;
		curr = curr->next;
	}

	// If the data was not found in the list
	if (curr == NULL) {
		return;
	}

	// Remove the node
	prev->next = curr->next;
	free(curr->data);
	free(curr);
}

void remove_at(Node** head, int idx) {
	if (*head == NULL) {
		return; // List is empty
	}

	Node* curr = *head;
	Node* prev = NULL;

	// If the head needs to be removed
	if (idx == 0) {
		*head = curr->next;
		free(curr->data);
		free(curr);
		return;
	}

	// Traverse to the node at the given index
	int i;
	for (i = 0; i < idx && curr; i++) {
		prev = curr;
		curr = curr->next;
	}

	// If the index is out of bounds
	if (!curr) {
		return;
	}

	// Remove the node
	prev->next = curr->next;
	free(curr->data);
	free(curr);
}

void add_node(Node** head, void* data, size_t data_size) {
	Node* new_node = create_node(data, data_size);

	if (*head == NULL) {
		// If the list is empty, the new node is now the head
		*head = new_node;
		return;
	}

	Node* curr = *head;
	while (curr->next != NULL) {
		curr = curr->next;
	}

	curr->next = new_node;
}


void insert_at(Node** head, void* data, size_t data_size, int idx) {
	Node* new_node = create_node(data, data_size);

	// Check if the list is empty and idx > 0
	if (*head == NULL && idx > 0) {
		fprintf(stderr, "Error: Index out of bounds.\n");
		free(new_node);
		return;
	}

	Node* curr = *head;
	Node* prev = NULL;

	// If new node should be head
	if (idx == 0) {
		new_node->next = *head;
		*head = new_node;
		return;
	}

	// Traverse to the node at the given index or the end of the list
	int i;
	for (i = 0; i < idx && curr != NULL; i++) {
		prev = curr;
		curr = curr->next;
	}

	// If the index is out of bounds (idx > list length)
	if (i != idx) {
		fprintf(stderr, "Error: Index out of bounds.\n");
		free(new_node);
		return;
	}

	// Insert the new node
	prev->next = new_node;
	new_node->next = curr;
}


Node* reverse_list(Node* head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}
	Node* new_head = reverse_list(head->next);
	
	// Adjust the pointers to reverse the current node
	head->next->next = head;
	head->next = NULL;

	return new_head;
}

void move_node(Node** head, int idxFrom, int idxTo) {
	if (idxFrom == idxTo || *head == NULL) {
		return;  // No need to move if the indices are the same or the list is empty
	}

	Node* prevFrom = NULL;
	Node* currFrom = *head;

	// Find the node at idxFrom and its previous node
	for (int i = 0; i < idxFrom; i++) {
		if (currFrom == NULL) {
			printf("IndexFrom out of bounds\n");
			return;  // Index out of bounds
		}
		prevFrom = currFrom;
		currFrom = currFrom->next;
	}

	if (currFrom == NULL) {
		printf("IndexFrom out of bounds\n");
		return;  // Index out of bounds
	}

	// Detach the node at idxFrom
	if (prevFrom != NULL) {
		prevFrom->next = currFrom->next;
	}
	else {
		*head = currFrom->next;  // Moving the head node
	}

	// If idxTo is 0, move the node to the front
	if (idxTo == 0) {
		currFrom->next = *head;
		*head = currFrom;
		return;
	}

	// Find the node at idxTo and its previous node
	Node* prevTo = NULL;
	Node* currTo = *head;
	for (int i = 0; i < idxTo; i++) {
		if (currTo == NULL) {
			break;  // Index out of bounds; place the node at the end
		}
		prevTo = currTo;
		currTo = currTo->next;
	}

	// Insert the node at the new position
	if (prevTo != NULL) {
		prevTo->next = currFrom;
	}
	currFrom->next = currTo;
}

Node* getNodeByIdx(Node* head, int idx) {
	return NULL;
}

Node* getNodeByData(Node** head, void* data, size_t data_size, int (*cmp_func)(void*, void*)) {
	return NULL;
}

void free_list(Node* head) {
	Node* temp = head;
	while (head) {
		temp = head;
		head = head->next;
		free(temp->data);
		free(temp);
	}
}

