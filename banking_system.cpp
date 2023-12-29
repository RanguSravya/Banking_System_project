#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
int N;
int N1;
class bankacc {
private:
  unsigned int accno;
  int curbal;
  bankacc *next;

public:
  bankacc() {
    accno = 0;
    curbal = 0;
    next = nullptr;
  }
 bankacc(int k) {
    accno = k;
    curbal = 1000;
    next = nullptr;
  }
  friend class sll;
  friend class dll;
};
class sll {
private:
  bankacc *first;
  bankacc *last;
  int len;

public:
  sll() {
    first = nullptr;
    last = nullptr;
    len = 0;
  }
  void insertbankacc(int k) {
    bankacc *toadd = new bankacc(k);
    if (first == nullptr) {
      first = toadd;
      last = toadd;
    } else {
      bankacc *temp = first;
      while (temp->next != nullptr) {
        temp = temp->next;
      }
      temp->next = toadd;
      last = toadd;
    }
    len++;
  }
  void print1() {
    bankacc *temp = first;
    while (temp != nullptr) {
      cout << temp->accno << " "<<temp->curbal<<" ";
      temp = temp->next;
    }
    cout << endl;
  }
  bankacc *getfirst() { return first; }
  friend class dll;
};
class transaction {
private:
  int ac1;
  char dorw;
  int amount;
  transaction *prev;
  transaction *next;

public:
  transaction() {
    ac1 = -1;
    dorw = '\0';
    amount = 0;
    prev = nullptr;
    next = nullptr;
  }
  transaction(int ac2, char dorw2, int amount1) {
    ac1 = ac2;
    dorw = dorw2;
    amount = amount1;
    prev = nullptr;
    next = nullptr;
  }
  friend class dll;
  friend class sll;
  friend class bankacc;
};
class dll {
private:
  transaction *head;
  transaction *tail;

public:
  transaction *cursor;
  dll() {
    head = new transaction();
    tail = new transaction();
    head->next = tail;
    head->prev = nullptr;
    tail->prev = head;
    tail->next = nullptr;
    cursor = head;
  }
  void inserttransaction(int ac2, char c2, int amount1) {
    transaction *toadd = new transaction(ac2, c2, amount1);
    transaction *temp = head;
    while (temp->next != tail) {
      temp = temp->next;
    }
    temp->next = toadd;
    toadd->prev = temp;
    toadd->next = tail;
    tail->prev = toadd;
  }
  void printalltransaction() {
    transaction *temp = head->next;
    while (temp != tail) {
      cout << temp->ac1 << " " << temp->dorw << " " << temp->amount << " ";
      temp = temp->next;
    }
    cout << endl;
  }
  transaction *gethead() { return head; }
  void processnextxtransactions(int x, sll &list1) {
    int e;
    if (N >= x) {
      e = x;
    } else {
      e = N;
    }
    for (int i = 0; i < e; i++) {
        cursor=cursor->next;
       bankacc *temp2 =list1.first;
      while (temp2 != nullptr) {
        if (temp2->accno == cursor->ac1) {
          if (cursor->dorw == 'W') {
            temp2->curbal = temp2->curbal - cursor->amount;
          } else {
            temp2->curbal = temp2->curbal + cursor->amount;
          }
          N--;
          break;
        }
  temp2=temp2->next;
      }
    }
    return;
  }
  void undoytransactions(int y, sll &list1) {
    if(cursor==head){
      return;
    }
    for (int i = 0; i < y; i++) {
      bankacc *temp2 = list1.first;
        while(cursor->ac1!=temp2->accno) {
          temp2=temp2->next;
        }
          if (cursor->dorw == 'W') {
            temp2->curbal = temp2->curbal + cursor->amount;
          } else {
            temp2->curbal = temp2->curbal - cursor->amount;
          }
          N++;
      if(cursor->prev==head){break;}
     else {
       if(i!=y){
         cursor=cursor->prev;
       }
     }
    }
  }
  void insertkpos(transaction *t, int k,sll& list1) {
    transaction *temp = head->next;
    for (int i = 0; i <= k - 2; i++) {
      temp = temp->next;
    }
    transaction *temp2 = temp->next;
    temp->next = t;
    t->prev = temp;
    t->next = temp2;
    temp2->prev = t;
    N++;
    N1++;
    if(k<=N1-N){
         bankacc *temp2 =list1.first;
      while (temp2 != nullptr) {
        if (temp2->accno == t->ac1) {
          if (t->dorw == 'W') {
            temp2->curbal = temp2->curbal - t->amount;
          } else {
            temp2->curbal = temp2->curbal + t->amount;
          }
          N--;
          break;
        }
  temp2=temp2->next;
      }
    }
  }
  void printalltransactionsofy(int y,sll& list1) {
    transaction *temp = head->next;
    while (temp!= cursor->next) {
      if (temp->ac1 == y) {
        cout << temp->ac1 << " " << temp->dorw << " " << temp->amount << endl;
      }
      temp=temp->next;
    }
  }
void processallfurthertransactions(sll& list1){
  while(cursor->next!=tail){
      cursor=cursor->next;
    bankacc* temp2=list1.first;
    while (temp2 != nullptr) {
        if (temp2->accno == cursor->ac1) {
          if (cursor->dorw == 'W') {
            temp2->curbal = temp2->curbal - cursor->amount;
          } else {
            temp2->curbal = temp2->curbal + cursor->amount;
          }
          N--;
          break;
        }
  temp2=temp2->next;
      }
  }
}
void printcurbalofx(int x,sll& list1){
    bankacc*temp=list1.first;
    while(temp!=nullptr){
        if(temp->accno==x){
            cout<<temp->curbal<<endl;
            break;
        }
        temp=temp->next;
    }
}
void printnoofaccwithcurbalmorethanorequaltox(int x,sll& list1){
    bankacc*temp=list1.first;
    int count=0;
    while(temp!=nullptr){
        if(temp->curbal>=x){
            count++;
        }
        temp=temp->next;
    }
    cout<<count<<endl;
}
void printaccountswithhighestbalance(sll& list1){
    bankacc* temp=list1.first;
    vector<int>v;
    int max=0;
    while(temp!=nullptr){
        if(temp->curbal>max){
            max=temp->curbal;
            v.clear();
            v.push_back(temp->accno);
        }
        else if(temp->curbal==max){
            v.push_back(temp->accno);
        }
        temp=temp->next;
    }
   sort(v.begin(), v.end(), greater<int>());
   for(int i=0;i<v.size();i++){
       cout<<v[i]<<" ";
   }
   cout<<endl;
}
void deletetransaction(int ac,int M,sll& list1){
    if(M>0){
        int i=0;
           transaction*temp=cursor->next;
            while((temp!=tail)&&(i<M)){
        if(temp->ac1==ac){
            transaction*temp1=temp;
            (temp1->prev)->next=temp1->next;
            (temp1->next)->prev=temp1->prev;
            delete temp1;
            N--;
          i++;
          break;
        }
        temp=temp->next;
        }
    }
    else{
        int i=0;
           transaction*temp=cursor->prev;
      while((temp!=head)&&(i<abs(M))){
        if(temp->ac1==ac){
            bankacc *temp2 = list1.first;
      while (temp2->accno!=temp->ac1) {
        temp2=temp2->next;
      }
          if (temp->dorw == 'W') {
            temp2->curbal = temp2->curbal + temp->amount;
          } else {
            temp2->curbal = temp2->curbal - temp->amount;
          }

             transaction*temp1=temp;
            (temp1->prev)->next=temp1->next;
            (temp1->next)->prev=temp1->prev;
            delete temp1;
          N--;
          i++;
        }
        temp=temp->prev;
        }
}
}

  friend class sll;
  friend class bankacc;
  friend class transaction;
};
int main() {
  cout << "Enter the number of bank accounts: ";
  int C;
  cin >> C;
  sll list1;
  int k;
  cout << "Enter the account numbers:" << endl;
  for (int i = 0; i < C; i++) {
    cin >> k;
    list1.insertbankacc(k);
  }
  cout << "Enter the number of transactions: ";
  cin >> N;
  N1=N;
  dll list2;
  int ac1;
  char dorw1;
  int amount1;
  cout << "Enter the transactions (account_number direction amount):" << endl;
  for (int i = 0; i < N; i++) {
    cin >> ac1 >> dorw1 >> amount1;
    list2.inserttransaction(ac1, dorw1, amount1);
  }
   // list1.print1();
   // list2.print2();
  string s;
  int x;
  cout << "Enter the operations (F, R, I, S, C, G, M, V, D) or END to exit:" << endl;
  cin >> s;
  while (s != "END") {
    if (s == "F") {
      cout << "Enter the number of transactions to process: ";
      cin >> x;
      list2.processnextxtransactions(x, list1);
      // list1.print1();
    }
     else if (s == "R") {
       cout << "Enter the number of transactions to undo: ";
      cin >> x;
      list2.undoytransactions(x, list1);
      // list1.print1();
    }
     else if (s == "I") {
      int ac1;
      char c3;
      int amount3;
      int k;
       cout << "Enter the transaction details (account_number direction amount position): ";
      cin >> ac1 >> c3 >> amount3 >> k;
      transaction *t = new transaction(ac1, c3, amount3);
      list2.insertkpos(t, k,list1);
      // list2.print2();
      // list1.print1();
    } 
    else if (s == "S") {
       cout << "Enter the account number to display transactions: ";
      int y;
      cin >> y;
      list2.printalltransactionsofy(y,list1);
    }
    else if(s=="C"){
       list2.processallfurthertransactions(list1); 
       // list1.print1();
    }
    else if(s=="G"){
      cout << "Enter the minimum balance: ";
      int r;
      cin>>r;
      list2.printnoofaccwithcurbalmorethanorequaltox(r,list1);
    }
    else if(s=="M"){
        list2.printaccountswithhighestbalance(list1);
    }
    else if(s=="V"){
      cout << "Enter the account number to display current balance: ";
        cin>>x;
        list2.printcurbalofx(x,list1);
    }
    else if(s=="D"){
      cout << "Enter the account number and number of transactions to delete: ";
        int A;
        cin>>A;
        int M;
        cin>>M;
        list2.deletetransaction(A,M,list1);
        // list2.print2();
        // list1.print1();
    }
    cout << "Enter the next operation or END to exit: ";
    cin >> s;
  }
  return 0;
}

