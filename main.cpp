#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std; 

struct FileNotFound {
	string message;
	string filename;
	
};

vector<string> load_words(string filename);
void display(pair<string, int> p);
bool over_1(pair<string, int> p);

int main()
{
	cout << "Welcome to my Word Analyzer App!\n\n";
	string filename= "";
	cout << "Enter a file name: ";
	cin >> filename;
	
	vector<string> words;

	try
	{
		words = load_words(filename);
	}
	catch (const FileNotFound e )
	{
		cout << e.message << "\n";
		cout << "You entered: " << e.filename << "!\n";
		cout << "Closing program...\n\n";
		return 0;
	}

	cout << "\n";
	cout << words.size() << " WORDS:\n";
	for (string word : words){
		cout << word << ' ';
	}
	
	cout << "\n\n";

	string longestWord = "";
	for (string word : words)
	{
		if (word.length() > longestWord.length()) {
			longestWord = word;
			
		}
	}

	cout << "Longest Word: " << longestWord << "\n\n";
	string searchWord = "";

	cout << "Enter a word to search for: ";
	cin >> searchWord;
	
	int count = 0;

	for (string word : words)
	{
		if (word.find(searchWord) != string::npos){
			count++;
		}
	}

	cout <<searchWord << " appears " << count << " time(s)\n\n";

	vector<pair<string, int>> word_counts;

for (string word : words)
{
    bool found = false;

    for (auto& p : word_counts)
    {
        if (p.first == word)
        {
            p.second++;
            found = true;
            break;
        }
    }

    if (!found)
    {
        word_counts.push_back({word, 1});
    }
}

for_each(word_counts.begin(), word_counts.end(), display);

int duplicateCount = count_if(word_counts.begin(), word_counts.end(), over_1);

cout << duplicateCount << " duplicate words\n\n";

	return 0;
}
//load words from the file into a vector
vector<string> load_words(string filename)
{
	vector<string> words;
	ifstream inputfile(filename);

	if (inputfile){
		string word;
		while (inputfile >> word){
			words.push_back(word);
		}
		inputfile.close();
		return words;
	} else 
	{
		FileNotFound error;
		error.message = "File not found!";
		error.filename = filename;
		throw error;
	}
}


void display(pair<string, int> p)
{
	cout << p.first << "=" << p.second << endl;
}
bool over_1(pair<string, int> p)
{
	if (p.second > 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

