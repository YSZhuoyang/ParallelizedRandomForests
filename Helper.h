
#ifndef _HELPER_H_
#define _HELPER_H_

#include "BasicDataStructures.h"
#include <stdlib.h>
#include <math.h>


using namespace std;
using namespace BasicDataStructures;

namespace MyHelper
{
    int Compare(
        const void* eleX,
        const void* eleY,
        void* featureId );
    // int Compare(
    //     const void* eleX,
    //     const void* eleY );
    bool StrEqualCaseSen( const char* str1, const char* str2 );
    bool StrEqualCaseInsen( const char* str1, const char* str2 );
    // Include string terminator
    unsigned int GetStrLength( const char* str );
    bool IsLetter( const char c );
    double* Tokenize(
        const char* str, 
        const vector<NumericAttr>& featureVec );

    unsigned int getIndexOfMax(
        const unsigned int* uintArray, 
        const unsigned int length );
    // Consume a sorted array, remove duplicates in place, 
    // and return the number of unique elements.
    unsigned int removeDuplicates(
        double* sortedArr,
        unsigned int length );
}

#endif
