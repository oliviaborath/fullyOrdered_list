/*
 * List342.h
 * List342 is a class for a fully ordered list, different types of objects can be stored in it. List342's implementation is right underneath.
*/

#include <iostream>
#include <ostream>
#include <fstream>
using namespace std;
template<class ItemType> class List342;

template<class ItemType>
class List342{
    public:
    List342();

    List342(List342 &list);

    List342(string fileName);

    ~List342();

    bool BuildList(string fileName);

    bool Insert(ItemType *obj);

    bool Remove(ItemType target, ItemType &result);

    bool Peek(ItemType target, ItemType &result) const;

    bool isEmpty() const;

    void DeleteList();

    bool Merge(List342<ItemType> &list1);
    
    friend ostream& operator<< (ostream &out_stream, const List342<ItemType> &list){ //Code was put here to avoid Linker error.
    Node *curr = list.head_;
    while(curr != nullptr){
        out_stream << *curr->data;
    curr = curr -> next;
    }
    return out_stream;
    }

    List342<ItemType> operator+(const List342<ItemType> &list) const;

    List342<ItemType>& operator+=(const List342<ItemType> &list);

    bool operator==(const List342<ItemType> &list);

    bool operator!=(const List342<ItemType> &list);

    List342<ItemType>& operator=(const List342<ItemType> &list);
    
private:
    struct Node{
        ItemType* data = nullptr;
            Node* next = nullptr;
        };
    Node* head_;
};

template <class ItemType>
List342<ItemType>::List342(){
    head_ = nullptr;
}

template <class ItemType>
List342<ItemType>::List342(List342 &list){
    head_ = nullptr;
    *this = list;
}

template <class ItemType>
List342<ItemType>::List342(string fileName){
    BuildList(fileName);
}

template <class ItemType>
bool List342<ItemType>::BuildList(string fileName){
    ifstream in_file;
    in_file.open(fileName);
    if(in_file.is_open()){
        while(!in_file.eof()){ //While we have not hit the end of file
            ItemType *item = new ItemType(); //Create the item
            in_file >> *item; 
            Insert(item);
        }
        return true;
        in_file.close();
    }
    else
    {
        cout << "file: " << fileName << " not found " << endl;
        return false;
    }
}

template <class ItemType>
bool List342<ItemType>::Insert(ItemType *obj){
    Node* ins_node = new Node;
    ins_node->data = obj;
    //If list is empty.
    if(head_ == nullptr){
        head_ = ins_node;
        return true;
    }
     Node* temp = head_; //duplicate check
          while(temp != nullptr){
              if(*temp->data == *obj)
                  return false;
              else
                  temp = temp->next;
          }
    Node* curr = head_;
        //Sorting algorithm (Insertion Sort) Based off Geeks4Geeks's code.
        //head end case
        if (head_ == nullptr || *head_->data > *ins_node->data){
            if(*curr-> data == *obj)
                return false;
            ins_node->next = head_;
            head_ = ins_node;
        }
        else
        {
            //Find node before the point of insertion
            if(*curr-> data == *obj)
                return false;
            curr = head_;
            while (curr ->next!= nullptr && *curr->next->data < *ins_node->data)
            curr = curr->next;
            ins_node->next = curr->next;
            curr->next = ins_node;
        }
        return true;
    }


template <class ItemType>
bool List342<ItemType>::Remove(ItemType target, ItemType &result){
    if(isEmpty())
        return false;
    Node *curr;
    if(*head_->data == target){
        curr = head_;
        head_ = head_->next;
        result = *curr->data; //Change result to what we're deleting.
        delete curr;
        curr = nullptr;
        return true;
}
    Node* p_node = head_;
    while(p_node->next != nullptr && *p_node->next->data < target)
        p_node = p_node->next;
    if(p_node->next == nullptr)
        return false;
    if(*p_node->next->data == target){
        curr = p_node->next;
        result = *curr->data;
        p_node->next = p_node->next->next;
        delete curr;
        curr = nullptr;
        return true;
    }
    return false;
}

template <class ItemType>
bool List342<ItemType>::Peek(ItemType target, ItemType &result) const{
    if(head_ == nullptr)
        return false;
    if(*head_->data == target){
        result = *head_->data; //Change result to what we're peeking at.
        return true;
}
    Node* curr = head_;
    while(curr->next != nullptr && *curr->next->data != target)
        curr = curr->next;
    if(curr->next == nullptr){
        return false;
    }
    else{
        Node* toReturn = curr->next;
        curr->next = curr->next->next;
        result = *toReturn->data;
        return true;
    }
}

template <class ItemType>
bool List342<ItemType>::isEmpty() const{
if(head_ == nullptr)
    return true;
else
    return false;
}

template <class ItemType>
void List342<ItemType>::DeleteList(){
    while(!(head_ == nullptr)){
        Node* t_node = new Node;
        t_node = head_;
        head_ = head_->next;
        delete(t_node);
        t_node = nullptr;
    }
}


template <class ItemType>
bool List342<ItemType>::Merge(List342<ItemType> &list1){
    if(*this == list1)
        return false;
    Node* curr = head_;
    while(list1.head_ != nullptr && curr != nullptr){ //While list1 and curr are not null
        if(curr->next == nullptr){ //If curr.next is the same as list1's head
            curr->next = list1.head_; //Move curr's pointer to point at list1's head.
            list1.head_ = nullptr;
            return true;
        }
        else if(*head_->data == *list1.head_->data){ //If duplicate found (heads)
            Node *toDelete = list1.head_;
            list1.head_ = list1.head_->next;
            delete(toDelete);
        }
        else if(*head_->data > *list1.head_->data){
            head_ = list1.head_;
            list1.head_ = list1.head_->next;
            head_->next = curr;
            curr = head_;
        }
        else if(*curr->next->data == *list1.head_->data){ //If duplicate found
            Node *toDelete = curr->next; //
            toDelete = list1.head_; //Delete list1's node data.
            list1.head_ = list1.head_->next;
            delete(toDelete);
        }
        else if (*curr->next->data > *list1.head_->data){
            Node *temp = curr->next;
            curr->next = list1.head_;
            list1.head_ = list1.head_->next;
            curr = curr->next;
            curr->next = temp;
        }
        else{
            curr = curr->next;
        }
    }
    return true;
}
    

template<class ItemType>
List342<ItemType> List342<ItemType>::operator+(const List342<ItemType> &list) const{
    List342<ItemType> listCopy = list;
    List342<ItemType> thisCopy = *this;
    thisCopy.Merge(listCopy);
    return *this;
}
 

template <class ItemType>
List342<ItemType>& List342<ItemType>::operator+=(const List342<ItemType> &list){
    List342<ItemType> listCopy;
    listCopy = list;
    Merge(listCopy);
    return *this;
}


template <class ItemType>
bool List342<ItemType>::operator==(const List342<ItemType> &list){
    Node *lhs, *rhs;
    lhs = head_;
    rhs = list.head_;
    if(this->isEmpty() && list.isEmpty())
        return true;
    while(lhs != nullptr && rhs != nullptr){
        if(lhs->next == nullptr && rhs->next == nullptr)
            return true;
        if((lhs->next != nullptr && rhs->next == nullptr) || (lhs->next == nullptr && rhs ->next != nullptr))
            return false;
        lhs = lhs->next;
        rhs = rhs->next;
    }
    return false;
}

template <class ItemType>
bool List342<ItemType>::operator!=(const List342<ItemType> &list){
    if(*this == list)
        return false;
    else
        return false;
}

template <class ItemType>
List342<ItemType>& List342<ItemType>::operator=(const List342<ItemType> &list){
    ItemType answer = *list.head_->data;
    ItemType result;
    while(Remove(answer, result));
    Node* s_node = nullptr;
    Node* ins_node = nullptr;
    
    if(list.head_ == nullptr)
        return *this;
    
    Node* d_node = new Node;
    d_node->data = (list.head_) ->data;
    head_ = d_node;
    s_node = list.head_->next;

    while(!(s_node == nullptr)){
        ins_node = new Node;
        ins_node->data = s_node->data;
        d_node->next = ins_node;
        d_node = d_node->next;
        s_node = s_node->next;
    }
    return *this;
}
 

template <class ItemType>
List342<ItemType>::~List342(){
    DeleteList();
};

