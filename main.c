#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct semn {
    char sym;
    int pri;
} a[1001];

struct formula {
    char item[1001];
} b[1001];

void showsteps(cs,cf,step){
int i;
printf("\n**********************************************\nPasul %d:\n\nStiva operatorilor: ",step);
for(i=0;i<cs;i++)
  printf("%c|",a[i].sym);
printf("\n                    ");
for(i=0;i<cs;i++)
  printf("%d ",a[i].pri);
printf("\n\nStiva operanzilor: ");
for(i=0;i<cf;i++)
  printf("%s|",b[i].item);
};

int main()
{
int i,cs=0,cf=0,pb=0,step=1;
char prop[1001]="#",inp[1001];
scanf("%s",&inp);
strcat(prop,inp);
strcat(prop,"#");
// adaugam simbolurie #
for (i=0;i<strlen(prop);i++)
{
//printf("\nDebug: %s\n",b[cf].item);
switch(prop[i])
{
case '#':
    a[cs].sym=prop[i];
    a[cs].pri=0;
    cs++;
    break;
case '+':
case '-':
    a[cs].sym=prop[i];
    a[cs].pri=1+pb;
    cs++;
    break;
case '*':
case '/':
    a[cs].sym=prop[i];
    a[cs].pri=2+pb;
    cs++;
    break;
case '(':
    pb+=10;
    b[cf].item[0]=prop[i];
    break;
case ')':
    pb-=10;
    strcat(b[cf-1].item,")");
    break;
default:
    //printf("\nDebug default: %s la pasul %d\n",b[cf].item[0],step);
    if(b[cf].item[0]=='(')
        strncat(b[cf].item,&prop[i],1); //pune operandul in stiva pe aceiasi locatie cu '('
    else {
        memset(b[cf].item,0,strlen(b[cf].item)); // goleste memoria pentru string
        b[cf].item[0]=prop[i];
        }
    cf++;
    break;
}
if (cs>1)
while(a[cs-1].pri<=a[cs-2].pri && !(a[cs-1].sym=='#' && a[cs-2].sym=='#'))
{

    showsteps(cs,cf,step); // pentru aratarea pasilor si stivelor
    step++;
    strncat(b[cf-2].item,&a[cs-2].sym,1); //daca gaseste un operator, il adauga in stiva de operanzi
    strcat(b[cf-2].item,b[cf-1].item);//adauga operandul curent la operandul precedent(cel care are si operator)
    cf--;
    a[cs-2]=a[cs-1]; //muta operatorul pe locul precedent in stiva
    cs--;
    memset(b[cf].item,0,strlen(b[cf].item)); // goleste memoria pentru string
}
showsteps(cs,cf,step); // pentru aratarea pasilor si stivelor
step++;
}
printf("\n**********************************************\nRezultatul final: %s\n",b[0].item);
}
