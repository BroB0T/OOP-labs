#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>

using namespace std;

multimap<string, int> wordIndex;

string normalizeRow(const string& rawRow)
{
    string result;
    result.reserve(rawRow.size());

    for (int i = 0; i < rawRow.size(); ++i)
    {
        char c = rawRow[i];

        if (isalnum(c))
        {
            result.push_back(tolower(c));
        }
        else
        {
            while (i < rawRow.size() && !isalnum((char)rawRow[i])) 
            {
                i++;
            }

            if (!result.empty()) result.push_back(' ');
            i--;
        }
    }
    return result;
}

vector<string> splitIntoLines(const string& inputText)
{
    vector<string> lines;
    string current;

    for (char c : inputText)
    {
        if (c == '.')
        {
            lines.push_back(current);
            current.clear();
        }
        else current.push_back(c);
    }
    lines.push_back(current);
    return lines;
}

void extractWords(const string& rawLine, int lineNumber)
{
    string normalizedLine = normalizeRow(rawLine);
    istringstream lineStream(normalizedLine);

    set<string> uniqueWords;
    string currentWord;

    while (lineStream >> currentWord)
    {
        uniqueWords.insert(currentWord);
    }

    for (set<string>::const_iterator i = uniqueWords.begin(); i != uniqueWords.end(); i++)
    {
        wordIndex.emplace(*i, lineNumber);
    }
}

void searchWord()
{
    cout << "Enter word to search\nEnter empty line to exit:\n";

    string userQuery;
    while (getline(cin, userQuery) && !userQuery.empty())
    {
        string normalized = normalizeRow(userQuery);
        if (normalized.empty())
        {
            cout << "Invalid input. Try again:\n";
            continue;
        }

        multimap<string, int>::iterator iterator = wordIndex.find(normalized);

        if (iterator == wordIndex.end())
        {
            cout << "Word \"" << normalized << "\" not found.\n";
        }
        else
        {
            cout << "Word \"" << normalized << "\" found in lines: ";

            multimap<string, int>::iterator upper = wordIndex.upper_bound(normalized);

            bool isFirst = true;
            for (; iterator != upper; iterator++)
            {
                if (!isFirst) cout << ", ";
                cout << (*iterator).second;
                isFirst = false;
            }
            cout << "\n";
        }
    }
}


int main()
{
    cout << "Enter text:\n";

    string inputText;
    getline(cin, inputText);

    vector<string> lines = splitIntoLines(inputText);

    for (int i = 0; i < lines.size(); i++)
    {
        extractWords(lines[i], i + 1);
    }

    cout << "Index built for " << lines.size() << " lines\n";

    searchWord();

    return 0;
}
