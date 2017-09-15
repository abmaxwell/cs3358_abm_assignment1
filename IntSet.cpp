// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     compile-time array whose size is IntSet::MAX_SIZE;
//     the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[IntSet::MAX_SIZE - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;


// Default Constructor
IntSet::IntSet() : data(), used(0){}

int IntSet::size() const
{
    // Return the value of used which is
    // the number of elements in the array.
    return used;
}

bool IntSet::isEmpty() const
{
    // Empty if size() == 0, has unique int otherwise.
    return this->size() == 0;
}

bool IntSet::contains(int anInt) const
{
    // Only traverse array if there are int's to check, otherwise
    // return false because there's no int's to compare with.
    if (used > 0){
        for(int index = 0; index < used; index++)
            if(data[index] == anInt){ return true; }
    }
    return false;
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
    if(this->isEmpty()) {

        // Check to see if the invoking IntSet
        // is empty. If it is then return true.
        return true;

    } else {

        // Check otherIntSet against invoking intSet to
        // determine if it's a subset of otherIntSet. If
        // there's a mismatch abort and return false.
        for(int index = 0; index < this->size(); index++){
            if(!otherIntSet.contains(this->data[index])){ return false; }
        }
        return true;
   }
}

void IntSet::DumpData(ostream& out) const
{
    if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
    // Check to make sure the current IntSet + otherIntSet when
    // unioned will be at MAX_SIZE or below.
    assert(size() + (otherIntSet.subtract(*this)).size() <= MAX_SIZE);

    IntSet unionIntSet = (*this); //Copy of invoking IntSet.

    // Loop through IntSet to be added to invoking set. If duplicate
    // elements found don't union, otherwise union unique elements.
    for (int index = 0; index < otherIntSet.size(); ++index) {
        if(!unionIntSet.contains(otherIntSet.data[index])){
            unionIntSet.add(otherIntSet.data[index]);
        }
    }
    return unionIntSet;
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
    IntSet interSet = (*this); // Create copy of invoking IntSet

    // Compare every item of invoking IntSet to otherIntSet
    // if no match is found then remove it from interSet.
    for (int index = 0; index < size(); index++) {
        if(!otherIntSet.contains(data[index])){
            interSet.remove(data[index]);
        }
    }
    return interSet;
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
    IntSet subSet = (*this); // Create copy of invoking IntSet.

    // If an element in intSet is also in otherSet then remove
    // it, otherwise keep elements in their respective sets.
    for(int index = 0; index < otherIntSet.size(); index++){
        if(subSet.contains(otherIntSet.data[index])){
            subSet.remove(otherIntSet.data[index]);
        }
    }
    return subSet; // Return subtracted IntSet.
}

void IntSet::reset()
{
    // Reset intSet by reinitializing used to "0".
    used = 0;
}

bool IntSet::add(int anInt)
{
    // Check for program to make sure we are under MAX_SIZE and there's
    // not a duplicate int.
    assert((contains(anInt)) ? size() <= MAX_SIZE : size() < MAX_SIZE);

    // If anInt is unique then add it as
    // the last element in the data array
    // and return true.
    if(!contains(anInt)){
        data[used] = anInt;
        used++;
        return true;
    }
    // No unique int's added to data
    // array return false.
    return false;
}

bool IntSet::remove(int anInt)
{
    // If the intSet has the requested element in the set then
    // remove it, and shift all elements to the left by one.
    if(contains(anInt)){
        for(int index = 0; index < size(); index++){
            if(data[index] == anInt) {
                for(int index2 = index; index2 < size(); index2++) {
                    data[index2] = data[index2 + 1];
                }
                used--;
                return true; // Int removed successfully.
            }
        }
    }
    return false; // No int removed.
}

bool equal(const IntSet& is1, const IntSet& is2)
{
    // If is2 is a subset of is1, and is1 is a subset of is2
    // then every element in is1 must be in is2 and vice-versa.
    if(is1.IntSet::isSubsetOf(is2) && is2.IntSet::isSubsetOf(is1)) {
        return true;
    }
    return false;
}
