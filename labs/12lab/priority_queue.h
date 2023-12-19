#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
    private:
    std::vector<T> m_heap;

    public:
    priority_queue() {}

    priority_queue( std::vector<T> const& values )
    {
        m_heap = std::vector<T>(values.begin(), values.end());
        // Restore the min-heap property by heapifying the vector
        for (int i = m_heap.size() / 2 - 1; i >= 0; i--) {
            heapDown(i);
        }
    }

    const T& top() const 
    {
        //assert( !m_heap.empty() );
        return m_heap[0]; 
    }

    void heapUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (m_heap[parentIndex] <= m_heap[index]) {
                break; // Parent is smaller or equal, so no need to swap
            }
            std::swap(m_heap[parentIndex], m_heap[index]);
            index = parentIndex;
        }
    }

    void push( const T& entry )
    {
        m_heap.push_back(entry); // Add the new element to the end of the heap
        int index = m_heap.size() - 1; // Index of the newly added element

        // Restore the min-heap property by comparing the new element with its parent
        heapUp(index);  
        
    }

    void heapDown(int index) {
        int size = m_heap.size();
        while (index < size) {
            int leftChildIndex = 2 * index + 1;
            int rightChildIndex = 2 * index + 2;
            int smallestIndex = index;

            // Find the smallest value among the parent, left child, and right child
            if (leftChildIndex < size && m_heap[leftChildIndex] < m_heap[smallestIndex]) {
                smallestIndex = leftChildIndex;
            }
            if (rightChildIndex < size && m_heap[rightChildIndex] < m_heap[smallestIndex]) {
                smallestIndex = rightChildIndex;
            }

            if (smallestIndex == index) {
                break; // Parent is smaller or equal, so no need to swap
            }

            std::swap(m_heap[index], m_heap[smallestIndex]);
            index = smallestIndex;
        }
    }

    void pop() 
    {
        if (m_heap.empty()) {
            throw std::runtime_error("Priority queue is empty");
        }

        m_heap[0] = m_heap.back(); // Move the last element to the root
        m_heap.pop_back(); // Remove the last element

        if (!m_heap.empty()) {
            heapDown(0); // Restore the min-heap property by comparing the root with its children
        }
    }

    int size() { return m_heap.size(); }
    bool empty() { return m_heap.empty(); }


    //  The following three functions are used for debugging.

    //  Check to see that internally the heap property is realized.
    bool check_heap( )
    {
        return this->check_heap( this->m_heap );
    }

    // Helper function to check if the subtree rooted at index i satisfies heap property
    bool check_heap_subtree(const std::vector<T>& heap, int i)
    {
        int leftChildIndex = 2 * i + 1;
        int rightChildIndex = 2 * i + 2;

        if (leftChildIndex < heap.size() && heap[leftChildIndex] < heap[i]) {
            return false; // Left child is smaller, so heap property is violated
        }

        if (rightChildIndex < heap.size() && heap[rightChildIndex] < heap[i]) {
            return false; // Right child is smaller, so heap property is violated
        }

        return true; // Subtree rooted at i satisfies the heap property
    }

    //  Check an external vector to see that the heap property is realized.
    bool check_heap( const std::vector<T>& heap )
    {
        int size = heap.size();
        for (int i = 0; i < size; i++) {
            int leftChildIndex = 2 * i + 1;
            int rightChildIndex = 2 * i + 2;

            if (leftChildIndex < size && heap[leftChildIndex] < heap[i]) {
                return false; // Left child is smaller, so heap property is violated
            }

            if (rightChildIndex < size && heap[rightChildIndex] < heap[i]) {
                return false; // Right child is smaller, so heap property is violated
            }

            // Check if the left child's subtree or right child's subtree violates heap property
            if (leftChildIndex < size && !check_heap_subtree(heap, leftChildIndex)) {
                return false;
            }

            if (rightChildIndex < size && !check_heap_subtree(heap, rightChildIndex)) {
                return false;
            }

        }
        return true; // All nodes satisfy the heap property
    }

    //  A utility to print the contents of the heap.  Use it for debugging.
    void print_heap( std::ostream & ostr )
    {
        for ( unsigned int i=0; i<m_heap.size(); ++i )
        ostr << i << ": " << m_heap[i] << std::endl;
    }
    
    
};


template <class T>
void heap_sort( std::vector<T> & v )
{
    // Build a min-heap from the input vector
    priority_queue<T> pq(v);
    
    // Perform the heap sort in-place
    for (int i = v.size() - 1; i >= 0; i--) {
        v[i] = pq.top(); // Move the root (min element) to the end of the vector
        pq.pop(); // Remove the root from the priority queue
    }
}

#endif