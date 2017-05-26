
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <mm_malloc.h>
#include <math.h>
#include <time.h>


unsigned long int comp = 0, moves = 0;
double T;
int s;
// About reading from file
typedef struct package
{
    double a;
    unsigned long int c;
} p;

struct bin_tree {
    int data;
    struct bin_tree * right, * left;
};
typedef struct bin_tree node;

int interpolationSearch(int a, int n, p *pack) {
    // Find indexes of two corners
    int lo = 0, hi = (n - 1);

    // Since array is sorted, an element present
    // in array must be in range defined by corner
    while (lo <= hi && a >= pack[lo].c && a <= pack[hi].c)
    {
        // Probing the position with keeping
        // uniform distribution in mind.
        int pos = lo + (((double)(hi-lo) /
                         (pack[hi].c-pack[lo].c))*(a - pack[lo].c));

        // Condition of target found
        if (pack[pos].c == a) {
            comp++;
            return pos;
        }

        // If x is larger, x is in upper part
        if (pack[pos].c < a) {
            lo = pos + 1;
            comp++;
        }
        // If x is smaller, x is in lower part
        else {
            hi = pos - 1;
            comp++;
        }

        moves++;
    }
    return -1;
}

void insert(node ** tree, int val) {
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        comp++;
        return;
    }

    if(val <= (*tree)->data)
    {
        insert(&(*tree)->left, val);
        comp++;
        moves++;
    }
    else if(val >= (*tree)->data)
    {
        insert(&(*tree)->right, val);
        comp++;
        moves++;
    }

}

void print_inorder(node * tree) {
    if (tree)
    {
        print_inorder(tree->left);
        printf("[%d]",tree->data);
        print_inorder(tree->right);
    }
}

void deltree(node * tree) {
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}

node* search(node ** tree, int val) {
    if(!(*tree))
    {
        comp++;
        return NULL;
    }

    if(val < (*tree)->data)
    {
        comp++;
        moves++;
        search(&((*tree)->left), val);
    }
    else if(val > (*tree)->data)
    {
        comp++;
        moves++;
        search(&((*tree)->right), val);
    }
    else if(val == (*tree)->data)
    {
        comp++;
        return *tree;
    }
    return *tree;
}


//ALL ABOUT SORT
// Bubble sort;
void sort_bubble(unsigned long int n, p *pack) {
    unsigned long int i, j, tmp;
    for (i=0; i<n-1; i++) {
        for (j=0; j<n-(1+i); j++) {
            if(pack[j].c > pack[j+1].c) {
                tmp = pack[j].c;
                pack[j].c = pack[j+1].c;
                pack[j+1].c = tmp;
                comp++;
            }
            moves++;

        }
    }
}

// Insertion sort;
void sort_insertion(unsigned long int n, p *pack) {
    unsigned int newElement;
    int location,i;
    for ( i = 1; i < n; i++) {
        newElement = pack[i].c;
        location = i - 1;
        while(location >= 0 && pack[location].c > newElement){
            pack[location+1].c = pack[location].c;
            location = location - 1;
            moves++;
            comp++;
        }
        pack[location+1].c = newElement;
        moves++;
    }
}

//Quick sort;
void sort_quick(p *pack, unsigned long int low, unsigned long int high)
{
    unsigned long int l=low,r=high;
    static unsigned long int i,sred,min,max;
    p temp;
    min=l;
    max=r;
    for (i=l; i<r; ++i)
    {
        if (pack[i].c > pack[max].c) max=i;
        if (pack[i].c < pack[min].c) min=i;
    }
    sred=(pack[max].c + pack[min].c)/2;
    while (l <= r)
    {
        while (pack[l].c < sred)
        {
            ++l;
            moves++;
        }
        while (pack[r].c > sred)
        {
            --r;
            moves++;
        }
        if (l <= r)
        {
            temp=pack[l];
            pack[l]=pack[r];
            pack[r]=temp;
            --r;
            ++l;
            comp++;
        }
        moves++;
    }
    if (low < r){
        sort_quick(pack, low, r);
        comp++;

    }
    if (high > l) {
        sort_quick(pack, l, high);
        comp++;
    }
}



//ALL ABOUT SEARCH
int linearSearch (unsigned int a, int n, p *pack) {
    int i ;
    unsigned int lol;
    for (i=0; i<n; i++) {
        lol = pack[i].c;
        if (a==lol) {
            comp++;
            return i;
        }
        moves++;
    }
    return -1;
}

int main(int argc,char *argv[])
{
    node *root = NULL, *min;

    unsigned long int * massive;
    unsigned int key;
    long int k,i;
    double Tstart,Tend;
    int inputinput,inputsortway,inputsearchway, value,see;
    printf("Input size: ");
    scanf("%i", &s);
    p *pack;
    pack=(struct package*)malloc(s*sizeof(struct package));

    printf("Choose a way of inputting:\n 1 By myself \n 2 From file\n 3 By random\n");
    scanf("%d",&inputinput);
    switch (inputinput){
        case 1:{
            printf(" Inputting by myself was chosen\n");
            massive = (unsigned long int *)malloc(s * sizeof(unsigned long int));
            printf("Input the array elements:\n");
            for ( i = 0; i < s; i++) {
                scanf("%lu", &massive[i]);
                pack[i].c = massive[i];
                pack[i].a = 1.1;
            }
            break;
        }
        case 2:{
            printf("Inputting from file was chosen\n ");
            FILE *otcr;
            char rz [255];
            int b=0;
            if(!(otcr=fopen(argv[1],"rb")) || (argc==1)) {
                printf("Enter the file name\n");
                scanf("%s",rz);
                if (!(otcr=fopen(rz,"rb"))) {
                    printf("Cant use this file");
                    return 0;
                }
                else
                    printf ("Using file %s\n", rz);
            }
            else printf("Using file %s\n", argv[1]);

            fseek(otcr,0,SEEK_SET);

            for (i=0; i<s; i++) {
                fscanf(otcr,"%lf,%lu\n",&pack[i].a,&pack[i].c);
            }

            fclose (otcr);
            break;
        }
        case 3:{
            printf(" Inputting by random was chosen\n");
            massive = (unsigned long int *)malloc(s * sizeof(unsigned long int));
            printf("Input the array elements:\n");
            for ( i = 0; i < s; i++) {
                massive[i]=rand()%10000;
                pack[i].c = massive[i];
                pack[i].a = 1.1;
            }
            break;
        }

        default:{
            printf ("Wrong input\n");
            return (0);
            break;
        }
    }

    printf("Choose a way of sort:\n 1 For insertion\n 2 For quick\n 3 For tree and tree search\n 4 For bubble\n ");
    scanf("%d",&inputsortway);

    switch (inputsortway){

        case 1:{
            Tstart = clock();
            sort_insertion (s, pack);
            Tend=clock();
            T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
            printf("\nEstimated time to sort:  %lf sec\n",T);
            printf("\nMoves through array: [%lu]", moves);
            printf("\nNumber of comparsions [%lu]", comp);
            moves=0;
            comp=0;
            T = 0;
            break;
        }
        case 2:{
            Tstart = clock();
            sort_quick(pack, 0, s-1);
            Tend=clock();
            T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
            printf("\nEstimated time to sort:  %lf sec\n",T);
            printf("\nMoves through array: [%lu]", moves);
            printf("\nNumber of comparsions [%lu]", comp);
            moves=0;
            comp=0;
            T = 0;
            break;
        }
        case 3:{

            Tstart = clock();
            for(k=0; k<s-1; k++) {
                value = pack[k].c;
                insert(&root, value);
            }
            Tend=clock();
         //   print_inorder(root);   вывод
            T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
            printf("\nEstimated time to sort:  %lf sec\n",T);
            printf("\nMoves through array: [%lu]", moves);
            printf("\nNumber of comparsions [%lu]", comp);
            moves=0;
            comp=0;
            T = 0;
            printf("Input element to search in array: ");
            scanf("%d", &key);
            Tstart = clock();
            min = search(&root, key);
            Tend=clock();
            T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
            if (min) {
                printf("Searched node=%d\n", min->data);printf("\nEstimated time to sort:  %lf sec\n",T);
                printf("\nMoves through array: [%lu]", moves);
                printf("\nNumber of comparsions [%lu]", comp);
                moves=0;
                comp=0;
                T = 0;
            } else {
                printf("Data Not found in tree.\n");
                moves=0;
                comp=0;
                T = 0;
            }

            break;
  // return 0 ******Эта строчка должна была заканчивать программу при выборе дерева, но мой компилятор работал некорректно и я не стал рисковать

        }
        case 4:{
            Tstart = clock();
            sort_bubble(s, pack);
            Tend=clock();
            T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
            printf("\nEstimated time to sort:  %lf sec\n",T);
            printf("\nMoves through array: [%lu]", moves);
            printf("\nNumber of comparsions [%lu]", comp);
            moves=0;
            comp=0;
            T = 0;
            break;
        }
        default:{
            printf("Wrong input\n");

            break;

        }

    }
    printf ( "Do you want to see soorted massive?:\n 1 Yes\n 2 No\n");
    scanf("%d",&see);
   switch (see){

    case 1: {printf("Sorted array:\n");
    for ( i = 0; i < s; i++){
        printf("%lu ", pack[i].c);
        printf("\n");}
      break; }

case 2: break;
}

       printf("Enter a key:\n");
        scanf("%d",&key);
        printf("Choose a way of search:\n 1 For line \n 2 For interpol\n ");
        scanf("%d",&inputsearchway);
        switch(inputsearchway){


            case 1:{
                Tstart = clock();
                k = linearSearch(key, s, pack);
                Tend=clock();
                T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
                if (k != -1) {
                    printf("The index of the element is %ld\n", k);
                    printf("\nEstimated time to sort:  %lf sec\n",T);
                    printf("\nMoves through array: [%lu]", moves);
                    printf("\nNumber of comparsions [%lu]", comp);
                    moves=0;
                    comp=0;
                    T = 0;
                }
                else
                {
                    printf("The element isn't found!\n");
                    moves=0;
                    comp=0;
                    T = 0;
                }
                break;
            }
            case 2:{
                Tstart = clock();
                value = interpolationSearch(key,s,pack);
                Tend=clock();
                T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
                if (value != -1) {
                    printf("The index of the element is %d\n", value);
                printf("\nEstimated time to sort:  %lf sec\n",T);
                printf("\nMoves through array: [%lu]", moves);
                printf("\nNumber of comparsions [%lu]", comp);
                moves=0;
                comp=0;
                T = 0;
                }
                else
                    printf("Element not found.");
break;
            }
            default:{
                printf("Wrong input\n");
                return 0;
                break;
            }
        }
    return 0;
}


