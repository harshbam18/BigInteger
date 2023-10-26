#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#define max 1001

struct node {
    int data;
    struct node* next;
};

struct BigInteger {
    struct node* l;
    int length;
    int sign; // 1 for positive, -1 for negative
};

void addatfront(struct node** n1, int data);
struct BigInteger initialize(char* s);
void display(struct BigInteger n1);
struct BigInteger add(struct BigInteger n1, struct BigInteger n2);
struct BigInteger sub(struct BigInteger n1, struct BigInteger n2);
struct BigInteger mul(struct BigInteger num1, struct BigInteger num2);
struct BigInteger div1(struct BigInteger dividend, struct BigInteger divisor);
struct BigInteger mod(struct BigInteger dividend, struct BigInteger divisor);
struct node* reverse(struct node* head);
int compare(struct BigInteger n1, struct BigInteger n2);
struct BigInteger length(struct BigInteger A);
struct node* inttolinkedlist(int n);
#endif
