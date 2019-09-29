#pragma once
#include <string>
#include"Index.h"
using namespace std;

class Node {
public:
	string word;
	Node *nxt;
	Index *h_index;
	Node(string d) :word(d), nxt(NULL) {}//, h_index(NULL) {}
};

