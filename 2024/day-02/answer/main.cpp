/*****
 * Author: Glowstudent
 * Day 2: Red-Nosed Reports
 *****/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> splitString(string str, char dilem = ' ')
{
    vector<int> vec;
    string temp = "";

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == dilem)
        {
            vec.push_back(stoi(temp));
            temp = "";
        }
        else
        {
            temp += str[i];
        }
    }

    vec.push_back(stoi(temp));

    return vec;
}

bool testVector(vector<int> v)
{
    bool valid = true;

    for (int j = 0; j < v.size(); j++)
    {
        if (!valid) // If the report is already invalid, no need to check further
            break;

        if ((j != v.size() - 1) && (abs(v[j] - v[j + 1]) <= 0 || abs(v[j] - v[j + 1]) > 3))
        {
            valid = false;
            break;
        }

        if ((j > 0 && j != v.size() - 1) && !((v[j] > v[j + 1] && v[j - 1] > v[j]) || (v[j] < v[j + 1] && v[j - 1] < v[j])))
        {
            valid = false;
            break;
        }
    }

    return valid;
}

bool testVecorWithMercy(vector<int> v, bool removedAtLeastOne = false)
{
    bool valid = true;
    bool redo = false;

    for (int j = 0; j < v.size(); j++)
    {
        if (!valid) // If the report is already invalid, no need to check further
            break;

        if ((j != v.size() - 1) && (abs(v[j] - v[j + 1]) <= 0 || abs(v[j] - v[j + 1]) > 3))
        {
            if (removedAtLeastOne)
            {
                valid = false;
            }
            else
            {
                // v.erase(v.begin() + j);
                removedAtLeastOne = true;
                redo = true;
            }
            break;
        }

        if ((j > 0 && j != v.size() - 1) && !((v[j] > v[j + 1] && v[j - 1] > v[j]) || (v[j] < v[j + 1] && v[j - 1] < v[j])))
        {
            if (removedAtLeastOne)
            {
                valid = false;
            }
            else
            {
                // v.erase(v.begin() + j);
                removedAtLeastOne = true;
                redo = true;
            }
            break;
        }
    }

    if (redo)
    {
        for (int i = 0; i < v.size(); i++)
        {
            vector<int> temp = v;

            temp.erase(temp.begin() + i);
            if (testVecorWithMercy(temp, true))
            {
                valid = true;
                break;
            }
            else
            {
                valid = false;
            }

            // cout << "Safe Report: ";
            // for (int j = 0; j < temp.size(); j++)
            // {
            //     cout << temp[j] << " ";
            // }
            // cout << endl;
        }
    }

    return valid;
}

void partTwo(vector<string> nums)
{
    int safeReports = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        vector<int> v;
        string str = nums[i];

        bool valid = true;

        v = splitString(str, ' ');

        if (testVecorWithMercy(v))
        {
            safeReports++;
        }
    }

    cout << "Safe Reports: " << safeReports << endl;
    return;
}

void partOne()
{
    ifstream inFile;
    string s;
    vector<string> nums;
    int safeReports = 0;

    inFile.open("../inputs/puzzle.txt");

    if (!inFile)
    {
        cout << "Error opening file" << endl;
        return;
    }

    while (getline(inFile, s))
    {
        if (s == "")
            continue;

        nums.push_back(s);
    }
    inFile.close();

    for (int i = 0; i < nums.size(); i++)
    {
        vector<int> v;
        string str = nums[i];

        bool valid = true;

        v = splitString(str, ' ');

        if (testVector(v))
            safeReports++;
    }

    cout << "Safe Reports: " << safeReports << endl;

    partTwo(nums);

    return;
}

int main()
{
    partOne();

    return 0;
}