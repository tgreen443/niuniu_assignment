/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include "queue.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
Queue<int> binaryMerge(Queue<int> a, Queue<int> b) {
    int aLen =a.size();
    int bLen =b.size();
    Queue aTep = a;
    Queue bTep = b;
    for(int i=0;i<aLen-1;i++){
        if(aTep.dequeue()>aTep.peek()){
            error("the queue a is unsorted ");
        }
    }
    for(int i=0;i<bLen-1;i++){
        if(bTep.dequeue()>bTep.peek()){
            error("the queue b is unsorted ");
        }
    }
    Queue<int> result;
    while(!a.isEmpty()){
        if(!b.isEmpty()){
            result.enqueue(a.peek()>b.peek()? b.dequeue() : a.dequeue() );
        }
        else{
            result.enqueue(a.dequeue());
        }


    }
    while(!b.isEmpty()){
        result.enqueue(b.dequeue());
    }
   return result;
}
/*
 * This function assumes correct functionality of the previously
 * defined binaryMerge function and makes use of this function to
 * iteratively merge a collection of sequences, starting off with
 * an empty sequence and progressively merging in one sequence at
 * a time. This function is provided for you fully implemented –
 * it does not need to modified at all.
 */
Queue<int> naiveMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;

    for (Queue<int>& q : all) {
        result = binaryMerge(q, result);
    }
    return result;
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
Queue<int> recMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;
    int aLen = all.size();
    if (all.isEmpty()){
        return {};
    }
    if (aLen==1){
        return all[0];
    }
    else{
        if(aLen==2){
            return binaryMerge(all[0],all[1]);
        }
        else{
            auto head = all.subList(0,aLen/2);
            auto tail = all.subList(aLen/2,aLen-aLen/2);
            return binaryMerge(recMultiMerge(head),recMultiMerge(tail));
        }
    }
}


/* * * * * * Test Cases * * * * * */

Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);

PROVIDED_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

PROVIDED_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

PROVIDED_TEST("recMultiMerge, compare to naiveMultiMerge") {
    int n = 20;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
}

PROVIDED_TEST("Time binaryMerge operation") {
    int n = 1000000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
}

PROVIDED_TEST("Time naiveMultiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), naiveMultiMerge(all));
}
PROVIDED_TEST("Time recMultiMerge operation") {
    int n = 90000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}


/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size) {
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}

/* Test helper to distribute elements of sorted sequence across k sequences,
   k is size of Vector */
void distribute(Queue<int> input, Vector<Queue<int>>& all) {
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size()-1)].enqueue(input.dequeue());
    }
}


STUDENT_TEST("binaryMerge test ") {
    Queue<int> a = {1,2, 2, 4, 4, 5, 8 ,9 };
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1,1, 2,2, 3, 3, 4, 4, 5 , 8 , 9};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}
STUDENT_TEST("naiveMultiMerge  empty vector") {
    Vector<Queue<int>> all = {};
    Queue<int> expected = {};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
    Vector<Queue<int>> allEmp = {{},{},{},{}};
    EXPECT_EQUAL(naiveMultiMerge(allEmp), expected);

}
