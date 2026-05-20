#include <iostream>
using namespace std;

int nSubsets, nElements;

// check if subset can be chosen (no element already covered)
bool canUse(int cover[][50], int usedElements[], int subset)
{
    for(int j = 0; j < nElements; j++)
    {
        if(cover[subset][j] == 1 && usedElements[j] == 1)
            return false;
    }
    return true;
}

// mark/unmark elements
void apply(int cover[][50], int usedElements[], int subset, int val)
{
    for(int j = 0; j < nElements; j++)
    {
        if(cover[subset][j] == 1)
            usedElements[j] = val;
    }
}

// backtracking
bool solve(int cover[][50], int usedElements[], int idx)
{
    // check if all elements are covered
    bool allCovered = true;
    for(int j = 0; j < nElements; j++)
    {
        if(usedElements[j] == 0)
        {
            allCovered = false;
            break;
        }
    }

    if(allCovered)
        return true;

    if(idx == nSubsets)
        return false;

    // choice 1: skip subset
    if(solve(cover, usedElements, idx + 1))
        return true;

    // choice 2: take subset (if valid)
    if(canUse(cover, usedElements, idx))
    {
        apply(cover, usedElements, idx, 1);

        if(solve(cover, usedElements, idx + 1))
            return true;

        apply(cover, usedElements, idx, 0); // backtrack
    }

    return false;
}

int main()
{
    nSubsets = 4;
    nElements = 5;

    /*
        cover[i][j] = 1 means subset i covers element j
    */
    int cover[50][50] =
    {
        {1, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1}
    };

    int usedElements[50] = {0};

    if(solve(cover, usedElements, 0))
        cout << "Exact cover exists";
    else
        cout << "No exact cover exists";

    return 0;
}