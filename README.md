# cs3358_abm_assignment1
This is "Assignment #1" from professor L.Koh's CS3358 Data Structures &amp; Algorithms class in Fall 2017

Assignment Active Dates: 8/30/17 - 09/13/17

Original Problem Description: http://cs.txstate.edu/~lk04/3358/Assign/Assign01.html

Grade Received: 98% (Returned 09/18/17)

Grading Sheet: http://cs.txstate.edu/~lk04/3358/Assign/Assign01PenaltyTallySheet.pdf
Grade Reasoning: 

Issue with IntSet::remove(int anInt) for being out of bounds when shifting elements after 
an element is removed. Fixed in assignment #2, look at updated IntSet::remove(int anInt).

bool IntSet::remove(int anInt)
{
    // If the intSet has the requested element in the set then
    // remove it, and shift all elements to the left by one.
    if(contains(anInt)){
        for(int index = 0; index < size(); index++){
            if(data[index] == anInt) {
                for(int index2 = index; index2 < size(); index2++) {
                    data[index2] = data[index2 + 1]; <------------------ Lost points for this line!
                }
                used--;
                return true; // Int removed successfully.
            }
        }
    }
    return false; // No int removed.
}
