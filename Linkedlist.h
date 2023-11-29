#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

using namespace std;

struct ListNode {
    string name;
    int total_tickets;
    ListNode* next;

    ListNode(const string& name, int total_tickets) : next(nullptr) {}
};

class LinkedList {
    public:
        ListNode* head;
        LinkedList() : head(nullptr) {}
        void insert(const string& name, int total_tickets);
        void display_total_tickets();
};

#endif