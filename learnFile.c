#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct date
{
    short day;
    short month;
    short year;
}Date;

typedef struct student
{
    char name[30];
    char id[30];
    Date birthdate;
    float mark;
}Student;

typedef struct node
{
    Student data;
    struct node* pNext;
}Node;

typedef struct list
{
    Node* pHead;
    Node* pTail;
}List;

//Init new List and new Node
void InitList(List* list);  //Init list defaul NULL
Node* InitNode(const Student student);  //Init pointer node with data is student

//Add node in list the firt and the end
void AddNodeHead(List* list, Node* node);   //Add Node into list with location the firt list
void AddNodeTail(List* list, Node* node);   //Add Node into list with location the end of list

//Read infor one student and read all student from file 
bool ReadDataFile(FILE* file,Student* student); //Read data one student from file
void ReadFiles(FILE* file, List* list); //Read data all students from file and add in list
//Write infor one student and write all student into file 
void WriteDataFile(FILE* file, Student* student);   //Write data one student out file
void WriteFile(FILE* file, List list);  //Write all data students in list out to file

//Write file infor students top mediummark
void WriteStudentBetter(FILE* file,List list);  //Write data student have mediummark better out file

//Display <printf> infor student for list
void DisplayStudent(const Student student); //Display one student
void DisplayList(const List list);  //Display all student in list

//Function handing student from list
Student InitStudent();  // Init data by student
void AddNodeStudent(List* list,const short style);   //Add node with data is student in to list ( 0: Tail, 1:Head, ...)
void SwapStudent(Student* student1, Student* student2); //Swap between two student
void InterchangeSort(const List list);  //Sort node in list by mediummark increate
void SearchStudentID(const List list);  //Search student in list by ID
void SearchStudentName(const List list);    //Search students in list by name ( uppercase or lowcase)
char* SubNameStudent(const char* source);   //Substring from string source and return string name
int CompareString(const char *str1, const char *str2); //Compare two string str1 and str2, return 0 (equal), -1(str1 less than str2), 1(str1 greater than str2)

//FUnction menu
void MenuUI(FILE* file, List* list);

//Free data and pointer for list
void FreeList(List* list);

int main()
{
   FILE *file;
   List list;
   
   InitList(&list);

   ReadFiles(file,&list);
   
   MenuUI(file,&list);
   
   //AddNodeStudent(&list,0);
   //while ( getchar() != '\n' );
   //AddNodeStudent(&list,1);
   //DisplayList(list);
   
   
        
   
   FreeList(&list);
   return 0;
}

//Function Node
void InitList(List* list)
{
    list->pHead = NULL;
    list->pTail = NULL;
}
Node* InitNode(const Student student)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL)
        return NULL;
    node->data = student;
    node->pNext = NULL;
    return node;
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

//Function work to file and list, student
bool ReadDataFile(FILE* file, Student* student)
{
    char data[50];
    char* buffer;
    if(fgets(data, sizeof(data), file) == NULL)
        return false;
    
    buffer = strtok(data,",");
    strcpy(student->name,buffer);
    buffer = strtok(NULL,",");
    buffer = strstr(buffer,"U");
    strcpy(student->id,buffer);
    buffer = strtok(NULL,"/");
    student->birthdate.day = strtol(buffer,NULL,2);
    buffer = strtok(NULL,"/");
    student->birthdate.month = strtol(buffer,NULL,2);
    buffer = strtok(NULL,",");
    student->birthdate.year = strtol(buffer,NULL,4);
    buffer = strtok(NULL,",");
    student->mark = strtof(buffer,NULL);
    
    return true;
}

void ReadFiles(FILE* file, List* list)
{
    Student student;
    Node* node = NULL;
    
    file = fopen("student.txt","r");
    if(file == NULL) 
    {
        printf("Dont't open file!\n");
        return;
    }
    
    while(ReadDataFile(file,&student))
    {
        node = InitNode(student);
        AddNodeTail(list, node);
    }
    fclose(file);
    node = NULL;
    free(node);
}

void WriteDataFile(FILE* file, Student* student)
{
    fprintf(file,"%s, ",student->name);
    fprintf(file,"%s, ",student->id);
    fprintf(file,"%hd/%hd/%hd, ",student->birthdate.day,student->birthdate.month,student->birthdate.year);
    fprintf(file,"%0.2f",student->mark);
}
void WriteFile(FILE* file, List list)
{
    Node* node = NULL;
    file = fopen("increatemark.txt","w");
    if(file == NULL) 
    {
        printf("Don't open file!\n");
        return;
    }
    
    InterchangeSort(list);
    for(node = list.pHead; node != NULL; node = node->pNext)
    {
        WriteDataFile(file,&node->data);
        fprintf(file,"\n");
    }
    node = NULL;
    free(node);
    fclose(file);
}

void WriteStudentBetter(FILE* file,List list)
{
    Node* node = NULL;
    float maxmark;
    
    file = fopen("maxmark.txt","w");
    if(file == NULL) 
    {
        printf("Don't open file!\n");
        return;
    }
    
    maxmark = list.pHead->data.mark;
    
    for(node = list.pHead->pNext; node != NULL; node = node->pNext)
    {
        if(node->data.mark > maxmark)
            maxmark = node->data.mark;
    }
    
    for(node = list.pHead; node != NULL; node = node->pNext)
    {
        if(node->data.mark == maxmark)
        {
            WriteDataFile(file,&node->data);
            fprintf(file,"\n");
        }
    }
    
    node = NULL;
    free(node);
    fclose(file);
}

//Function display ( printf)
void DisplayStudent(const Student student)
{
    printf("Name: %s\n",student.name);
    printf("Id: %s\n",student.id);
    printf("Date: %hd/%hd/%hd\n",student.birthdate.day,student.birthdate.month,student.birthdate.year);
    printf("Mark: %0.2f\n",student.mark);
}

void DisplayList(const List list)
{
    Node* node = NULL;
    for(node = list.pHead; node != NULL; node = node->pNext)
    {
        DisplayStudent(node->data);
        printf("\n");
    }
    node = NULL;
    free(node);
}

//Function Student
Student InitStudent()
{
    Student student;
    
    fflush(stdin);
    printf("Input name: ");
    fgets(student.name,sizeof(student.name),stdin);
    student.name[strlen(student.name)-1] = '\0';
    printf("Input ID: ");
    fgets(student.id,sizeof(student.id),stdin);
    student.id[strlen(student.id)-1] = '\0';
    printf("Input birthday(day): ");
    scanf("%hd",&student.birthdate.day);
    printf("Input birthday(month): ");
    scanf("%hd",&student.birthdate.month);
    printf("Input birthday(year): ");
    scanf("%hd",&student.birthdate.year);
    printf("Input mediummark(score): ");
    scanf("%f",&student.mark);
    
    return student;
}

void AddNodeStudent(List* list,const short style)
{
    Student student;
    
    student = InitStudent();
    Node* node = InitNode(student);
    switch(style)
    {
     case 0:
        AddNodeHead(list, node);
        break;
     case 1:
        AddNodeTail(list, node);
        break;
     default:
        break;
    }
    
    node = NULL;
    free(node);
}

void SwapStudent(Student* student1, Student* student2)
{
    Student sts;
    //swap name
    strcpy(sts.name,student1->name);
    strcpy(student1->name,student2->name);
    strcpy(student2->name,sts.name);
    //swap id
    strcpy(sts.id,student1->id);
    strcpy(student1->id,student2->id);
    strcpy(student2->id,sts.id);
    //Swap birthdate
    sts.birthdate = student1->birthdate;
    student1->birthdate = student2->birthdate;
    student2->birthdate = sts.birthdate;
    //Swap mark
    sts.mark = student1->mark;
    student1->mark = student2->mark;
    student2->mark = sts.mark;
}
void InterchangeSort(const List list)
{
    Node* node1 = NULL;
    Node* node2 = NULL;
    for(node1 = list.pHead; node1 != NULL; node1 = node1->pNext)
    {
        for(node2 = node1->pNext; node2 != NULL; node2 = node2->pNext)
        {
            if(node1->data.mark > node2->data.mark)
            {
                SwapStudent(&node1->data,&node2->data);
            }
        }
    }
    node1 = NULL;
    node2 = NULL;
    free(node1);
    free(node2);
}

void SearchStudentID(const List list)
{
    Node* node = NULL;
    char id[30];
    printf("Input student ID search: ");
    
    fflush(stdin);
    fgets(id,sizeof(id),stdin);
    id[strlen(id)-1] = '\0';
    
    for(node = list.pHead; node != NULL; node = node->pNext)
    {
        if(CompareString(id,node->data.id) == 0)
        {
            DisplayStudent(node->data);
            break;
        }
    }
    node = NULL;
    free(node);
}

void SearchStudentName(const List list)
{
    Node* node = NULL;
    char name[30];
    char* temple;
    
    fflush(stdin);
    printf("Input student name search: ");
    fgets(name,sizeof(name),stdin);
    name[strlen(name)-1] = '\0';
    
    for(node = list.pHead; node != NULL; node = node->pNext)
    {
        temple = SubNameStudent((char*)node->data.name);
        if(CompareString(name,temple) == 0)
        {
            DisplayStudent(node->data);
            printf("\n");
        }
    }
    
    node = NULL;
    free(node);
}

char* SubNameStudent(const char* source)
{
    char* destination;
    int index;
       
    for(index = strlen(source) -1; index >= 0; index--)
    {
        if(source[index] == ' ')
            break;
    }
   
    destination = (char*)malloc(sizeof(char) * (strlen(source) - index));
    strncpy(destination, (source + index +1), (strlen(source) - index));
    
    return destination;
}

int CompareString(const char *str1, const char *str2)
{
    int size_str1, size_str2;
    
    size_str1 = strlen(str1);
    size_str2 = strlen(str2);
    
    if((size_str1 == size_str2) || (size_str1 > size_str2))
    {
        for(int i = 0, j = 0 ; str1[i]!='\0'; i++)
        {
            if(str1[i] - str2[i] == 32 || str1[i] - str2[i] == -32 || str1[i] - str2[i] == 0)
                j++;
            else if(str1[i]<str2[i])
                return -1; //The string str1 is lesser than str2
            else
                return 1; //The string str1 is greater than str2
        }
    }
    else
    {
        for(int i = 0, j = 0; str2[i]!='\0'; i++)
        {
            if(str1[i] - str2[i] == 32 || str1[i] - str2[i] == -32 || str1[i] - str2[i] == 0)
                j++;
            else if(str1[i]<str2[i])
                return -1; //The string str1 is lesser than str2
            else 
                return 1; //The string str1 is greater than str2
        }
    }
    
    return 0; // the string str1 and str2 are same
}

//Function Menu
void MenuUI(FILE* file, List* list)
{
    bool isFlag = true;
    short choose;
    
    while(isFlag)
    {
        system("clear");
        printf("\t\t====== MENU ======\n");
        printf("\t\t1. Add student Head\n");
        printf("\t\t2. Add student Tail\n");
        printf("\t\t3. Add stuent After [error]\n");
        printf("\t\t4. Add student Before [error]\n");
        printf("\t\t5. Write student increate mark out file\n");
        printf("\t\t6. Write students have mediummark better out file\n");
        printf("\t\t7. Search student by ID\n");
        printf("\t\t8. Search student by Name\n");
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
            while ( getchar() != '\n' );
            AddNodeStudent(list,0);
            break;
        case 2:
            while ( getchar() != '\n' );
            AddNodeStudent(list,1);
            break;
        case 3:
            while ( getchar() != '\n' );
            AddNodeStudent(list,0);
            break;
        case 4:
            
            break;
        case 5:
            WriteFile(file,*list);
            break;
        case 6:
            WriteStudentBetter(file,*list);
            break;
        case 7:
            while ( getchar() != '\n' );
            SearchStudentID(*list);
            getchar();
            break;
        case 8:
            while ( getchar() != '\n' );
            SearchStudentName(*list);
            getchar();
            break;
        case 9:
            DisplayList(*list);
            while(getchar() != '\n');
            getchar();
            break;
        }
    }
}


//free list
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

