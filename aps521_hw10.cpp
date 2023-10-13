#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Employee {
    int ID;
    double rate, hoursWorked, totalPay;
    string name;
    public:
        Employee(){
            name = "Unknown";
            ID = -1;
            rate = 0.00;
            hoursWorked = 0.0;
            totalPay = 0.0;
        }
        Employee(int i, double r, string n){
            name = n;
            ID = i;
            rate = r;
            hoursWorked = 0.0;
            totalPay = 0.0;
        }
        string getName() { return name; }
        int getID() { return ID; }
        double getRate() { return rate; }
        double getHours() { return hoursWorked; }
        double getTotalPay() { return totalPay; }
        void calcTotalPay() { totalPay = (hoursWorked * rate); }
        void setHours(double num) { hoursWorked = num; }
        void addHours(double num) { hoursWorked += num; }
};

class Node {
    Employee e; //stores data
    Node* nextNode; //stores pointer to next link
    Node* prevNode;
    public:
        Node(){
            nextNode = nullptr;
            prevNode = nullptr;
        }
        Node(Employee newEmp){
            e = newEmp;
            nextNode = nullptr;
            prevNode = nullptr;
        }
        void setE(Employee emp) { e = emp; }
        void setNext(Node* ne) { nextNode = ne; }
        void setPrev(Node* pre) { prevNode = pre; }
        Employee* getE() { Employee* ePtr = &e; return ePtr; }
        Node* getNextNode() { return nextNode; }
        Node* getPrevNode() { return prevNode; }
        void Nodeclear();
};

void Node::Nodeclear() {
    if (getNextNode() == nullptr){
        return;
    }else{
        getNextNode()->Nodeclear();
        delete getNextNode();
    }
}

class LList {
    Node* head;
    Node* tail;
    Node* current;
    public:
        LList(){
            head = nullptr;
            tail = nullptr;
            current = nullptr;
        }
        bool isEmpty() { return (head == nullptr); }
        void setHead(Node* h) { head = h; }
        void setTail(Node* t) { tail = t; }
        void setCurrent(Node* c) { current = c; }
        Node* getHead() { return head; }
        Node* getTail() { return tail; }
        Node* getCurrent() { return current; }
        void next();
        void addNode(Employee newNodeData);
        void insertNode(Employee newNodeData, Node* nextNode);
        void clear();
};

void LList::next(){
    if (getCurrent()->getNextNode() == nullptr){//if last in the list
        setCurrent(getHead());
        return;
    }
    setCurrent(getCurrent()->getNextNode());
}

void LList::addNode(Employee newNodeData){
    Node* temp = new Node();
    temp->setE(newNodeData);
    if (isEmpty()){
        setHead(temp);
        setCurrent(temp);
    }else{
        getTail()->setNext(temp);
        temp->setPrev(getTail());
    }
    setTail(temp);
}

void LList::insertNode(Employee newNodeData, Node* nextNode){
    Node* temp = new Node();
    temp->setE(newNodeData);
    Node* tempComesAfter = nextNode->getPrevNode();
    if (tempComesAfter == nullptr){//if temp is first
        setHead(temp);
    }else{//if temp is not first
        tempComesAfter->setNext(temp);//sets next on the node before nextNode to temp
        temp->setPrev(tempComesAfter);//sets prevNode on temp to whatever came before nextNode
    }
    temp->setNext(nextNode);
    nextNode->setPrev(temp);
}

void LList::clear(){
    getHead()->Nodeclear();
    delete getHead();
    setHead(nullptr);
    setTail(nullptr);
}

void openFile(ifstream& inFile, string message);
void printPayroll(LList* sortedList);

Employee* CE(LList* li){ //CurrentEmployee
    return li->getCurrent()->getE();
}

Node* CN(LList* li){ //CurrentNext
    return li->getCurrent()->getNextNode();
}

int main(){
    ifstream inFile;
    openFile(inFile, "ENTER FIRST (EMPLOYEE INFO) FILE NAME: ");

    LList* list = new LList();

    int tempID;
    double tempRate;
    string tempName;
    while (inFile>>tempID){
        inFile>>tempRate;
        getline(inFile, tempName);
        Employee tempEmp(tempID, tempRate, tempName);
        list->addNode(tempEmp);
    }
    inFile.close();

    //read hourly data off of hours file
    openFile(inFile, "ENTER SECOND (WAGE INFO) FILE NAME: ");//inFIle is now hours.txt
    double tempHours;
    while(inFile>>tempID){
        inFile>>tempHours;
        while (CE(list)->getID() != tempID){
            list->next();
        }
        CE(list)->addHours(tempHours * 1.0);
        CE(list)->calcTotalPay();
    }
    inFile.close();

    LList* sortedList = new LList();
    Employee* firstListNode = list->getHead()->getE();//returns employee data at head
    sortedList->addNode(*firstListNode);//adds first node to sortedList so we can start using insertNode()
    list->setCurrent(list->getHead());//reset to top
    list->next();//we already added the first node to the sortedList so we can skip

    while (true){
        double nodePay = CE(list)->getTotalPay();
        sortedList->setCurrent(sortedList->getHead());//reset to top
        double sortedNodePay = CE(sortedList)->getTotalPay();
        while (nodePay < sortedNodePay && CN(sortedList) != nullptr){//iterate thru sorted list
            sortedList->next();
            sortedNodePay = CE(sortedList)->getTotalPay();
        }
        if (nodePay >= sortedNodePay){
            sortedList->insertNode(*CE(list), sortedList->getCurrent());
        }else{
            sortedList->addNode(*CE(list));
        }
        if (CN(list) == nullptr){
            break;
        }
        list->next();
    }
    printPayroll(sortedList);

    sortedList->clear();
    delete sortedList;
    list->clear();
    delete list;

    return 0;
}

void openFile(ifstream& inFile, string message){
    string fileName;
    cout<<message;
    cin>>fileName;
    inFile.open(fileName);
    while (!inFile){
        cout<<"FILE OPEN FAILED\n";
        cout<<message;
        cin>>fileName;
        inFile.clear();
        inFile.open(fileName);
    }
}

void printPayroll(LList* sortedList){
    cout<<"\n*********Payroll Information********\n";

    sortedList->setCurrent(sortedList->getHead());//reset to top
    while (true){
        Employee* e = CE(sortedList);
        cout<<e->getName()<<", $"<<e->getTotalPay()<<endl;
        if (CN(sortedList) == nullptr){
            break;
        }
        sortedList->next();
    }

    cout<<"*********End Payroll****************\n";
}