#ifndef priority_queue_h_
#define priority_queue_h_

#include <cassert>
#include <iostream>
#include <vector>
#include <map>

// The DistancePixel_PriorityQueue is a customized, non-templated
// priority queue that stores DistancePixel pointers in a heap.  The 
// elements in the heap can be looked up in a map, to quickly find out
// the current index of the element within the heap.

// ASSIGNMENT: The class implementation is incomplete.  Finish the
//   implementation of this class, and add any functions you need.

// =========================================================================

class DistancePixel_PriorityQueue {
    public:
  
    // --------------------------
    // CONSTRUCTORS
    // default constructor
    DistancePixel_PriorityQueue() {}
    // construct a heap from a vector of data
    DistancePixel_PriorityQueue(const std::vector<DistancePixel*> &values) {
        for (long unsigned int v = 0; v < values.size(); v++) {
            //std::cout << values[v]->getX() << " " << values[v]->getY() << " " << values[v]->getValue() << std::endl;
            push(values[v]);
        }
    }

    // ------------------------
    // ACCESSORS
    int size() { return m_heap.size(); }
    bool empty() { return m_heap.empty(); }
    int last_non_leaf() { return (size()-1) / 2; }
    int get_parent(int i) { assert (i > 0 && i < size()); return (i-1) / 2; }
    bool has_left_child(int i) { return (2*i)+1 < size(); }
    bool has_right_child(int i) { return (2*i)+2 < size(); }
    int get_left_child(int i) { assert (i >= 0 && has_left_child(i)); return 2*i + 1; }
    int get_right_child(int i) { assert (i >= 0 && has_right_child(i)); return 2*i + 2; }

    // read the top element
    const DistancePixel* top() const  {
        assert(!m_heap.empty());
        return m_heap[0]; 
    }

    // is this element in the heap?
    bool in_heap(DistancePixel* element) const {
        std::map<DistancePixel*,int>::const_iterator itr = backpointers.find(element);
        return (itr != backpointers.end());
    }

    // add an element to the heap
    void push(DistancePixel* element) {
        //std::cout << element->getX() << " " << element->getY() << " " << element->getValue() << std::endl;
        std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
        assert (itr == backpointers.end());
        m_heap.push_back(element);
        backpointers[element] = m_heap.size()-1;
        this->percolate_up(int(m_heap.size()-1));
    }

    // the value of this element has been edited, move the element up or down
    void update_position(DistancePixel* element) {
        std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
        assert (itr != backpointers.end());
        this->percolate_up(itr->second);
        this->percolate_down(itr->second);
    }
    
    // remove the top (minimum) element
    void pop() {
        assert(!m_heap.empty());
        int success = backpointers.erase(m_heap[0]);
        assert (success == 1);
        m_heap[0] = m_heap.back();
        m_heap.pop_back();
        this->percolate_down(0);
    }
    
    private:

    // REPRESENTATION
    // the heap is stored in a vector representation (the binary tree
    // structure "unrolled" one row at a time)
    std::vector<DistancePixel*> m_heap;
    // the map stores a correpondence between elements & indices in the heap
    std::map<DistancePixel*,int> backpointers;

    // private helper functions
    void percolate_up(int i) {
        while (((i-1) / 2) >= 0) { // while there is a "parent"
            // if the current value is smaller than the parent
            if (m_heap[i]->getValue() < m_heap[((i-1) / 2)]->getValue()) {
                // swap the values
                DistancePixel* curr_pix = m_heap[i];
                m_heap[i] = m_heap[((i-1) / 2)]; 
                m_heap[((i-1) / 2)] = curr_pix;
                i = ((i-1)/2);
            }
            else { // one its more than the parent stop swaps
                break;
            }
        }
    }
    
    void percolate_down(int i) {
        while (has_left_child(i)) { // while not at a leaf
            int child_ind = get_left_child(i);
            bool left = true;

            if (has_right_child(i)) { // if there is a right child -- check right
                // if check if the right child is less than left
                if (m_heap[get_right_child(i)]->getValue() < m_heap[child_ind]->getValue()) {
                    left = false;
                    child_ind = get_right_child(i);
                }
            }
            // check the smaller child
            // if the child is smaller than current
            if (m_heap[child_ind]->getValue() < m_heap[i]->getValue()) {
                // swap values
                DistancePixel* curr_pix = m_heap[i];
                m_heap[i] = m_heap[child_ind];
                m_heap[child_ind] = curr_pix;
                if (left) {
                    i = 2*i + 1;
                }
                else {
                    i = 2*i + 2;
                }
            }
            else { // once the heap tree conditions are filled break
                break;
            }
        }
    }
};

#endif