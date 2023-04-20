#include <iostream>
#include <fstream>
using namespace std;
#include "unordered_list.h"
#include "Timer.h"

int UnorderedArrayList::find_index(const string & word){
    for (int i = 0; i < size; ++i){
        if (buf[i] == word){
            return i;
        }
    }
    return -1;
}
UnorderedArrayList::UnorderedArrayList(int max_len) : UnorderedList("UnorderedArrayList"){
    buf = new string[max_len];
    size = 0;
    capacity = max_len;
}
void UnorderedArrayList::insert(const string & word){
    if (size < capacity){
        buf[size] = word;
        ++size;
    }
}
bool UnorderedArrayList::find(const string & word){
    int location = find_index(word);
    if (buf[location] == word){
        return true;
    }
    else{
        return false;
    }
}
void UnorderedArrayList::remove(const string & word){
    int location = find_index(word);
    if (location != 1){
        for (int i = location; i < size-1; ++i){
            buf[i] = buf[i + 1];
        }
        --size;
    }
}
bool UnorderedArrayList::is_empty(){
    if (size == 0){
        return true;
    }
    else{
        return false;
    }
}
bool UnorderedArrayList::is_full(){
    if (size == capacity){
        return true;
    }
    else{
        return false;
    }
}
void UnorderedArrayList::erase(){
    size = 0;
}
void UnorderedArrayList::print(ostream & out){
    for (int i = 0; i < size; ++i){
        out << buf[i] << endl;
    }
}
UnorderedArrayList::~UnorderedArrayList(){
    delete [] buf;
}

void ListNode::print(ostream & out, ListNode * L){
    ListNode* current = L;
    while (current != nullptr){
        out << current->data << endl;
        current = current->next;
    }
}
ListNode * ListNode::find(const string & word, ListNode * L){
    ListNode* current_L = L;
    string current_word = word;
    while (current_L != nullptr){
        if (current_L->data == current_word){
            return current_L;
        }
        current_L = current_L->next;
    }
    return nullptr;
}
void ListNode::delete_list(ListNode * L){
    ListNode* current = L;
    ListNode* tmp;
    while (current != nullptr){
        tmp = current->next;
        delete current;
        current = tmp;
    }
}
void ListNode::remove(const string & word, ListNode * & L){ //review this when sober
    //use find to find word then remove from L, so delete from L
    ListNode* current = L;
    while (current != nullptr){
        if (current->next->data == word){
            ListNode* tmp = current->next;
            current->next = current->next->next;
            delete tmp;
        }
    }
}

UnorderedLinkedList::UnorderedLinkedList() : UnorderedList("UnorderedLinkedList"){
    head = nullptr;
}
void UnorderedLinkedList::insert(const string & word){
    head = new ListNode(word, head);
}
bool UnorderedLinkedList::find(const string & word){
    if (ListNode::find(word, head) != nullptr){
        return true;
    }
    else{
        return false;
    }
}
void UnorderedLinkedList::remove(const string & word){
    ListNode::remove(word, head);
}
bool UnorderedLinkedList::is_empty(){
    if (head == nullptr){
        return true;
    }
    else{
        return false;
    }
}
bool UnorderedLinkedList::is_full(){
    int counter;
    for (ListNode* current = head; current != nullptr; current = current->next){
        ++counter;
    }
    if (counter == NWORDS){
        return true;
    }
    else{
        return false;
    }
}
void UnorderedLinkedList::erase(){
    ListNode::delete_list(head);
    head = nullptr;
}
void UnorderedLinkedList::print(ostream & out){
    ListNode::print(out, head);
}
UnorderedLinkedList::~UnorderedLinkedList(){
    ListNode::delete_list(head);
}

ostream & operator << (ostream & out, UnorderedList & L){
    L.print(out);
    return out;
}

void error(string word, string msg){
    cout << word << msg << endl;
} 
void insert_all_words(int k, string file_name, UnorderedList & L){ //?
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
        L.insert(word);
        t.elapsedUserTime(eTime);
        in.close();
        cout << "\t\tI = " << eTime << endl;
}
void find_all_words(int k, string file_name, UnorderedList & L){
    //same thing but with find?
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
        L.find(word);
        t.elapsedUserTime(eTime);
        in.close();
        cout << "\t\tI = " << eTime << endl;
}
void remove_all_words(int k, string file_name, UnorderedList & L){
    //same thing but with remove
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
        L.remove(word);
        t.elapsedUserTime(eTime);
        in.close();
        cout << "\t\tI = " << eTime << endl;
}
void measure_UnorderedList_methods(string file_name, UnorderedList & L){
    cout << L.name << endl;
    for (int K=1; K<=10; ++K){
        cout << "\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        find_all_words(K, file_name, L);
        remove_all_words(K, file_name, L);
        if (!L.is_empty())
            error(L.name, "is not empty");
    }
}
void measure_lists(string input_file){
    UnorderedArrayList UAL(NWORDS);
    measure_UnorderedList_methods(input_file, UAL);
    UnorderedLinkedList ULL;
    measure_UnorderedList_methods(input_file, ULL);
} //?

//this is not the optimal ver, just make it work first and then think abt how to optimize