#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Node.h"
using namespace std;
class Doc {
	Node *head;
	Index *h;
	int sz;
public:
	Doc() :head(NULL) {}
	int getsize() { return sz; }
	bool isEmpty() { return sz == 0; }
	bool isFull() { return false; }
	void traverse() {
		Node *walk = head;
		Index *wlk = h;
		while (walk != NULL) {
			wlk = walk->h_index;
			cout << walk->word << endl;
			while (wlk != NULL) {
				cout << wlk->id << "  ";
				wlk = wlk->next;
			}
			walk = walk->nxt;
		}
	}
	void search(string data) {
		Node *walk = head;
		Index *wlk;
		int flag = 0; // bir flag açtım ki listenin içinde aradığım bilgi varsa döngüden çıkabilsin.
		if (isEmpty()) {
			cout << "list is empty" << endl;
			return;
		}
		while (walk != NULL) {
			if (walk->word != data) {
				walk = walk->nxt;
				continue;
			}
			else {
				flag = 1;  //aradığım kelimeyi bulduğumu gösterir ve çıkar.
				break;
			}
		}
		if (flag == 1) {         // kelimenin geçtiği diğer textleri yazdırır.
			wlk = walk->h_index;
			while (wlk != NULL) {
				cout << wlk->id << endl;
				wlk = wlk->next;

			}
		}
		else { //yani flag=0 kaldıysa kelime listede yoktur.
			cout << data << " was not found. " << endl;
		}
	}
	void add(string data, int textname) {
		int flag = 0;
		Node *walk = head;
		Index *wlk;
		if (isEmpty()) { //boş ise yeni node oluşturup head i o node yapıyor
			Node *newNode = new Node(data);
			newNode->nxt = head;
			head = newNode;
			Index *new_id = new Index(textname);
			newNode->h_index = new_id;
			sz++;
			//cout << data << "  " << textname<<endl;
			flag = 1;
		}
		if (!isEmpty()) { // sorun bu kısımda çünkü daha önce listede var olan kelimeyi tekrar yazıyor. Ama bu hatayı her kelime için yapmıyor.
			while (walk != NULL) {
				if (walk->word == data) {  //eklemek istediğim kelime listenin içinde varsa bulunduğu dosyanın adını indexlerin olduğu listeye ekleyecek.
					flag = 1;
					wlk = walk->h_index;
					if (wlk->id == textname) {  // yanlış burada mı çözemedim ?! burada bu koşul doğruysa walk ı bir sonrakine artırıp devam etsin istiyorum
						return;
					}
					else {  //kelime farklı bir textten geldiyse index nodu eklesin
						Index *newIndexNode = new Index(textname);
						wlk = walk->h_index;
						while (wlk->next != NULL)
							wlk = wlk->next;
						wlk->next = newIndexNode;
					}
				}
				walk = walk->nxt;
			}
			if (flag == 0) {  // bu demek oluyor ki aradığımız kelime listede daha önce var olmamış
				Node *newNode = new Node(data);
				newNode->nxt = head;
				head = newNode;
				Index *newIndexNode = new Index(textname);
				newNode->h_index = newIndexNode;
				sz++;
				//cout << data << "  " << textname<<endl;
			}
		}
	}
	friend void specialChar(string &w) {
		string a;
		int size = w.length();
		int k = 0;
		while (w[k] != '\0') {
			if (!(w[k] >= 'a') || !(w[k] <= 'z'))
				k++;
			else {
				a += w[k];
				k++;
			}
		}
		w = a;
	}
	friend Doc occurStopList(const string name) {
		string word1, word;
		int k = 0;
		Doc stop;
		ifstream f;
		f.open(name, ios::in);
		while (!f.eof()) {
			k = 0;
			f >> word1;
			while (word1[k] != '\0') {
				if (!(word1[k] >= 'a' && word1[k] <= 'z')) {
					k++;
					continue;
				}
				else {
					word += word1[k];
					k++;
				}
			}
			Node *newNode = new Node(word);
			newNode->nxt = stop.head;
			stop.head = newNode;
			stop.sz++;
			word = "\0";
		}
		f.close();
		return stop;
	}
	bool is_inStopList(Doc stop, string data) {
		Node *stop_walk = stop.head;
		if (!stop.isEmpty()) {
			while (stop_walk != NULL) {
				if (stop_walk->word == data)
					return true;
				else
					stop_walk = stop_walk->nxt;
			}
			return false;
		}
	}


};

