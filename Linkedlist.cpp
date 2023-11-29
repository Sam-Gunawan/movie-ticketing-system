#include "Linkedlist.h"
#include <iostream>

using namespace std;


void LinkedList::insert(const string& name, int total_tickets) {
    ListNode* newNode = new ListNode(name, total_tickets);
    if (!head || total_tickets > head->total_tickets) {
        newNode->next = head;
        head = newNode;
    } else {
        ListNode* current = head;
        while (current->next && total_tickets <= current->next->total_tickets) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void LinkedList::display_total_tickets() {
    ListNode* current = head;
    while (current) {
        cout << current->name << ": " << current->total_tickets << " tickets\n";
        current = current->next;
    }
}