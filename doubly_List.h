#include <bits/stdc++.h>

using namespace std;





/* --------------------------------------------------------- MACROES - START --------------------------------------------------------- */
#define ERR_EMPTY       "List is empty !"
#define ERR_VAL         "Value is invalid !"
#define ERR_DUPLICATED  "No conversion !"

/* --------------------------------------------------------- MACROES - END ----------------------------------------------------------- */





/* ----------------------------------------------------- DATA STRUCTS - START -------------------------------------------------------- */
struct node {
	node *pre;
	int data;
	node *next;

    node(int value = 0) {
        data = value;
        pre = next = NULL;
    }
};



struct douList {
    int numOfNodes;
	node *head;
	node *tail;
};
/* ----------------------------------------------------- DATA STRUCTS - END ---------------------------------------------------------- */





/* ------------------------------------------------------ PROTOTYPE - START ---------------------------------------------------------- */
/**
 * @brief add a new node at the head of the list
 * 
 * @param list 
 * @param data 
 */
void addHead(douList *&list, int data);



/**
 * @brief add a new node at the tail of the list
 * 
 * @param list 
 * @param data 
 */
void addTail(douList *&list, int data);



/**
 * @brief Create a List object
 * 
 * @param list 
 * @param nums - number of nodes
 * @param opt - select addHead (0) or addTail (1)
 */
void createList(douList *&list, int nums, int opt);



/**
 * @brief print all nodes of the list
 * 
 * @param list 
 */
void printList(douList *list);



/**
 * @brief insert a new node at any position in the list
 * 
 * @param list 
 * @param pos position is in range of [0 - sizeof(List)]
 * @param data 
 */
void insertAt(douList *&list, int pos, int data);



/**
 * @brief delete node at the head of the list
 * 
 * @param list 
 */
void deleteHead(douList *&list);



/**
 * @brief delele node at the tail of the list
 * 
 * @param list 
 */
void deleteTail(douList *&list);



/**
 * @brief delete node at any position in the list
 * 
 * @param list 
 * @param pos position is in range of [0 - sizeof(List)-1]
 */
void deleteAt(douList *&list, int pos);
/* ------------------------------------------------------- PROTOTYPE - END ----------------------------------------------------------- */





/* --------------------------------------------------------- FUNCTIONS - START ------------------------------------------------------- */
void addHead(douList *&list, int data) 
{
	node *temp = new node(data);
	temp->next = list->head;

	list->head->pre = temp;
	list->head = temp;
}



void addTail(douList *&list, int data) 
{
	node *temp = new node(data);
	temp->pre = list->tail;

	list->tail->next = temp;
	list->tail = temp;
}



void createList(douList *&list, int nums, int opt) 
{
    try {
        if (nums < 1)
            throw ERR_VAL;

        if (opt != 0 && opt != 1)
            throw ERR_VAL;

        list = new douList;
        list->numOfNodes = nums;

        int data, i;
        for (i = 0; i < nums; i++) {
            cout << "Enter data of node: ";
            cin >> data;

            if (i == 0) {
                list->head = new node(data);
                list->tail = list->head;
            }
            else {
                if (opt)
                    addTail(list, data);
                else
                    addHead(list, data);
            }            
        }
    }

    catch (char const *exc) {
        cout << exc << endl;
    }
}



void printList(douList *list) 
{
    try {
        if (list == NULL)
            throw ERR_EMPTY;

        node *p = list->head;

        cout << "List includes " << list->numOfNodes << (list->numOfNodes == 1 ? " node: " : " nodes: ");

        while (p != NULL) {
            cout << p->data << " ";
            p = p->next;
        }
    }

    catch (char const *exc) {
        cout << exc << endl;
    }
}



void insertAt(douList *&list, int pos, int data) 
{
    try {
        if (list == NULL)
            throw ERR_EMPTY;

        if (pos < 0 || pos > list->numOfNodes)
            throw ERR_VAL;

        node *p = list->head;

        if (pos == 0) 
            addHead(list, data);
        else if (pos == list->numOfNodes)
            addTail(list, data);
        else {
            node *temp = new node(data);    // inserted node

            for (int i = 1; i < pos; i++)   // previous node of inserted node
                p = p->next; 

            temp->pre = p;     
            temp->next = p->next;

            p->next->pre = temp;
            p->next = temp;
        } 

        list->numOfNodes++;
    }

    catch (char const *exc) {
        cout << exc << endl;
    }
}



void deleteHead(douList *&list) 
{
	node *oldHead = list->head;
    node *newHead = oldHead->next;
    if (list->numOfNodes != 1) 
	    newHead->pre = NULL;
	list->head = newHead;
	delete oldHead;
}



void deleteTail(douList *&list) 
{
	node *oldTail = list->tail;
	node *newTail = oldTail->pre;
	newTail->next = NULL;
	list->tail = newTail;
	delete oldTail;
}



void deleteAt(douList *&list, int pos)
{
    try {
        if (list == NULL)
            throw ERR_EMPTY;

        if (pos < 0 || pos >= list->numOfNodes)
            throw ERR_VAL;

        node *p = list->head;

        if (pos == 0) 
            deleteHead(list);
        else if (pos == list->numOfNodes-1)
            deleteTail(list);
        else {
            node *temp = new node();
            for (int i = 1; i < pos; i++)    // previous node of deleted node
                p = p->next; 

            temp = p->next;
            p->next = temp->next;           
            temp->next->pre = p;
            delete temp;
        } 

        list->numOfNodes--;
        if (list->numOfNodes == 0)
            list = NULL;
    }

    catch (char const *exc) {
        cout << exc << endl;
    }
}
/* --------------------------------------------------------- FUNCTIONS - END ------------------------------------------------------- */