#pragma once
class Index {
public:
	int id;
	Index *next;
	Index(int k) :id(k), next(NULL) {}
};
