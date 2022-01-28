#include "minHeap.h"
/**Description of header file "minHeap.h":
 * This class defines a heap where each node has a
 * less or equal value than all of its child nodes (min-heap)
 * Implemented using a vector of integers erpresenting the
 * values at each node of a complete binary tree 
*/

// Helper functions: parentOf, Lchild, Rchild made using equations from class slides

// Returns parent index of given node
int parentOf(int pos) {
    int p = floor((pos - 1) / 2);
    return p;
}

// Returns left child index of given node
int Lchild(int pos) {
    int c = (2 * pos) + 1;
    return c;
}

// Returns right child index of given node
int Rchild(int pos) {
    int c = (2 * pos) + 2;
    return c;
}

void minHeap :: siftUp(int pos) {
    /* Check to see if heap property is violated
    if(pos && heap[parentOf(pos)] > heap[pos]) {
        // Heap property violated! Sound the alarms! Just kidding, all we gotta do is swap the nodes!
        swap(heap[pos], heap[parentOf(pos)]);

        // Recurse onto parent node
        siftUp(parentOf(pos));
    } */

    // Recursive method caused SIGPIPE error, trying an iterative method

    int parent = parentOf(pos);

    while(pos < heap.size() && heap[parent] > heap[pos]) {
        swap(heap[parent], heap[pos]);
        pos = parent;
        parent = parentOf(pos);
    }
}

void minHeap :: siftDown(int pos) {
    // Obtain left and right child indices for pos
    unsigned L = Lchild(pos);
    unsigned R = Rchild(pos);

    // Preset smaller indicator to pos
    int small = pos;

    // Find the smallest value among pos and its children
    // and check to see if the L and R values are within bounds
    if(heap[L] < heap[pos] && L < heap.size()) {
        small = L;
    }
    
    if(heap[R] < heap[small] && R < heap.size()) {
        small = R;
    }

    // If smaller is not equal to position, swap position and smaller
    if(small != pos) {
        // Swap 'em!
        swap(heap.at(pos), heap.at(small));

        // Recurse down!
        siftDown(small);
    }
}

// Builds the heap from a vector of integers
minHeap :: minHeap(vector<int> data) {
    // Loop through the vector and insert each value into heap vector 
    for(unsigned i = 0; i < data.size(); i++) {
        insert(data[i]);
    }
}

// Inserts a value into the heap
void minHeap :: insert(int value) {
    // Place value at root and sift up

    // Insert value
    heap.push_back(value);

    // Sift up
    siftUp(heap.size() - 1);
}

// Removes the minimum value from the heap
int minHeap :: removeMin() {
    // Make sure the heap is large enough to perform this
    if(heap.size() == 0) {
        // Heap is empty, print error and return 0?

        cout << "Heap is empty - cannot remove minimum value! Returning 0 to main function." << endl;

        return 0;
    } else if(heap.size() == 1) {
        // Heap has only one element in it, simply remove it and return it

        // Save root value into temp
        int temp = heap[0];

        // Remove last (and only) element in heap)
        heap.pop_back();

        // Return original root value
        return temp;
    }

    // If we have arrived here, heap is presumably larger than one element, perform full removal

    // Save root value into temp
    int temp = heap[0];

    // Set root value to last element
    heap[0] = heap.back();

    // Remove last element
    heap.pop_back();

    // Sift down from root node (position 0) to restore heap property
    siftDown(0);

    // Return original root value
    return temp;
}

/*
int main(void) {

    return 0;
}
*/