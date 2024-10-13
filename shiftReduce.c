#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 20

int n;
struct production{
    char lhs;
    char rhs[MAX_STACK];
}p[MAX_STACK];
char stack[MAX_STACK],input[MAX_STACK];
int k=0,top=-1;

void push(char sub){
    if(top<MAX_STACK-1){
        stack[++top]=sub;
        stack[top+1]='\0';
    }
    else{
        printf("Stack Overflow");
    }
}

void pop(int i){
    if(top>=i-1){
        top=top-i;
        stack[top+1]='\0';
    }
    else{
        printf("Stack Underflow");
    }
}

int shift_reduce(char sub[],int index){
    char check[20];
    strcpy(check,sub);
    int len=strlen(check);
    check[len]=input[k];
    check[len+1]='\0';
    for(int i=0;i<n;i++){
        if(i!=index && strncmp(check,p[i].rhs,len+1)==0){
            return 1;
        }
    }
    return 0;
}

int reduce_reduce(char sub[],int index){
    for(int i=0;i<n;i++){
        if(i!=index && (strcmp(sub,p[i].rhs)==0)){
            return 1;
        }
    }
    return 0;
}

void parse_input(){
    int l=strlen(input);
    input[l]='$';
    input[l+1]='\0';
    push(input[k++]);
    printf("\nStack\tInput\tAction\n");
    printf("%s\t%s\tShift\n",stack,&input[k]);
    int accepted=0;
    while(input[k]!='$'){
        int m=top;
        while(m>=0){
            char sub[MAX_STACK];
            strcpy(sub,&stack[m]);
            m--;

            for(int i=0;i<n;i++){
                if(strcmp(sub,p[i].rhs)==0){
                    if(shift_reduce(sub,i)){
                        printf("Shift reduce conflict\n");
                        exit(0);
                    }
                    if(reduce_reduce(sub,i)){
                        printf("Reduce reduce conflict\n");
                        exit(0);
                    }
                    pop(strlen(sub));
                    push(p[i].lhs);
                    printf("%s\t%s\tReduce by %c->%s\n",stack,&input[k],p[i].lhs,p[i].rhs);
                    m=top;
                }
            }
        }
        if(input[k]!='$'){
            push(input[k++]);
            printf("%s\t%s\tShift\n",stack,&input[k]);
        }
        if(stack[top]==p[0].lhs && input[k]=='$'){
            printf("String is accepted");
            accepted=1;
            break;
        }
    }

    if(input[k]=='$' && !accepted){
        int m=top;
        while(m>=0){
            char sub[MAX_STACK];
            strcpy(sub,&stack[m]);
            m--;

            for(int i=0;i<n;i++){
                if(strcmp(sub,p[i].rhs)==0){
                    if(reduce_reduce(sub,i)){
                        printf("Reduce reduce conflict\n");
                        exit(0);
                    }
                    pop(strlen(sub));
                    push(p[i].lhs);
                    printf("%s\t%s\tReduce by %c->%s\n",stack,&input[k],p[i].lhs,p[i].rhs);
                    m=top;

                    if(stack[top]==p[0].lhs && top==0 && input[k]=='$'){
                        printf("String is accepted\n");
                        accepted=1;
                        break;
                    }
                }
            }
        }
        
    }
    if(!accepted){
            printf("String is not accepted");
        }
}

void main(){
    printf("\nEnter the number of productions:");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        printf("\nEnter the LHS:");
        scanf(" %c",&p[i].lhs);
        printf("\nEnter the RHS:");
        scanf("%s",p[i].rhs);
    }

    printf("Production rules\n");
    for(int i=0;i<n;i++){
        printf("%c->%s\n",p[i].lhs,p[i].rhs);
    }
    printf("Enter the input string:");
    scanf("%s",input);
    parse_input();    
}