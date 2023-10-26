#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInteger.h"
#define max 1001
void addatfront(struct node** n1, int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (!temp) {
        printf("Memory allocation failed\n");
        return;
    }
    temp->data = data;
    temp->next = *n1;
    *n1 = temp;
}
struct BigInteger initialize(char* s) {
    struct BigInteger n1;
    n1.l = NULL;
    n1.length = 0;
    n1.sign = 1;

    if (s[0] == '-') {
        n1.sign = -1;
        s++; // Move past the negative sign
    }
    int l=strlen(s);
    for (int i = (s[0] == '-' ? 1 : 0); i < l; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            addatfront(&(n1.l), (s[i] - '0'));
            n1.length++;
        }
    }

    return n1;
}
void display(struct BigInteger n1) {
  

    if (!n1.l) {
        printf("0\n");
        return;
    }
    else if (n1.sign == -1) {
        printf("-");
    }
    // Count the number of digits to determine the required buffer size
    int numDigits = n1.length;
    int buffer_size = numDigits + 1;  // +1 for the null terminator
    char* displayStr = (char*)malloc(buffer_size);
    if (!displayStr) {
        printf("Memory allocation failed\n");
        return;
    }

    struct node* current = n1.l;
    int i = 0;
    while (current) {
        displayStr[i] = current->data + '0';
        current = current->next;
        i++;
    }
    displayStr[i] = '\0';

    printf("%s\n", displayStr);
    free(displayStr);
}
struct node* reverse(struct node* head) {
    struct node* temp1 = NULL;
    struct node* temp2 = NULL;
    while (head != NULL) {
        temp2 = (head)->next;
        (head)->next = temp1;
        temp1 = head;
        (head) = temp2;
    }
    head = temp1;
    return temp1;
}
int compare(struct BigInteger n1, struct BigInteger n2) {
    if (n1.length > n2.length) {
        return 1;
    } else if (n1.length < n2.length) {
        return -1;
    } else {
        int res=0;
        struct node* itr1=n1.l;
        struct node* itr2= n2.l;
        while(itr1!=NULL)
        {
            if(itr1->data > itr2->data)
            {
                res=1;
            }
            else if(itr1->data < itr2->data)
            {
                res=-1;
            }
            itr1=itr1->next;
            itr2=itr2->next;

        }
        return res;
    }
}
struct BigInteger length(struct BigInteger A)
{
    int l=0;
    struct node *temp=A.l;
    while(temp)
    {
        l++;
        temp=temp->next;
    }
    A.length=l;
    return A;
}
struct BigInteger add(struct BigInteger n1, struct BigInteger n2) {
    struct BigInteger result;
    result.l = NULL;
    result.length = 0;
     if(n2.length>n1.length)
    {
        struct BigInteger temp = n1;
        n1=n2;
        n2=temp;
    }

    // Determine the sign based on the conditions
    if (n1.sign == -1 && n2.sign == -1) {
        result.sign = -1; // Both inputs are negative
    } else if (n1.sign == 1 && n2.sign == 1) {
        result.sign = 1; // Both inputs are positive
    }
    else if (n1.sign == -1 && n2.sign == 1) {
        if(compare(n1,n2)==1)
        {
            
            n1.sign=1;
            result=sub(n1,n2);
            result.sign=-1;
            return result;
        }
        else{
            
            n1.sign=1;
            result=sub(n2,n1);
            result.sign=1;
            return result;
        }
    }
    else {
        if(compare(n1,n2)==1)
        {
            
            n2.sign=1;
            result=sub(n1,n2);
            result.sign=1;
            return result;
        }
        else
        {
            
            n2.sign=1;
            result=sub(n2,n1);
            result.sign=-1;
            return result;
        }
    }

    int carry = 0;
    struct node* p1 = n1.l;
    struct node* p2 = n2.l;

    while (p1 || p2) {
        int val1 = (p1) ? p1->data : 0;
        int val2 = (p2) ? p2->data : 0;

        int sum = carry + val1 + val2;
        carry = sum / 10;
        addatfront(&(result.l), sum % 10);
        result.length++;

        if (p1) p1 = p1->next;
        if (p2) p2 = p2->next;
    }

    if (carry > 0) {
        addatfront(&(result.l), carry);
        result.length++;
    }
    // Remove leading zeros
    while (result.l && result.l->data == 0) {
        struct node* temp = result.l;
        result.l = result.l->next;
        free(temp);
        result.length--;
    }
    return result;
}
struct BigInteger sub(struct BigInteger n1, struct BigInteger n2) {
    struct BigInteger result;
    result.l = NULL;
    result.length = 0;

    if (n2.length > n1.length) {
        // Swap n1 and n2, so n1 always represents the larger absolute value
        struct BigInteger temp = n1;
        n1 = n2;
        n2 = temp;
    }

    // Determine the sign based on the conditions
    if (n1.sign == -1 && n2.sign == -1) 
    {
        
         if(compare(n1,n2)==1)
        {
            result.sign=-1;
            
        }
        else{
            result.sign=1;
            struct BigInteger temp = n1;
            n1 = n2;
            n2 = temp;
        }
    } 
    else if (n1.sign == 1 && n2.sign == 1)
    {
         if(compare(n1,n2)==1)
        {
            result.sign=1;
        }
        else{
            result.sign=-1;
            struct BigInteger temp = n1;
            n1 = n2;
            n2 = temp;
        }
    }
    else if(n1.sign==1 && n2.sign==-1)
    {
        n2.sign=1;
        result.sign=1;
        result=add(n1,n2);
        return result;

    }
    else
    {
        n2.sign=-1;
        result.sign=-1;
        result=add(n1,n2);
        return result;
    }
    
    int borrow = 0;
    struct node* p1 = n1.l;
    struct node* p2 = n2.l;

    while (p1 || p2) {
        int val1 = (p1) ? p1->data : 0;
        int val2 = (p2) ? p2->data : 0;

        int diff = val1 - val2-borrow;

        if (diff<0) {
            borrow = 1;
            diff += 10;  // Borrow from the next digit
        } else {
            borrow = 0;
        }
        addatfront(&(result.l), diff);
        result.length++;
        if (p1) p1 = p1->next;
        if (p2) p2 = p2->next;
    }

    // Remove leading zeros
    while (result.l && result.l->data == 0) {
        struct node* temp = result.l;
        result.l = result.l->next;
        free(temp);
        result.length--;
    }

    return result;
}
struct BigInteger mul(struct BigInteger num1, struct BigInteger num2) {
    struct BigInteger result;
    result.l = NULL;
    result.length = 0;
    result.sign = (num1.sign == num2.sign) ? 1 : -1; // Determine the sign of the result

    if (num1.length == 0 || num2.length == 0) {
        // If either input is empty, the product is also empty
        return result;
    }

    // Create an array to store intermediate results for each digit
    int* intermediate = (int*)calloc(num1.length + num2.length, sizeof(int));

    if (!intermediate) {
        printf("Memory allocation failed\n");
        return result;
    }

    struct node* p1 = num1.l;
    int index1 = 0;

    while (p1) {
        int carry = 0;
        struct node* p2 = num2.l;
        int index2 = 0;

        while (p2) {
            intermediate[index1 + index2] += (p1->data * p2->data) + carry;
            carry = intermediate[index1 + index2] / 10;
            intermediate[index1 + index2] %= 10;

            p2 = p2->next;
            index2++;
        }

        if (carry > 0) {
            intermediate[index1 + index2] += carry;
        }

        p1 = p1->next;
        index1++;
    }

    // Find the first non-zero index in the intermediate array
    int product_length = num1.length + num2.length;
    int first_non_zero_index = product_length - 1;
    while (first_non_zero_index >= 0 && intermediate[first_non_zero_index] == 0) {
        first_non_zero_index--;
    }

    // Create the result struct based on the intermediate array
    for (int i = first_non_zero_index; i >= 0; i--) {
        addatfront(&(result.l), intermediate[i]);
        result.length++;
    }

    free(intermediate);
    struct node* ptr = result.l;
    ptr = reverse(ptr);
    result.l = ptr;
    return result;
}
struct node* inttolinkedlist(int n)
{
    struct node* list = NULL;

    int digit;

    do {
        digit = n % 10;
        addatfront((&list),digit);
        n = n / 10;
    } while(n > 0);
    return list;
}
struct BigInteger div1( struct BigInteger n1,struct BigInteger n2)
{
    struct BigInteger result;
    result.l=NULL;
    result.length=0;
    unsigned int count=0;
    if(n1.sign==n2.sign)
    {
        result.sign=1;
    }
    else
    {
        result.sign=-1;
    }
    n1.sign=1;
    n2.sign=1;
    struct BigInteger temp=n2;
    while(compare(n1,temp)>=0)
    {
        count++;
        temp= add(temp,n2);
        temp.l=reverse(temp.l);
       
    }
    result.l=inttolinkedlist(count);
    return result;
}
struct BigInteger mod(struct BigInteger n1,struct BigInteger n2)
{
    struct BigInteger result;
    result.l=NULL;
    result.length=0;
    unsigned int count=0;
    if(compare(n1,n2)==-1)
    {
        n1.l=reverse(n1.l);
        return n1;
    }
    if(n1.sign==n2.sign)
    {
        result.sign=1;
    }
    else
    {
        result.sign=-1;
    }
    
    n1.sign=1;
    n2.sign=1;
    struct BigInteger temp=n2;
    struct BigInteger prev;
    while(compare(n1,temp)>=0)
    {
        count++;
        prev=temp;
        temp= add(temp,n2);
        temp.l=reverse(temp.l);
      
    }
    result=sub(n1,prev);
    result.l=reverse(result.l);
    return result;
}