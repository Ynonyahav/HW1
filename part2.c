#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct node_t {
    int val;
    struct node_t *next;
} *Node;

/**
 *  isListSorted: checks if a given list is sorted in ascending order.
 * @return
 *  true if the list is sorted, false otherwise.
*/ 
bool isListSorted(Node list);
/**
 *  mergeSortedLists: merges two sorted lists into a single sorted list.
 * @return a new list containing all the elements of list1 and list2, sorted in ascending order.
*/
Node mergeSortedLists(Node list1, Node list2);

Node createNode(int value, Node next) {
    Node node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->val = value;
    node->next = next;
    return node;
}

int main() {
    Node list1 = createNode(1, createNode(3, createNode(5, NULL)));
    Node list2 = createNode(2, createNode(4, createNode(6, NULL)));
    Node merged_list = mergeSortedLists(list1, list2);
    Node current_node = merged_list;
    while (current_node != NULL) {
        printf("%d\n", current_node->val);
        current_node = current_node->next;
    }
    return 0;
}

int main(){
    Node list1=malloc(sizeof(list1));
    Node list2=malloc(sizeof(list2));
    list1->val=1;
    list1->next=malloc(sizeof(list1));
    list1->next->val=3;
    list1->next->next=malloc(sizeof(list1));
    list1->next->next->val=5;
    list1->next->next->next=NULL;
    list2->val=2;
    list2->next=malloc(sizeof(list2));
    list2->next->val=4;
    list2->next->next=malloc(sizeof(list2));
    list2->next->next->val=6;
    list2->next->next->next=NULL;
    Node merged_list=mergeSortedLists(list1,list2);
    Node current_node=merged_list;
    while(current_node!=NULL){
        printf("%d\n",current_node->val);
        current_node=current_node->next;
    }
    return 0;
}

bool isListSorted(Node list)
{
    if(list==NULL){
        return true;
    }
    Node current_node=list;
    while(current_node->next!=NULL){
        if(current_node->val>(current_node->next)->val){
            return false;
        }
        current_node=current_node->next;
    }
    return true;
}


Node mergeSortedLists(Node list1, Node list2)
{
    if((list1==NULL)&&(list2==NULL)){
        return NULL;
    }
    if(list1==NULL){
        return list2;
    }
    if(list2==NULL){
        return list1;
    }
    Node merged_list;
    if((list1->val)<(list2->val)){
        merged_list=list1;
        list1=list1->next;
    }
    else{
        merged_list=list2;
        list2=list2->next;
    }
    Node current_node=merged_list;
    while((list1!=NULL)&&(list2!=NULL)){
        if((list1->val)<(list2->val)){
            current_node->next=list1;
            list1=list1->next;
        }
        else{
            current_node->next=list2;
            list2=list2->next;
        }
        current_node=current_node->next;
    }
    if(list1==NULL){
        current_node->next=list2;
    }
    else{
        current_node->next=list1;
    }
    return merged_list;
}

