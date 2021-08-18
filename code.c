# include <stdio.h>
# include <stdlib.h>
# include <time.h>
#define MAX_VER 10000
#define MAX_EDG 3000

struct event                                                                                 // Structure of event node
{
    int time;
    int identity;
    char action;
    struct event* next;
};
struct list                                                                                  // structure of list node which contains the list of different status
{
    int identity;
    struct list* next;
};

typedef unsigned char vertex;
typedef struct list list;
typedef struct event event;
typedef unsigned char vertex;
list *head_s,*head_i,*head_r;                                                                // Declaring some global variables
event* head=NULL;
vertex*** graph;

void process_rec_SIR(int identity);                                                          // Prototype of functions
void process_trans_SIR(int identity);
int find(int identity,char action);
void initial_sus(void);
void print_lists(void);
int check_exists(int identity,char type);
void del_list(int identity,char type);
void add(int identity,char type);
void insert(int identity,char type);
void delt(void);
void SIR(void);
void initial_inf(void);
int getRecTime(void);
void get_graph(void);
int getInfTime(void);
int num_ver,num_edg,TIME;

/* This function adds the node in different lists(suseptible infected and recovered)*/
void add(int identity,char type)
{
    list* temp=(list*)malloc(sizeof(list));
    temp->identity=identity;
    temp->next=NULL;
    if(type =='S')
    {
        temp->next=head_s;
        head_s=temp;
    }
    if(type =='I')
    {
        temp->next=head_i;
        head_i=temp;
    }
    if(type =='R')
    {
        temp->next=head_r;
        head_r=temp;
    }
}
/*This function checks if a particular node exists in a given list or not*/
int check_exists(int identity,char type)
{
    list* temp=NULL;
    if(type =='S')
    {
        temp=head_s;
    }
    else if(type =='I')
    {
        temp=head_i;
    }
    else if(type =='R')
    {
        temp=head_r;
    }
    if(temp==NULL)
    {
        return(0);
    }
    while(temp!=NULL)
    {
        if(temp->identity==identity)
        {
            return(1);
        }
        temp=temp->next;
    }
    return(0);
}

/*This function delete the nodes from the a given list*/
void del_list(int identity,char type)
{
    list* temp=NULL,*temp1=NULL;
    if(type =='S')
    {
        temp=head_s;
    }
    else if(type =='I')
    {
        temp=head_i;
    }
    else if(type =='R')
    {
        temp=head_r;
    }
    while(temp->identity!=identity)
    {
        temp1=temp;
        temp=temp->next;
        if(temp==NULL)
        {
            break;
        }
    }
    if(temp==NULL)
    {
        return;
    }
    else if(temp1==NULL)
    {
        if(type =='S')
        {
            head_s=head_s->next;
        }
        else if(type =='I')
        {
            head_i=head_i->next;
        }
        else if(type =='R')
        {
            head_r=head_r->next;
        }
    }
    else if(temp!=NULL)
    {
        temp1->next=temp->next;
    }
}
/* this function insert the event node in the priority queue.
It takes the identity of the node and type of the event(infection or recovery)*/
void insert(int identity,char type)
{
    int time;
    event *newevent,*temp1,*temp;
    newevent=(event*)malloc(sizeof(event));
    newevent->identity=identity;
    if(type=='T')
    {
        newevent->action='T';
        time=getInfTime()+TIME;
        newevent->time=time;
    }
    else if(type=='R')
    {
        newevent->action='R';
        time=getRecTime()+TIME;
        newevent->time=time;
    }
    if(head==NULL)
    {
        head=newevent;
        head->next=NULL;
    }
    else
    {
        if(head->time>=newevent->time)
        {
            newevent->next=head;
            head=newevent;
        }
        else
        {
            temp=head;
            while(temp->time<=newevent->time)
            {
                temp1=temp;
                if(temp!=NULL)
                {
                    temp=temp->next;
                }
                if(temp==NULL)
                {
                    break;
                }
            }
            if(temp==NULL)
            {
                temp1->next=newevent;
            }
            else
            {
                newevent->next=temp;
                temp1->next=newevent;
            }
        }
    }
}
/*This function removes the event from the queue*/
void delt(void)
{
    head=head->next;
}

/*this function searches a particular node with a given action in the queue*/
int find(int identity,char action)
{
    event* temp=head;
    if(temp==NULL)
    {
        return(0);
    }
    while(1)
    {
        if(temp==NULL)
        {
            return(0);
        }
        else if(temp->identity==identity&&temp->action=='T')
        {
            return(1);
        }
        temp=temp->next;
    }
    return(0);
}

/*This function determines the infection time for a event node that is when will it spread the infection*/
int getInfTime(void)
{
    int counter=1;
    while(rand()%2!=1)
    {
        counter++;
    }
    return(counter);
}

/*This function determines the recovery time for a event node that is when will it recover*/
int getRecTime(void)
{
    int counter=1;
    while(rand()%5!=4)
    {
        counter++;
    }
    return(counter);
}

/*This function generate the graph of random number of nodes which is less than MAX_VER.
pointer to pointer to pointer is used in this function*/
void get_graph(void)
{
    srand(time(NULL));
    num_ver=rand()%MAX_VER;
    num_edg=rand()%MAX_EDG;
    graph= (vertex***)malloc(sizeof(vertex**)*num_ver);
    int ver_count=0;
    int edg_count=0;
    printf("Number of Vertices and Edges are %d and %d respectively .\n",num_ver,num_edg);
    /*allocating the memory to variable*/
    for(ver_count=0; ver_count<num_ver;ver_count++)
    {
        graph[ver_count]=(vertex**)malloc(sizeof(vertex*)*num_ver);
        for(edg_count=0;edg_count<num_ver;edg_count++)
        {
            graph[ver_count][edg_count]=(vertex*)malloc(sizeof(vertex));
        }
    }
    for(ver_count=1; ver_count<num_ver; ver_count++)
    {
        for(edg_count=1;edg_count<num_ver;edg_count++)
        {
            graph[ver_count][edg_count]=NULL;
        }
    }
    /*linking the vertices*/
    int link_ver;
    for(ver_count=0; ver_count<num_ver; ver_count++)
    {
        for(edg_count=0;edg_count<num_edg;edg_count++)
        {
            if(rand()%2==1)
            {
                link_ver=rand()%num_ver;
                graph[ver_count][link_ver]=graph[link_ver][0];
            }
            else
            {
                /*If node ver_count is not linked with node link_ver then graph[ver_count][link_ver] will be null*/
                graph[ver_count][link_ver]=NULL;
            }
        }
    }
}
/*This function runs through the queue for 300 days and then calls the recovery and infection process and then prints the different categories */
void SIR(void)
{
    for(TIME=0;TIME<300;TIME++)
    {
        if(head!=NULL&&!(head_s==NULL&&head_i==NULL))                                      // If no infected and suspected case is remaining
        {
            event* topevent=head;
            while(topevent->time==TIME)
            {
                if(topevent->action=='T')
                {
                    if((check_exists(topevent->identity,'R')==0))
                    {
                        process_trans_SIR(topevent->identity);
                    }
                    delt();
                    insert(topevent->identity,'T');
                }
                else if(topevent->action=='R')
                {
                    if(check_exists(topevent->identity,'R')==0)
                    {
                        process_rec_SIR(topevent->identity);
                    }
                    delt();
                }
                if(head==NULL)
                {
                    break;
                }
                topevent=head;
            }
        }
        printf("\n**********************************************************************************************************\n");
        printf("The summary on day %d*************************************************************************************\n",TIME+1);
        print_lists();
    }
}
/*This function process the transmission of infection to different nodes*/
void process_trans_SIR(int identity)
{
    for(int i=0;i<num_ver;i++)
    {
        if(graph[identity][i]!=NULL)                 // if ith node connected with the identity node
        {
            if(rand()%2==1)                          // probability of infection
            {
                if(find(i,'T')==0)                   // if there is no transmission of i node exists in the queue
                {
                    if((check_exists(i,'R')==0)&&(check_exists(i,'S')==1))    // If ith node is suseptible and not yet recovered
                    {
                        insert(i,'T');
                        insert(i,'R');
                        del_list(i,'S');
                        if(check_exists(i,'I')==0)                            // If ith node is not yet inserted the infected list
                        {
                            add(i,'I');
                        }
                    }
                }
            }
        }
    }
}

void process_rec_SIR(int identity)
{
    if(check_exists(identity,'R')==0)                                         // If Ith node is not yet recovered
    {
        add(identity,'R');
        del_list(identity,'I');
    }
}

/*This function takes the input of nodes initially infected*/
void initial_inf(void)
{
    int n,inf_id;
    printf("\nEnter the number of initial infected: ");
    scanf("\n%d",&n);
    for(int i=0;i<n;i++)
    {
        printf("\nEnter the identity of the Infected:");
        scanf("\n%d",&inf_id);
        insert(inf_id,'T');
        insert(inf_id,'R');
        add(inf_id,'I');
        del_list(inf_id,'S');
    }
}

/*Initially assigning all nodes to suspected category*/
void initial_sus(void)
{
    for(int i=0;i<num_ver;i++)
    {
        add(i,'S');
        /*
        list *temp,*temp1,*temp2;
        temp1=head_s;
        temp=(list*)malloc(sizeof(list));
        temp->identity=i;
        temp->next=NULL;
        if(head_s==NULL)
        {
            head_s=temp;
            head_s->next=NULL;
        }
        else if(temp1!=NULL)
        {
            while(temp1!=NULL)
            {
                temp2=temp1;
                temp1=temp1->next;
            }
            temp2->next=temp;
        }*/
    }
}
/*This function prints all three lists */
void print_lists(void)
{
    int counter;
    for(int i=0;i<3;i++)
    {
        list* temp=NULL;
        counter=0;
        if(i==0)
        {
            temp=head_s;
            printf("The susceptible nodes are following :");
        }
        else if(i==1)
        {
            temp=head_i;
            printf("The infected nodes are following :");
        }
        else if(i==2)
        {
            temp=head_r;
            printf("The recovered nodes are following :");
        }
        while(temp!=NULL)
        {
            counter++;
            temp=temp->next;
        }
        printf("%d ",counter);
        printf("\n");
    }
}

/* main function starts here */
int main()
{
    TIME=0;
    get_graph();
    initial_sus();
    initial_inf();
    SIR();
}
