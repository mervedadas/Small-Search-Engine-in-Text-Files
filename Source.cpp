#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<ctype.h>
#include"Doc.h"
using namespace std;
Doc occurStopList(string);
void specialChar(string&);
string lower(string &a) {
	int i = 0;
	char c;
	string d;
	while (a[i] != '\0') { //bütün kelimeleri küçük harfe çeviriyor.
		c = a[i];
		char b = tolower(c);
		i++;
		d += b;
	}
	return d;
}
Doc openTxt(Doc &doc, const Doc stoplist) {
	ifstream file;
	string word1, word;
	for (int a = 1; a <= 2; a++) {
		string textname ="AllDocs/"+to_string(a); //integer ı stringe çeviriyor.
		textname += ".txt";
		file.open(textname, ios::in);
		while (!file.eof()) {
			file >> word1;
			word = lower(word1); //küçük harfe çeviren fonksiyon
			int sz = word.length();
			if (sz != 0) {
				if (!(word[sz - 1] >= 'a' && word[sz - 1] <= 'z')|| !(word[0] >= 'a' && word[0] <= 'z')) {
					specialChar(word);
				}
				else {
					if (doc.is_inStopList(stoplist, word) == false) {
						//cout << word << endl;
						doc.add(word, a);
					}
				}
			}
			word = "\0";
		}
		file.close();
	}
	return doc;
}

void main() {
	int a;
	Doc doc, stoplist;
	ifstream file, stop;
	string word, word1;
	stop.open("stopword.txt", ios::in);
	stoplist = occurStopList("stopword.txt");
	//stoplist.traverse();
	doc=openTxt(doc, stoplist);
	doc.traverse();
	//doc.search("ended");
	
	}

