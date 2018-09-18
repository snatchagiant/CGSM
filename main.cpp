#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <sstream>
#include <string>
#include "time.h"
#include "math.h"
#include "CGSM.h"


using namespace std;

void clean_memory(int **memory_space, int first_row_number);
int Interleave_items(int *sequence, int num_items);

int main()
{
    /* * state the number of items * */
    int theScale = 0; //
    while(theScale  <= 0){//
        cout<<"\n input a number for scale = ";
        cin>>theScale; if(theScale >= 2) break;
        cout<<"\n please input a numeric that is at least greater than 2 for definite number"<<endl;
        theScale = 0;
    }//
    cout<<"\n theScale = "<<theScale<<endl;

    /* *  make data * */
    const int Input_Amount_I = 4; //the number of columns of 2nd dimension array
    int **Memory_instance = new int*[Input_Amount_I];//define 2D array to carray items, keys, intermedium data and result

    for(int n = 0; n < Input_Amount_I; n++)
    {//initialize
        Memory_instance[n] = new int[theScale + 1];
        for(int m = 0; m <= theScale; m++)
        {
            if(!n) Memory_instance[n][m] = m; else Memory_instance[n][m] = 0;
        }
    }//initialize
    /* *********************** arrangement for memory *********************** */
    /* A. these indices for row serves as items' indices.                     */
    /* B. 0th column is for keys.                                             */
    /* C. 1th column for aid.                                                 */
    /* D. 2th column for carry index that is former item.                     */
    /* E. 3th column for carry index that is later item.                      */
    /* F. with 2th and 3th commonly constructs a double linked list.          */
    /* *********************** ********************** *********************** */

    Memory_instance[0][0] = theScale; int index = 0;

    index = Interleave_items(Memory_instance[0], theScale);// ster those keys to minic a worst case in permutation

    // test print
    if(theScale <= 100) for(int n = 0; n <= theScale; n++){cout<<n<<" = "<<Memory_instance[0][n]; if(n != theScale) cout<<", "; else cout<<"."<<endl;}

    /* *  initialize the sorting class with space, scale and the number of row * */
    CardGameSorting_Method sorting_method(Memory_instance, theScale, Input_Amount_I);
    index = sorting_method.Sorting();

    /* *  test the sequence that should in ascent from left to right * */
    theScale = 0;

    while(index)
    {
        int next = sorting_method.get_theLater(index);
        if(!next) break;
        if(sorting_method.get_theKeys(index) > sorting_method.get_theKeys(next))theScale ++;
        index = next;
    }
    // print the result of verifying sequence
    if(theScale > 0) cout<<"\n failure! = "<<theScale<<endl; else cout<<"\n succeed!"<<endl;

    //print results
    if(theScale <= 100)
    {
        int next = sorting_method.get_theHead();
        while(next)
        {
            cout<<" "<<next<<" = "<<sorting_method.get_theKeys(next)<<"; ";
            next = sorting_method.get_theLater(next);
            if(!next) break;
        }
    }

    cout<<"\n number of comparisons = "<<sorting_method.get_numberofcomparisons()<<endl;
    cout<<"\n number of node's moving = "<<sorting_method.get_numberofnodemoving()<<endl;

    /* *  clean the space * */
    clean_memory(Memory_instance, Input_Amount_I);

    return 0;
}

void clean_memory(int **array2D, int n_size)
{//clean_memory
    if(n_size <= 0) exit(-1024);
    for(int n = 0; n < n_size; n++){delete array2D[n]; array2D[n]  = NULL;}
    delete array2D; array2D = NULL;
}//clean_memory

int Interleave_items(int *sequence, int num_items)
{//Interleave_items
    /* the number of items which needs to sort is in [0] */
    if(sequence[0] < 2 || sequence[0] > num_items) exit(-64);//if item' number less than 2
    int cursor = 1;
    while(cursor < sequence[0])
    {
        sequence[cursor] = cursor * (-1);
        cursor = cursor + 2;
    }
    return sequence[0];
}//Interleave_items


