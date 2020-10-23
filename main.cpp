#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "rbtree.h"

using std::cout;
using std::endl;
using std::ostream;
using std::vector;

// struktura do eksperymentu
struct data {
	int num;
	char c;
};

// generowanie struktury z losowymi danymi
data* generateData() {
	data* d = new data();
	int x = 32;
	d->num = rand() * x + rand() % x; // rownowazne z rand() << 4 + rand() & 15
	d->c = rand() % ('z' - 'a' + 1) + 'a'; // a - z
	return d;
}

data* testGenerateData() {
	data* d = new data();
	d->num = rand() % 10000; // 0 - 9999
	d->c = rand() % ('z' - 'a' + 1) + 'a'; // a - z
	return d;
}

// porownanie danych dwoch struktur
int dataCompare(const data& ob1, const data& ob2)
{
	int d = ob1.num - ob2.num;
	if (d != 0)
		return d;
	return ob1.c - ob2.c;
}

int dataCompare(data* const &ob1, data* const& ob2)
{
	int d = ob1->num - ob2->num;
	if (d != 0)
		return d;
	return ob1->c - ob2->c;
}

int operator>(const data& ob1, const data& ob2)
{
	int d = ob1.num - ob2.num;
	if (d != 0)
		return d;
	return ob1.c - ob2.c;
}

// wypisanie danych struktury
ostream& operator<<(ostream& out, const data& n) {
	out << "[int: " << n.num << ", char: " << n.c << "]";
	return out;
}

ostream& operator<<(ostream& out, data* const& n) {
	out << "[int: " << n->num << ", char: " << n->c << "]";
	return out;
}

string printData(const data& d) {
	string s = "[int: " + to_string(d.num) + ", char: " + to_string(d.c) + "]";
	return s;
}

// funkcje przekazywane do metod typu traverse
vector<int> helperList;

void saveOrder(TElement<data>* el) {
	helperList.push_back(el->getIndex());
}

void saveOrder(TElement<data*>* el) {
	helperList.push_back(el->getIndex());
}

void printOrder(TElement<data>* el) {
	cout << el->getIndex() << ": " << el->getData() << endl;
}

void printOrder(TElement<data*>* el) {
	cout << el->getIndex() << ": " << el->getData() << endl;
}

void deleteElemData(TElement<data*>* el) {
	delete el->getData();
}

// inicjalizacja generatora indeksow elementow drzewa
template <>
int TElement<data>::indexGen = 0;

template <>
int TElement<data*>::indexGen = 0;

// test funkcjonalnosci
/*
void testStatData() {
	RBTree<data>* test = new RBTree<data>();

	data d1;
	d1.num = 10;
	d1.c = 's';

	test->add(d1, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data d2;
	d2.num = 7;
	d2.c = 'a';

	test->add(d2, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data d3;
	d3.num = 4;
	d3.c = 'b';

	test->add(d3, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data d4;
	d4.num = 25;
	d4.c = 'n';

	test->add(d4, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data d5;
	d5.num = 2;
	d5.c = 'n';

	test->add(d5, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data d6;
	d6.num = 5;
	d6.c = 'r';

	test->add(d6, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data d7;
	d7.num = 24;
	d7.c = 'e';

	test->add(d7, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data d8;
	d8.num = 123;
	d8.c = 'w';

	test->add(d8, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	cout << "treePreOrderToStr()" << endl;
	cout << test->treePreOrderToStr() << endl;

	cout << "treeInOrderToStr()" << endl;
	cout << test->treeInOrderToStr() << endl;

	cout << "treeInOrderToStr() - level = 3" << endl;
	cout << test->treeInOrderToStr(3) << endl;

	test->search(d6, dataCompare);

	cout << endl;

	data d9;
	d9.num = 999;
	d9.c = 'x';

	test->search(d9, dataCompare);

	cout << endl;

	cout << "Kolejnosc przejscia drzewa in-order (indeksy i dane):" << endl;
	test->traverseInOrder(printOrder);
	cout << endl;

	cout << endl;

	cout << "Kolejnosc przejscia drzewa pre-order (indeksy i dane):" << endl;
	test->traversePreOrder(printOrder);
	cout << endl;

	cout << endl;

	cout << "Kolejnosc przejscia drzewa pre-order (indeksy, std::vector):" << endl;
	test->traversePreOrder(saveOrder);
	for (int i = 0; i < helperList.size(); i++) {
		cout << helperList[i] << endl;
	}

	cout << endl;

	cout << "Wysokosc drzewa: " << test->getHeight() << endl << endl;

	test->clearTree();
	cout << endl;

	delete test;
	cout << endl;
}
*/

/*
void testDynData() {
	RBTree<data*>* test = new RBTree<data*>();

	data* d1 = new data();
	d1->num = 10;
	d1->c = 's';

	test->add(d1, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data* d2 = new data();
	d2->num = 7;
	d2->c = 'a';

	test->add(d2, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data* d3 = new data();
	d3->num = 4;
	d3->c = 'b';

	test->add(d3, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data* d4 = new data();
	d4->num = 25;
	d4->c = 'n';

	test->add(d4, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data* d5 = new data();
	d5->num = 2;
	d5->c = 'n';

	test->add(d5, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data* d6 = new data();
	d6->num = 5;
	d6->c = 'r';

	test->add(d6, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data* d7 = new data();
	d7->num = 24;
	d7->c = 'e';

	test->add(d7, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	data* d8 = new data();
	d8->num = 123;
	d8->c = 'w';

	test->add(d8, dataCompare);
	cout << test->treePreOrderToStr() << endl;

	cout << "treePreOrderToStr()" << endl;
	cout << test->treePreOrderToStr() << endl;

	cout << "treeInOrderToStr()" << endl;
	cout << test->treeInOrderToStr() << endl;

	test->search(d6, dataCompare);

	cout << endl;

	data* d9 = new data();
	d9->num = 999;
	d9->c = 'x';

	test->search(d9, dataCompare);

	cout << endl;

	cout << "Kolejnosc przejscia drzewa in-order (indeksy i dane):" << endl;
	test->traverseInOrder(printOrder);
	cout << endl;

	cout << endl;

	cout << "Kolejnosc przejscia drzewa pre-order (indeksy i dane):" << endl;
	test->traversePreOrder(printOrder);
	cout << endl;

	cout << endl;

	cout << "Kolejnosc przejscia drzewa pre-order (indeksy, std::vector):" << endl;
	test->traversePreOrder(saveOrder);
	for (int i = 0; i < helperList.size(); i++) {
		cout << helperList[i] << endl;
	}

	cout << endl;

	cout << "Wysokosc drzewa: " << test->getHeight() << endl << endl;

	test->traversePostOrder(deleteElemData);

	test->clearTree();
	cout << endl;

	delete test;
	cout << endl;
}
*/

void testGenData() {
	RBTree<data>* test = new RBTree<data>();

	for (int i = 0; i < 12; i++) {
		data* d = testGenerateData();
		test->add(*d, dataCompare);
		cout << test->treePreOrderToStr() << endl;
		delete d;
	}

	cout << "treePreOrderToStr()" << endl;
	cout << test->treePreOrderToStr() << endl;

	cout << "treeInOrderToStr()" << endl;
	cout << test->treeInOrderToStr() << endl;

	cout << "treeInOrderToStr() - level = 3" << endl;
	cout << test->treeInOrderToStr(3) << endl;

	int numOfHits = 0;

	for (int i = 0; i < 3; i++) {
		data* d = generateData();
		TElement<data>* r = test->search(*d, dataCompare);

		delete d;
	}

	cout << endl;

	cout << "Kolejnosc przejscia drzewa in-order (indeksy i dane):" << endl;
	test->traverseInOrder(printOrder);
	cout << endl;

	cout << endl;

	cout << "Kolejnosc przejscia drzewa pre-order (indeksy i dane):" << endl;
	test->traversePreOrder(printOrder);
	cout << endl;

	cout << endl;

	cout << "Kolejnosc przejscia drzewa pre-order (indeksy, std::vector):" << endl;
	test->traversePreOrder(saveOrder);
	for (int i = 0; i < helperList.size(); i++) {
		cout << helperList[i] << endl;
	}

	cout << endl;

	cout << "Wysokosc drzewa: " << test->getHeight() << endl << endl;

	test->clearTree();
	cout << endl;

	delete test;
	cout << endl;
}

/*
void expPtrs() {
	RBTree<data*>* t = new RBTree<data*>();

	const int testStages[] = {
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000
	};
	double elapsedTime = 0;

	for (int i = 0; i < sizeof(testStages) / sizeof(testStages[0]); i++) {

		// add()
		clock_t start = clock();
		for (int j = 0; j < testStages[i]; j++) {
			data* d = generateData();
			t->add(d, dataCompare);
		}
		clock_t stop = clock();

		// wypis na ekran aktualnej postaci drzewa (skrotowej)
		int level = 3;
		cout << "Wypis drzewa (porzadek pre-order, ograniczenie do " << level << " poziomu):" << endl << endl;
		cout << t->treePreOrderToStr(level);

		cout << endl;

		cout << "Aktualna wysokosc drzewa: " << t->getHeight() << endl << endl;

		elapsedTime = double(stop - start) / (CLOCKS_PER_SEC);
		printf("Dodanie %d elementow do drzewa zajelo %.6f s (%.3f ms)\n", testStages[i], elapsedTime, elapsedTime * 1000);
		printf("Dodanie pojedynczego elementu zajelo %.8f s (%.5f ms)\n\n", elapsedTime / testStages[i], (elapsedTime / testStages[i]) * 1000);

		// search()
		const int numOfSearches = testStages[3];
		int numOfHits = 0;

		start = clock();
		for (int i = 0; i < numOfSearches; i++) {
			data* d = generateData();
			TElement<data*>* r = t->search(d, dataCompare);

			if (r != nullptr) {
				numOfHits++;
			}

			delete d;
		}
		stop = clock();

		elapsedTime = double(stop - start) / (CLOCKS_PER_SEC);
		printf("Wyszukanie w drzewie elementow o losowych danych (%d prob) zajelo %.4f s (%.2f ms)\n", numOfSearches, elapsedTime, elapsedTime * 1000);
		printf("Wyszukanie pojedynczego elementu zajelo %.9f s (%.6f ms)\n", elapsedTime / numOfSearches, (elapsedTime / numOfSearches) * 1000);
		printf("Liczba trafien: %d\n", numOfHits);

		t->traversePostOrder(deleteElemData);

		cout << endl;
		t->clearTree();
		cout << endl << endl;
	}

	delete t;
}
*/

int main() {
	srand(time(NULL));

	//testStatData();
	//testDynData();
	//testGenData();

	// eksperyment
	//expPtrs();
	
	RBTree<data>* t = new RBTree<data>();

	const int testStages[] = {
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000
	};
	double elapsedTime = 0;

	for (int i = 0; i < sizeof(testStages) / sizeof(testStages[0]); i++) {

		// dodawanie
		clock_t start = clock();
		for (int j = 0; j < testStages[i]; j++) {
			data* d = generateData();
			t->add(*d, dataCompare);
			delete d;
		}
		clock_t stop = clock();

		// wypis na ekran skrotowej postaci drzewa
		int level = 3; // ile poziomow wglab (wliczajac korzen) chcemy wypisac
		cout << "Wypis drzewa (porzadek pre-order, ograniczenie do " << level << " poziomu):" << endl << endl;
		cout << t->treePreOrderToStr(level);

		cout << endl;

		cout << "Aktualna wysokosc drzewa: " << t->getHeight() << endl << endl;

		elapsedTime = double(stop - start) / (CLOCKS_PER_SEC);
		printf("Dodanie %d elementow do drzewa zajelo %.6f s (%.3f ms)\n", testStages[i], elapsedTime, elapsedTime * 1000);
		printf("Dodanie pojedynczego elementu zajelo %.8f s (%.5f ms)\n\n", elapsedTime / testStages[i], (elapsedTime / testStages[i]) * 1000);

		// wyszukiwanie
		const int numOfSearches = testStages[3];
		int numOfHits = 0;

		start = clock();
		for (int i = 0; i < numOfSearches; i++) {
			data* d = generateData();
			TElement<data>* r = t->search(*d, dataCompare);

			if (r != nullptr) {
				numOfHits++;
			}

			delete d;
		}
		stop = clock();

		elapsedTime = double(stop - start) / (CLOCKS_PER_SEC);
		printf("Wyszukanie w drzewie elementow o losowych danych (%d prob) zajelo %.4f s (%.2f ms)\n", numOfSearches, elapsedTime, elapsedTime * 1000);
		printf("Wyszukanie pojedynczego elementu zajelo %.9f s (%.6f ms)\n", elapsedTime / numOfSearches, (elapsedTime / numOfSearches) * 1000);
		printf("Liczba trafien: %d\n", numOfHits);

		cout << endl;
		t->clearTree();
		cout << endl << endl;
	}

	delete t;

	cout << "Nacisnij dowolny klawisz, aby zakonczyc..." << endl;
	getchar();
	return 0;
}