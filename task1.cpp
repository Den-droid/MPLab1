#include <iostream>
#include <fstream>
using namespace std;

int main() {
	const int N = 25;
	const int numOfStopWords = 8;
	const char* stopWords[] = { "the", "for", "a", "an", "at", "on", "in", "of" };

	int countAllWords = 0;
	ifstream in;
	in.open("test.txt");
	if (in.is_open())
	{
		char symb;
	wordsCount:
		symb = in.get();
		if (symb == ' ' || symb == '\n')
			countAllWords++;
		if (in)
			goto wordsCount;
	endWordsCount:
		countAllWords++;
		in.close();
	}

	string* words = new string[countAllWords];
	int* numOfWords = new int[countAllWords];
	bool isWord = false;
	int wordCount = 0;
	in.open("test.txt");
	if (in.is_open())
	{
		string str = "";
		char symb;
	throughFile:
		symb = in.get();
		if (symb >= 65 && symb <= 90)
			symb += 32;
		if ((symb >= 97 && symb <= 122) || (isWord && (symb == '-' || symb == '\''))) {
			isWord = true;
			str += symb;
		}
		else if (symb == ',' || symb == ':' || symb == ';' || symb == '!' || symb == '?' || symb == '.' || symb == ' ') {
			if (isWord)
			{
				isWord = false;

				int stopIndex = 0;
				int dupIndex = 0;
			lookForStopWords:
				if (stopIndex == numOfStopWords)
					goto lookForDuplicates;
				if (stopWords[stopIndex] == str) {
					str = "";
					goto throughFile;
				}
				stopIndex++;
				goto lookForStopWords;
			lookForDuplicates:
				if (wordCount == dupIndex)
					goto endCheckup;
				if (words[dupIndex] == str)
				{
					numOfWords[dupIndex]++;
					str = "";
					goto throughFile;
				}
				dupIndex++;
				goto lookForDuplicates;
			endCheckup:
				words[wordCount] = str;
				numOfWords[wordCount] = 1;
				str = "";
				wordCount++;
			}
		}
		if (in)
			goto throughFile;
	endThroughFile:
		in.close();
	}

	int firstIndex = 0;
	int secondIndex = 0;
bubble:
	if (firstIndex == wordCount - 1)
		goto show;
	if (numOfWords[secondIndex] < numOfWords[secondIndex + 1]) {
		string temp = words[secondIndex];
		words[secondIndex] = words[secondIndex + 1];
		words[secondIndex + 1] = temp;
		int tempNum = numOfWords[secondIndex];
		numOfWords[secondIndex] = numOfWords[secondIndex + 1];
		numOfWords[secondIndex + 1] = tempNum;
	}
	secondIndex++;
	if (secondIndex == wordCount - firstIndex - 1) {
		secondIndex = 0;
		firstIndex++;
	}
	goto bubble;
show:
	int endIndex = N;
	if (wordCount < endIndex)
		endIndex = wordCount;
	int index = 0;
resShow:
	if (index == endIndex)
		goto end;
	cout << words[index] << " - " << numOfWords[index] << endl;
	index++;
	goto resShow;
end:
	delete[] numOfWords;
	delete[] words;
	return 0;
}