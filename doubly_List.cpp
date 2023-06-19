#include <iostream>
using namespace std;



#define ERR_NUMS        "The number of nodes is out of range !"
#define ERR_EMPTY       "List is empty !"
#define ERR_POS         "Position is out of range !"
#define ERR_DUPLICATED  "No conversion !"



struct node {
	node *pre;
	int data;
	node *next;
};

struct douList {
    int numOfNodes;
	node *head;
	node *tail;
};



node *createNode(int data) {
    node *temp = new node;
    temp->pre = NULL; 
    temp->data = data;
    temp->next = NULL; 
    return temp;
}



douList *addHead(douList *list, int data) {
	node *temp = new node;
	temp->pre = NULL;
	temp->data = data;
	temp->next = list->head;

	list->head->pre = temp;
	list->head = temp;

	return list;
}



douList *addTail(douList *list, int data) {
	node *temp = new node;
	temp->pre = list->tail;
	temp->data = data;
	temp->next = NULL;

	list->tail->next = temp;
	list->tail = temp;

	return list;
}



douList *createList(int n) {
	douList *list = new douList;
    list->numOfNodes = n;

    try {
        if (n < 1)
            throw ERR_NUMS;

        int data, i;
        for (i = 0; i < n; i++) {
            cout << "Enter data of node: ";
            cin >> data;
            if (i == 0) {
                list->head = createNode(data);
                list->tail = list->head;
            }
            else
                list = addTail(list, data);
        }
    }

    catch (char const *exc) {
        list->head = NULL;
        cout << exc << endl;
    }
    
	return list;
}



void printList(douList *list) {
	node *p = list->head;

    try {
        if (p == NULL)
            throw ERR_EMPTY;

        cout << "List includes " << list->numOfNodes;
        if (list->numOfNodes == 1)
            cout << " node: ";
        else
            cout << " nodes: ";

        while (p != NULL) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

    catch (char const *exc) {
        cout << exc << endl;
    }
}



douList *insertAt(douList *list, int pos, int data) {
    node *p = list->head;

    try {
        if (p == NULL)
            throw ERR_EMPTY;

        if (pos < 0 || pos > list->numOfNodes)
            throw ERR_POS;

        if (pos == 0) 
            list = addHead(list, data);
        else if (pos == list->numOfNodes)
            list = addTail(list, data);
        else if (pos > 0 && pos < list->numOfNodes) {
            node *temp = new node;          // inserted node

            for (int i = 1; i < pos; i++)   // previous node of inserted node
                p = p->next; 

            temp->pre = p;    
            temp->data = data;  
            temp->next = p->next;

            p->next->pre = temp;
            p->next = temp;
        } 

        list->numOfNodes++;
    }

    catch (char const *exc) {
        cout << exc << endl;
    }

    return list;
}



douList *deleteHead(douList *list) {
	node *oldHead = list->head;
    node *newHead = oldHead->next;
    
    if (list->numOfNodes != 1)
	    newHead->pre = NULL;
	list->head = newHead;

	delete(oldHead);
	return list;
}



douList *deleteTail(douList *list) {
	node *oldTail = list->tail;
	node *newTail = oldTail->pre;
	newTail->next = NULL;
	list->tail = newTail;

	delete(oldTail);
	return list;
}



douList *deleteAt(douList *list, int pos) {
    node *p = list->head;

    try {
        if (p == NULL)
            throw ERR_EMPTY;

        if (pos < 0 || pos >= list->numOfNodes)
            throw ERR_POS;

        if (pos == 0) 
            list = deleteHead(list);
        else if (pos == list->numOfNodes-1)
            list = deleteTail(list);
        else {
            node *temp = new node;
            for (int i = 1; i < pos; i++)    // previous node of deleted node
                p = p->next; 
            temp = p->next;
            p->next = temp->next;           
            temp->next->pre = p;
            delete(temp);
        } 

        list->numOfNodes--;
    }

    catch (char const *exc) {
        cout << exc << endl;
    }
    
    return list;
}



int main() {
    int n, pos, data, i, opt;
    douList *list;

    while (1) {
        cout << " -------------- MENU ------------- " << endl;
        cout << "0. Quit" << endl;
        cout << "1. Create list" << endl;
        cout << "2. Display list" << endl;
        cout << "3. Insert node" << endl;
        cout << "4. Delete node" << endl;
        cout << "Enter your option: ";
        cin >> opt;

        switch (opt)
        {
            case 0:
                return 0;
            case 1:
                cout << "Enter the number of nodes: ";
                cin >> n;
                list = createList(n);
                break;
            case 2:
                printList(list);
                break;
            case 3:
                cout << "Enter the position: ";
                cin >> pos;
                cout << "Enter data: ";
                cin >> data;
                list = insertAt(list, pos, data);
                break;
            case 4:
                cout << "Enter the position: ";
                cin >> pos;
                list = deleteAt(list, pos);
                break;
            default:
                cout << "Invalid option !" << endl;
                break;
        }
    }
    
    return 0;
}