#ifndef CGSM_H_INCLUDED
#define CGSM_H_INCLUDED

#include <iostream>
#include <stdlib.h>

class CardGameSorting_Method
{
    private:
        int **Memory_2D; // the pointer of 2D array
        int the_Size; // the number of items in need of sorting
        int the_layer; // the number of row

        int *aid_list; // the pointer that points the address of aid array
        int the_Former; int the_Later; // the addresses of rows points the cellular storing the index of former or later
        int the_key; // the addresses of rows points the cellular storing the key
        int *key_list; // the pointer that points the address of key array
        int the_head; // the head of new sequence

        int statistics_comparison; // count the number of comparisons
        int statistics_nodemoving; // count the moving of node

        int Push_intoList(int *array_, int reference_); // push an index into aid list
        void Connect_TwoItems(int index_1, int index_2, bool direction); // connect two items as "<-" or "->"
        int Initialize_sequence(); // initialize the sequence into a set of components in which a small sorting subsequence is
        int Merge_method(int A_cursor, int B_cursor); // the engine to merge two samll subsequences into a bigger new one

    public:
        // initialize class with corresponding parameters
        CardGameSorting_Method(int **M, int S, int L): Memory_2D(M), the_Size(S), the_layer(L){
            the_key = the_layer - 4; key_list = Memory_2D[the_key];
            aid_list = Memory_2D[the_layer - 3];
            the_Former = the_layer - 2; the_Later = the_layer - 1; the_head = 0;
            statistics_comparison = 0; statistics_nodemoving = 0;
        }

        int test_ini(){return Initialize_sequence();}//test function used to test the result of initialization on sequence
        int Sorting(); // sorting sequence that includes building a linked list of items, their keys in ascent and return the head

        int get_theLater(int reference_); //return someone's later
        int get_theKeys(int reference_); //return someone's former
        int get_theHead(){return the_head;}

        int get_numberofcomparisons(){return statistics_comparison;} // return statistics of comparison
        int get_numberofnodemoving(){return statistics_nodemoving;} // return statistics of nodes' moving
};


#endif // CGSM_H_INCLUDED
