/*****
 * Author: Glowstudent
 * Day 1: Historian Hysteria
 *****/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

bool sortAsc(int i, int j)
{
    return (i < j);
};

int calculateDifference(vector<int> &left, vector<int> &right)
{
    int sum = 0;

    sort(left.begin(), left.end(), sortAsc);
    sort(right.begin(), right.end(), sortAsc);

    for (int i = 0; i < left.size(); i++)
    {
        sum += abs(left[i] - right[i]);
    }

    return sum;
}

void partTwo(vector<int> &left, vector<int> &right)
{
    int similarityScore = 0;
    int count = 0;

    for (int i = 0; i < left.size(); i++)
    {
        for (int j = 0; j < right.size(); j++)
        {
            if (left[i] == right[j])
            {
                count++;
            }
        }
        similarityScore += (count * left[i]);
        count = 0;
    }

    cout << "The similarity score is: " << similarityScore << endl;

    return;
}

void partOne()
{
    ifstream inFile;
    string s;
    vector<int> left, right;
    int sum = 0, count = 0;

    inFile.open("../inputs/puzzle.txt");

    if (!inFile)
    {
        cout << "Error opening file" << endl;
        return;
    }

    while (getline(inFile, s))
    {
        int lnum, rnum;

        if (s == "")
        {
            continue;
        }

        count++;

        lnum = stoi(s.substr(0, s.find(" ")));
        rnum = stoi(s.substr(s.find(" ") + 1));

        left.push_back(lnum);
        right.push_back(rnum);
    }
    inFile.close();

    sum = calculateDifference(left, right);
    cout << "The sum of the differences is: " << sum << endl;

    partTwo(left, right);

    return;
}

int main()
{
    partOne();

    return 0;
}