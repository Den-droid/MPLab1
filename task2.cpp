#include <iostream>
#include <fstream>
using namespace std;

int main() {
	const int rowsToPage = 45;
	const int numLimit = 100;

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
	int** pagesNumber = new int* [countAllWords];
	int* wordsCount = new int[countAllWords];
	int pageIndex = 0;
initPagesNumber:
	if (pageIndex == countAllWords)
		goto endInit;
	pagesNumber[pageIndex] = new int[numLimit];
	pageIndex++;
	goto initPagesNumber;
endInit:
	bool isWord = false;
	int wordCount = 0;
	int row = 1;
	int page = 1;
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
		else if (symb == ',' || symb == ':' || symb == ';' || symb == '!' || symb == '?' || symb == '.' || symb == ' ' || symb == '\n') {
			if (symb == '\n') {
				row++;
				page = (row / rowsToPage) + 1;
			}
			if (isWord)
			{
				isWord = false;

				int dupIndex = 0;
			lookForDuplicates:
				if (wordCount == dupIndex)
					goto endCheckup;
				if (words[dupIndex] == str)
				{
					pagesNumber[dupIndex][wordsCount[dupIndex]] = page;
					wordsCount[dupIndex]++;
					str = "";
					goto throughFile;
				}
				dupIndex++;
				goto lookForDuplicates;
			endCheckup:
				words[wordCount] = str;
				wordsCount[wordCount] = 0;
				pagesNumber[wordCount][wordsCount[wordCount]++] = page;
				str = "";
				wordCount++;
			}
		}
		if (in)
			goto throughFile;
	endThroughFile:
		in.close();
	}

	int throughIndex = 0;
excluding100andMore:
	if (throughIndex == wordCount)
		goto sort;
	if (wordsCount[throughIndex] >= numLimit)
	{
		int indexArray = throughIndex;
	arrayDecrease:
		if (indexArray == wordCount - 1)
			goto afterArrayDecr;
		words[indexArray] = words[indexArray + 1];
		wordsCount[indexArray] = wordsCount[indexArray + 1];
		pagesNumber[indexArray] = pagesNumber[indexArray + 1];
		indexArray++;
		goto arrayDecrease;
	afterArrayDecr:
		wordCount--;
	}
	throughIndex++;
	goto excluding100andMore;

sort:
	int firstIndex = 0;
	int secondIndex = 0;
bubble:
	int strIndex = 0;
	bool firstMoreSecond = false;
	if (firstIndex == wordCount - 1)
		goto showRes;
strComp:
	if (words[secondIndex][strIndex] == '\0')
	{
		firstMoreSecond = false;
		goto afterStrComp;
	}
	else if (words[secondIndex + 1][strIndex] == '\0')
	{
		firstMoreSecond = true;
		goto afterStrComp;
	}
	if (words[secondIndex][strIndex] > words[secondIndex + 1][strIndex])
	{
		firstMoreSecond = true;
		goto afterStrComp;
	}
	else if (words[secondIndex][strIndex] < words[secondIndex + 1][strIndex])
	{
		firstMoreSecond = false;
		goto afterStrComp;
	}
	strIndex++;
	goto strComp;
afterStrComp:
	if (firstMoreSecond) {
		string word = words[secondIndex];
		words[secondIndex] = words[secondIndex + 1];
		words[secondIndex + 1] = word;
		int tempCount = wordsCount[secondIndex];
		wordsCount[secondIndex] = wordsCount[secondIndex + 1];
		wordsCount[secondIndex + 1] = tempCount;
		int* tempPagesNumber = pagesNumber[secondIndex];
		pagesNumber[secondIndex] = pagesNumber[secondIndex + 1];
		pagesNumber[secondIndex + 1] = tempPagesNumber;
	}
	secondIndex++;
	if (secondIndex == wordCount - firstIndex - 1) {
		secondIndex = 0;
		firstIndex++;
	}
	goto bubble;

showRes:
	int firstIndexShowRes = 0;
	int secondIndexShowRes = 0;
res:
	if (firstIndexShowRes == wordCount)
		goto end;
	if (secondIndexShowRes == 0)
		cout << words[firstIndexShowRes] << " - ";
	cout << pagesNumber[firstIndexShowRes][secondIndexShowRes];
	if (secondIndexShowRes != wordsCount[firstIndexShowRes] - 1)
		cout << ", ";
	secondIndexShowRes++;
	if (secondIndexShowRes == wordsCount[firstIndexShowRes]) {
		cout << endl;
		firstIndexShowRes++;
		secondIndexShowRes = 0;
	}
	goto res;
end:
	delete[] pagesNumber;
	delete[] words;
	delete[] wordsCount;

	return 0;
}