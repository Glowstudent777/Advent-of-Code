/*****
 * Author: Glowstudent
 * Day 3: Mull It Over
 *****/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

void partTwo()
{
    ifstream inFile;
    string s;

    int sum = 0;
    bool mul_enabled = true;

    smatch m;
    regex e(R"(mul(\(([0-9]+),([0-9]+)\)))");
    regex control_pattern(R"(do\(\)|don't\(\))");
    regex iteratorReg(R"(do\(\)|don't\(\)|mul\(([0-9]+),([0-9]+)\))");

    inFile.open("../inputs/puzzle.txt");

    if (!inFile)
    {
        cout << "Error opening file" << endl;
        return;
    }

    string input((istreambuf_iterator<char>(inFile)),
                 istreambuf_iterator<char>());

    inFile.close();

    auto matches_begin = sregex_iterator(input.begin(), input.end(), iteratorReg);
    auto matches_end = sregex_iterator();

    if (matches_begin == matches_end)
    {
        cout << "No matches found.\n";
    }
    else
    {
        for (auto it = matches_begin; it != matches_end; ++it)
        {
            // Extract the entire match and groups
            smatch match = *it;
            string matched_text = match.str();

            if (regex_match(matched_text, control_pattern))
            {
                if (matched_text == "do()")
                {
                    mul_enabled = true;
                }
                else
                {
                    mul_enabled = false;
                }
            }
            else if (regex_match(matched_text, e))
            {
                if (!mul_enabled)
                {
                    continue;
                }
                string first_num = match.str(1);
                string second_num = match.str(2);

                sum += (stoi(first_num) * stoi(second_num));
            }
        }
    }

    cout << "Sum: " << sum << endl;

    return;
}

void partOne()
{
    ifstream inFile;
    string s;

    int sum = 0;

    smatch m;
    // regex e{R"~(([^[]+)\[([^=]+)="([^"]+)"\])~"};
    // regex e{R"~((mul)(\(([0-9]+),([0-9]+)\)))~"};
    regex e(R"(mul(\(([0-9]+),([0-9]+)\)))");

    // mul\([0-9]+,[0-9]+\) scope: gm
    // (mul)(\(([0-9]+),([0-9]+)\))
    // https://cplusplus.com/forum/beginner/150992/

    inFile.open("../inputs/puzzle.txt");

    if (!inFile)
    {
        cout << "Error opening file" << endl;
        return;
    }

    string input((istreambuf_iterator<char>(inFile)),
                 istreambuf_iterator<char>());

    inFile.close();

    auto matches_begin = sregex_iterator(input.begin(), input.end(), e);
    auto matches_end = sregex_iterator();

    if (matches_begin == matches_end)
    {
        cout << "No matches found.\n";
    }
    else
    {
        for (auto it = matches_begin; it != matches_end; ++it)
        {
            // Extract the entire match and groups
            smatch match = *it;
            string first_num = match.str(2);
            string second_num = match.str(3);

            sum += (stoi(first_num) * stoi(second_num));
        }
    }

    cout << "Sum: " << sum << endl;

    return;
}

int main()
{
    partOne();
    partTwo();

    return 0;
}