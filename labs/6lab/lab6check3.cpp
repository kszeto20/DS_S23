#include <iostream>
#include <string>


// Note: It's ok that all the member variables are public for this
// tiny class.  We'll build up to a more robust and complete linked
// list implementation in lecture 11.
template <class T>
class Node {
public:
  T value;
  Node<T> *ptr;
};



template <class T>
void print(Node<T> *data, const std::string &label) {
  std::cout << label;
  Node<T> *tmp = data;
  while (tmp != NULL) {
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}



template <class T>
void reverse(Node<T>* &input) {
  if(input == NULL)
  {
    return;
  }

  int size = 1;
  Node<T>* tempNode = input;
  while(tempNode->ptr != NULL)
  {
    size++;
    tempNode = tempNode->ptr;
  }

  Node<T>* lastNode = tempNode;
  Node<T>* tempBackNode = lastNode;

  for(int i = 0;i < size-1;i++)
  {
    tempNode = input;
    for(int j = 0;j < size-2-i;j++)
    {
      tempNode = tempNode->ptr;
    }
    tempBackNode->ptr = tempNode;
    tempBackNode = tempBackNode->ptr;
  }

  input->ptr = NULL;
  input = lastNode;

}




int main() {

  // manually create a linked list of notes with 4 elements
  Node<int>* my_list = new Node<int>; 
  my_list->value = 1; 
  my_list->ptr = new Node<int>;
  my_list->ptr->value = 2;
  my_list->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->value = 3;
  my_list->ptr->ptr->ptr = new Node<int>;
  my_list->ptr->ptr->ptr->value = 4;
  my_list->ptr->ptr->ptr->ptr = NULL;

  
  print(my_list,"my_list before");
  reverse(my_list);
  print(my_list,"my_list after ");


  // Note: We are not deleting any of the Nodes we created...  so this
  // program has memory leaks!  More on this in lecture 11.

}

// ===========================================================================