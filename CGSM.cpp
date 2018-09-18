#include "CGSM.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int CardGameSorting_Method::Push_intoList(int *array_, int reference_)
{//Push_intoList
    /* * in 0th cellular, leave down a counter to number the available items in array * */
    if(array_[0] >= the_Size) return -1;
    if(array_[0] < 0) array_[0] = 0;

    array_[0] ++; int index = array_[0]; array_[index] = reference_;

    return index; // return the position of fresh items in array
}//Push_intoList

void CardGameSorting_Method::Connect_TwoItems(int index_1, int index_2, bool direction)//true: index_1 <- intdex_2; false: index_1 -> intdex_2;
{//Connect_TwoItems
    int later = the_Later; int former = the_Former; // default is index_1 <--- index_2

    if(!direction){later = the_Former; former = the_Later;} //now is index_1 ---> index_2

    Memory_2D[later][index_1] = index_2; Memory_2D[former][index_2] = index_1; // do connecting

}//Connect_TwoItems

int CardGameSorting_Method::Initialize_sequence()
{//Initialize_sequence
    if(key_list[0] < 2 || key_list[0] > the_Size) exit(-64);

    /* * * parameters * * */
    bool course = false; // false: no in course; inverse to yes
    int manner = 0; // -1: is the "e1 > e2"; 1 is "e1 < e2" in course.
    int dirction = 0; //number the "<" or ">" in sequence.

    /* * * make components from a stochastics * * */
    statistics_nodemoving = key_list[0];
    for(int n = 1; n <= key_list[0]; n++)
    {//making component

        /* * * when cursor at the end and in "->" direction * * */
        if(n == key_list[0])//
        {
            if(!course || (course && manner < 0)) Push_intoList(aid_list, n);
            break;
        }

        /* * * manage the relation anomg n and n+1 or at the end of component * * */
        int check = 1;// defualt is "<"; -1 is ">"
        if(key_list[n] > key_list[n + 1]){check = -1; dirction --; statistics_comparison ++;}
        else {dirction ++; statistics_comparison ++;}
        check = check + manner;

        /* ********************************************** detail ************************************************* */
        /*                                                                                                         */
        /* A. check = 1; manner = 1; then check := 2 means in the "<" search course, can go on.                    */
        /* B. check = -1; manner = -1; then check := -2 means in the ">" search course, can go on.                 */
        /*                                                                                                         */
        /* C. check = 1; manner = -1; then check := 0 means at the head of a ">" subsequence.                      */
        /* D. check = -1; manner = 1; then check := 0 means at the tail of a "<" subsequence.                      */
        /*                                                                                                         */
        /* E. check = 1; manner = 0; then check := 1 means at the head of a "<" subsequence.                       */
        /* F. check = -1; manner = 0; then check := -1 means at the tail of a ">" subsequence.                     */
        /*                                                                                                         */
        /* ********************************************** detail ************************************************* */

        bool head = false; // signify: record the head of component.
        bool connection = false; // signify: connect n and n+1.
        bool type = true; // signify: the diretion of connection, defaut is "<---".

        if(course)//the course = 1;
        {//in
            /* * * a. check = 0, means the cursor at the end of component * * */
            if(!check)
            {//end
                if(manner < 0) head = true; // at C status, needing record the head of ">" sequence
                check = 0; manner = 0; course = 0;//C and D both reset status
            }//end
            /* * * b. check = 2 or -2, means the course proceed * * */
            else{//on
                connection = true; //A and B both do connecting
                if(manner < 0) type = false; // " ---> " style is false
            }//on
        }//in
        //the course = 0; not in course
        else{//no in
            connection = true; course = true; //E and F both do connecting
            manner = 1;//default is "<" direction

            if(check > 0) head = true;// record the head for "<" sequence
            else{
                type = false; // " ---> " style is false
                manner = -1;//set status for ">" direction
            }
        }//no in

        //manage items
        if(head)Push_intoList(aid_list, n); // record per head of every subsequence that in ascent
        if(connection)Connect_TwoItems(n, (n+1), type); // connect two neighbors

    }//making component
    if(dirction == (the_Size - 1))return 0; //sequence in ascent
    else if((dirction + the_Size) == 1) return -1;//sequence in descent

    return key_list[0];
}//Initialize_sequence

int CardGameSorting_Method::Merge_method(int A_cursor, int B_cursor)
{//Merge_method

    //A. find the head for future new bigger sequence
    int head = A_cursor; //default A_cursor is the of future new bigger sequence
    if (key_list[A_cursor] > key_list[B_cursor]) head = B_cursor;
    statistics_comparison ++;

    //B. comparing and sorting those items
    int x_cursor = A_cursor; int y_cursor = B_cursor; //make two cursors on two subsequences respectively

    while(y_cursor)
    {//loop
        statistics_comparison ++;
        if(key_list[x_cursor] < key_list[y_cursor])
        {//x<y
            if(Memory_2D[the_Later][x_cursor]) x_cursor = Memory_2D[the_Later][x_cursor]; //x walks on
            else{//x <= y, connect
                statistics_nodemoving ++;
                Connect_TwoItems(x_cursor, y_cursor, 1); //x <- y then the right rest of y also following the end of x
                break;
            }//x <= y, connect
        }//x<y
        else
        {//x>y, y inserted ahead of x

            // backup two items involved
            int x_former = Memory_2D[the_Former][x_cursor]; int y_follower = Memory_2D[the_Later][y_cursor];
            statistics_nodemoving ++;

            Connect_TwoItems(x_former, y_cursor, 1);//x_former <-> y_cursor
            Connect_TwoItems(y_cursor, x_cursor, 1);//y_cursor <-> x_cursor

            y_cursor = y_follower;//y walks on
        }//x>y, insertinsert
    }//loop

    return head;
}//Merge_method

int CardGameSorting_Method::Sorting()
{//Sorting
    int flag = Initialize_sequence();

    if(flag <= 0){
        if(flag < 0){
           cout<<"\n the list has been in descent"<<endl; return the_Size;
        }
        cout<<"\n the list has been in ascent"<<endl;
        return 1;
    }
    the_head = 0; // the head of new sequence
    int counter = 0; // record the index when a new item push into
    int cursor = 1; // move cursor to fetch those items in aid_list
    int qty = aid_list[0]; // the quantity of items in aid_list

    while(qty > 1)
    {//loop
        int next = cursor + 1; // get two cursors
        the_head = Merge_method(aid_list[cursor], aid_list[next]); // do merger
        counter ++; aid_list[counter] = the_head; aid_list[0] = counter; // backup the head of new bigger sequence

        cursor = cursor + 2; // leap to the next new index
        if(cursor >= qty)
        {//at the end
            if(cursor == qty){ // if qty is odd, then directly back up the end one for next
                counter ++; aid_list[counter] = aid_list[cursor]; aid_list[0] = counter;
            }

            //update the parameters for next round
            qty = aid_list[0]; if(qty <= 1) break;
            cursor = 1;  counter = 0;
        }//at the end

    }//loop
    return the_head;
}//Sorting

int CardGameSorting_Method::get_theLater(int reference_)
{//get_theLater
    if(reference_ <= 0 || reference_ > the_Size) return -1;
    return Memory_2D[the_Later][reference_];
}//get_theLater

int CardGameSorting_Method::get_theKeys(int reference_)
{//get_theKeys
    if(reference_ <= 0 || reference_ > the_Size) return -1;
    return Memory_2D[the_key][reference_];
}//get_theKeys




