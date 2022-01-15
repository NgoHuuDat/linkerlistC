#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data; //Data my node
    struct node* pNext; //Pointer Node save address node next
}Node;

typedef struct list
{
    Node* pHead; //Pointer Node save address node the firt
    Node* pTail; //Poaiter Node save address node the end
}List;

void InitList(List* list);
Node* InitNode(int data);

void AddNodeHead(List* list, Node* node);
void AddNodeTail(List* list, Node* node);
void AddNodeByAfter(List* list, Node* node);
void AddNodeByBefore(List* list, Node* node);
void AddNodeLocation(List* list,Node* node,short location,short size);

void DelNodeHead(List* list);
void DelNodeTail(List* list);
void DelNode(List* list);

void DisplayList(List list);
void FreeList(List* list);

int main()
{
    List list;
    Node* nodeA = NULL;
    int data;
    short location,size,choose;
    char temple;
    bool isFlag = true;
    InitList(&list);
    
    size = 0;
    location = 0;
    
    while(isFlag)
    {
        system("clear");
        printf("\t\t====== MENU ======\n");
        printf("\t\t1. Add Node Head\n");
        printf("\t\t2. Add Node Tail\n");
        printf("\t\t3. Add Node After\n");
        printf("\t\t4. Add Node Before\n");
        printf("\t\t5. Add Node By Location\n");
        printf("\t\t6. Delete Node Head\n");
        printf("\t\t7. Delete Node Tail\n");
        printf("\t\t8. Delete Node something\n");
        printf("\t\t9. Display List\n");
        printf("\t\t0. Exit\n\n");
        
        printf("Input Choose: ");
        scanf("%hd",&choose);
        switch(choose)
        {
        case 0:
            isFlag = false;
            break;
        case 1:
            printf("Nhap data: ");
            scanf("%d",&data);
            size++;
            AddNodeHead(&list,InitNode(data));
            break;
        case 2:
            printf("Nhap data: ");
            scanf("%d",&data);
            size++;
            AddNodeTail(&list,InitNode(data));
            break;
        case 3:
            printf("Nhap data: ");
            scanf("%d",&data);
            size++;
            nodeA = InitNode(data);
            AddNodeByAfter(&list,nodeA);
            break;
        case 4:
            printf("Nhap data: ");
            scanf("%d",&data);
            size++;
            nodeA = InitNode(data);
            AddNodeByBefore(&list,nodeA);
            break;
        case 5:
            printf("Nhap data: ");
            scanf("%d",&data);
            printf("Nhap location: ");
            scanf("%hd",&location);
            Node* nodeA = InitNode(data);
            AddNodeLocation(&list,nodeA,location,size);
            size++;
            break;
        case 6:
            DelNodeHead(&list);
            size--;
            break;
        case 7:
            DelNodeTail(&list);
            size--;
            break;
        case 8:
            DelNode(&list);
            size--;
            break;
        case 9:
            DisplayList(list);
            while(getchar() != '\n');
            getchar();
            break;
        }
    }
    
    nodeA = NULL;
    free(nodeA); 
    FreeList(&list);
    return 0;
}

void InitList(List* list)
{
    list->pHead = NULL;
    list->pTail = NULL;
}

Node* InitNode(int data)
{
    Node* ptr = (Node*)malloc(sizeof(Node));
    if(ptr == NULL)
        return NULL;
    ptr->data = data;
    ptr->pNext = NULL;
    return ptr;
}

void AddNodeHead(List* list, Node* node)
{
    if(list->pHead == NULL)
        list->pHead = list->pTail = node;
    else
    {
        node->pNext = list->pHead;
        list->pHead = node;
    }
}

void AddNodeTail(List* list, Node* node)
{
    if(list->pHead == NULL)
        list->pHead = list->pTail = node;
    else
    {
        list->pTail->pNext = node;
        list->pTail = node;
    }
}

void AddNodeByAfter(List* list, Node* node)
{
    int data;
    printf("Nhap node: ");
    scanf("%d",&data);
   
    if(data == list->pHead->data && list->pHead->pNext == NULL)
        AddNodeTail(list,node);
    else
    {
        Node* k = NULL;
        for(k = list->pHead; k!=NULL;k = k->pNext)
        {
            if(data == k->data)
            {
                Node* temp = InitNode(node->data);
                Node* ptr = k->pNext;
                temp->pNext = ptr;
                k->pNext = temp;
            }
        }
        k = NULL;
        free(k);
    }
}

void AddNodeByBefore(List* list, Node* node)
{
    int data;
    printf("Nhap node: ");
    scanf("%d",&data);
   
    if(data == list->pHead->data && list->pHead->pNext == NULL)
        AddNodeHead(list,node);
    else
    {
        Node* ptr = NULL;
        Node* k = NULL;
        for(k = list->pHead; k!=NULL;k = k->pNext)
        {
            if(data == k->data)
            {
                Node* temp = InitNode(node->data);
                temp->pNext = k;
                ptr->pNext = temp;
            }
            ptr = k;
        }
        ptr = NULL;
        k = NULL;
        free(ptr);
        free(k);
    }
}

void AddNodeLocation(List* list,Node* node,short location,short size)
{
    if(list->pHead == NULL || location == 1)
    {
        AddNodeHead(list,node);
        return;
    }
    if(location == size +1)
    {
        AddNodeTail(list,node);
        return;
    }
    Node* ptr = NULL;
    Node* k = NULL;
    short index = 0;
    for(k = list->pHead; k!=NULL;k = k->pNext)
    {
        index++;
        if(location == index)
        {
            Node* temp = InitNode(node->data);
            temp->pNext = k;
            ptr->pNext = temp;
            break;
        }
        ptr = k;
    }
    k = NULL;
    ptr = NULL;
    free(k);
    free(ptr);
}

void DelNodeHead(List* list)
{
    if(list->pHead == NULL)
        return;
    Node* node = list->pHead;
    list->pHead = list->pHead->pNext;
    free(node);
}

void DelNodeTail(List* list)
{
    if(list->pHead == NULL)
        return;
    if(list->pHead->pNext == NULL)
    {
        DelNodeHead(list);
        return;
    }
    
    for(Node* node = list->pHead; node != NULL; node = node->pNext)
    {
        if(node->pNext == list->pTail)
        {
            free(list->pTail);
            node->pNext = NULL;
            list->pTail = node;
            return;
        }
    }
}

void DelNode(List* list)
{
    int data;
    printf("Nhap node: ");
    scanf("%d",&data);
    if(list->pHead == NULL)
        return;
    if(list->pHead->data == data)
    {
        DelNodeHead(list);
        return;
    }
    if(list->pTail->data == data)
    {
        DelNodeTail(list);
        return;
    }
    Node* ptr = NULL;
    for(Node* k = list->pHead; k!=NULL;k = k->pNext)
    {
        if(data == k->data)
        {
            Node* temp = k->pNext;
            ptr->pNext = temp;
            free(k);
            return;
        }
        ptr = k;
    }
}

void DisplayList(List list)
{
    Node* node = NULL;
    for(node = list.pHead; node != NULL; node = node->pNext)
    {
        printf("%d\t",node->data);
    }
    printf("\n");
    node = NULL;
    free(node);
}

void FreeList(List* list)
{
    Node* node = NULL;
    while(list->pHead != NULL)
    {
        node = list->pHead;
        list->pHead = list->pHead->pNext;
        free(node);
    }
}
