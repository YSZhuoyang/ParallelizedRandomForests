
#include "Helper.h"


void MyHelper::SwapInst(
    vector<Item>& iv,
    int* feaValueArray,
    const unsigned int first,
    const unsigned int second )
{
    // Swap feature value
    int tempVal = feaValueArray[first];
    feaValueArray[first] = feaValueArray[second];
    feaValueArray[second] = tempVal;

    // Swap instance data
    Item tempInst = iv[first];
    iv[first] = iv[second];
    iv[second] = tempInst;
}

void MyHelper::QSortInstances(
    vector<Item>& iv,
    int* feaValueArray,
    const unsigned int left,
    const unsigned int right )
{
    if (left >= right) return;

    int slow = left;
    // Shift pivot to the left.
    SwapInst( iv, feaValueArray, left, (left + right) >> 1 );

    for (unsigned int fast = left + 1; fast <= right; fast++)
        if (feaValueArray[fast] < feaValueArray[left])
            SwapInst( iv, feaValueArray, ++slow, fast );

    // Shift pivot back.
    SwapInst( iv, feaValueArray, left, slow );
    if (slow > 0) QSortInstances( iv, feaValueArray, left, slow - 1 );
    QSortInstances( iv, feaValueArray, slow + 1, right );

    /*if (right - left <= 1)
    {
        if (feaValueArray[right] < feaValueArray[left])
            SwapInst( iv, feaValueArray, left, right );
        
        return;
    }

    const unsigned int middle = (left + right) >> 1;
    const int pivot = feaValueArray[middle];
    unsigned int lIter = left;
    unsigned int rIter = right;

    while (lIter < rIter)
    {
        while (feaValueArray[lIter] < pivot) lIter++;
        while (feaValueArray[rIter] > pivot) rIter--;
        
        SwapInst( iv, feaValueArray, lIter, rIter );
        lIter++;
        rIter--;
    }

    QSortInstances( iv, feaValueArray, left, middle );
    QSortInstances( iv, feaValueArray, middle, right );*/
}

int MyHelper::Compare( const void* ele1, const void* ele2 )
{
    return (*((int*) ele1) - *((int*) ele2) );
}

Item MyHelper::Tokenize(
    const char* str, 
    const vector<NumericAttr>& featureVec )
{
    unsigned int numFeatures = featureVec.size();
    Item item;
    item.featureAttrArray = 
        (int*) calloc( numFeatures, sizeof( int ) );

    unsigned int iter = 0;

    while (str[iter] != '\0')
    {
        unsigned int startIndex = iter;

        while (IsLetter( str[iter] ))
            iter++;

        // Found a token
        if (iter > startIndex)
        {
            unsigned int tokenLen = iter - startIndex;

            // Compare the token with every feature name
            // Might use a hashmap (with key: name, value: index) 
            // to speed up
            for (unsigned int feaIndex = 0;
                feaIndex < numFeatures; feaIndex++)
            {
                const char* feaName = featureVec[feaIndex].name;

                unsigned index = 0;
                while (index < tokenLen && feaName[index] != '\0'
                    && (feaName[index] == str[startIndex + index] ||
                    feaName[index] == str[startIndex + index] + 32))
                    index++;
                
                if (index == tokenLen && feaName[index] == '\0')
                    item.featureAttrArray[feaIndex]++;
            }
        }

        if (str[iter] != '\0') iter++;
    }

    return item;
}

bool MyHelper::IsLetter( const char c )
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || 
        c == '\?' || c == '_');
}

bool MyHelper::StrEqual( const char* str1, const char* str2 )
{
    unsigned short i = 0;
    while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]) i++;

    return (str1[i] == '\0' && str2[i] == '\0') ? true : false;
}

unsigned int MyHelper::GetStrLength( const char* str )
{
    unsigned int len = 0;

    while (str[len++] != '\0');

    return len;
}

unsigned int MyHelper::getIndexOfMax(
    const unsigned int* uintArray, 
    const unsigned int length )
{
    if (uintArray == nullptr || length <= 0) return 0;

    unsigned int indexOfMax = 0;
    unsigned int max = 0;

    for (unsigned int i = 0; i < length; i++)
    {
        if (uintArray[i] > max)
        {
            indexOfMax = i;
            max = uintArray[i];
        }
    }

    return indexOfMax;
}

int MyHelper::removeDuplicates(
    int* sortedArr, 
    unsigned int length )
{
    if (sortedArr == nullptr) return 0;

    unsigned int uniqueId = 1;
    unsigned int iter = 1;

    while (iter < length)
    {
        if (sortedArr[iter - 1] != sortedArr[iter])
            sortedArr[uniqueId++] = sortedArr[iter];

        iter++;
    }

    return uniqueId;
}
