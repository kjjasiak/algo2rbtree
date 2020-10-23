#ifndef RBTREE_H
#define RBTREE_H

#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::stringstream;

enum Color { RED, BLACK };

string colorToStr(Color color) {
	return color == Color::RED ? "red" : "black";
}

template <typename T>
class TElement {
	static int indexGen;
	T data;
	TElement<T>* parent;
	TElement<T>* lChild;
	TElement<T>* rChild;
	Color color;
	int index;

public:
	TElement(const T& data) {
		this->parent = nullptr;
		this->lChild = nullptr;
		this->rChild = nullptr;
		this->color = Color::RED;
		this->data = data;
		this->index = indexGen;
		indexGen++;
	}

	// funkcje get() i set()
	T& getData() {
		return this->data;
	}

	void setData(const T& data) {
		this->data = data;
	}

	TElement<T>* getParent() {
		return this->parent;
	}

	void setParent(TElement<T>* parent) {
		this->parent = parent;
	}

	TElement<T>* getGrandParent() {
		if (this->parent == nullptr) {
			return nullptr;
		}

		return this->parent->parent;
	}

	TElement<T>* getUncle() {
		TElement<T>* gparent = this->getGrandParent();

		if (gparent == nullptr) {
			return nullptr;
		}

		return (this->parent == gparent->lChild) ? gparent->rChild : gparent->lChild;
	}

	TElement<T>* getlChild() {
		return this->lChild;
	}

	void setlChild(TElement<T>* child) {
		this->lChild = child;
	}

	TElement<T>* getrChild() {
		return this->rChild;
	}

	void setrChild(TElement<T>* child) {
		this->rChild = child;
	}

	Color getColor() {
		return this->color;
	}

	void setColor(Color color) {
		this->color = color;
	}

	int& getIndex() {
		return this->index;
	}

	void traversePreOrder(void(*fun)(TElement<T>*));
	void traverseInOrder(void(*fun)(TElement<T>*));
	void traversePostOrder(void(*fun)(TElement<T>*));
	void elemPreOrderToStr(stringstream&, int level = -1);
	void elemInOrderToStr(stringstream&, int level = -1);
	string elemToStr();
	int getSubTreeHeight();
	void deletePostOrder();
};

template <typename T>
void TElement<T>::traversePreOrder(void(*fun)(TElement<T>*)) { // przejscie pre-order

	fun(this);

	if (this->getlChild() != nullptr)
		this->getlChild()->traversePreOrder(fun);

	if (this->getrChild() != nullptr)
		this->getrChild()->traversePreOrder(fun);
}

template <typename T>
void TElement<T>::traverseInOrder(void(*fun)(TElement<T>*)) { // przejscie in-order

	if (this->getlChild() != nullptr) {
		this->getlChild()->traverseInOrder(fun);
	}

	fun(this);

	if (this->getrChild() != nullptr) {
		this->getrChild()->traverseInOrder(fun);
	}

	return;
}

template <typename T>
void TElement<T>::traversePostOrder(void(*fun)(TElement<T>*)) { // przejscie post-order

	if (this->getlChild() != nullptr) {
		this->getlChild()->traversePostOrder(fun);
	}

	if (this->getrChild() != nullptr) {
		this->getrChild()->traversePostOrder(fun);
	}

	fun(this);

	return;
}

template <typename T>
string TElement<T>::elemToStr() { // zwrocenie skladowych elementu jako string

	stringstream s;

	s << this->getIndex() << " => color: " << colorToStr(this->getColor()) << ",\t parent: ";

	if (this->getParent() != nullptr)
		s << this->getParent()->getIndex();
	else
		s << "NULL";

	s << ",\t lChild: ";

	if (this->getlChild() != nullptr)
		s << this->getlChild()->getIndex();
	else
		s << "NULL";

	s << ",\t rChild: ";

	if (this->getrChild() != nullptr)
		s << this->getrChild()->getIndex();
	else
		s << "NULL";

	s << ",\t data: " << this->data << endl;

	return s.str();
}

template <typename T>
void TElement<T>::elemPreOrderToStr(stringstream& s, int level) { // zwrocenie pre-order

	if (level == 0) {
		return;
	}	

	s << this->elemToStr();

	if (level > 0) {
		level--;
	}

	if (this->getlChild() != nullptr) {
		this->getlChild()->elemPreOrderToStr(s, level);
	}

	if (this->getrChild() != nullptr) {
		this->getrChild()->elemPreOrderToStr(s, level);
	}
}

template <typename T>
void TElement<T>::elemInOrderToStr(stringstream& s, int level) { // zwrocenie in-order

	if (level == 0) {
		return;
	}

	if (level > 0) {
		level--;
	}

	if (this->getlChild() != nullptr) {
		this->getlChild()->elemInOrderToStr(s, level);
	}

	s << this->elemToStr();

	if (this->getrChild() != nullptr) {
		this->getrChild()->elemInOrderToStr(s, level);
	}
}

template <typename T>
int TElement<T>::getSubTreeHeight() {
	int hL, hR, hMax;

	if (this->getlChild() != nullptr)
		hL = this->getlChild()->getSubTreeHeight();
	else
		hL = -1;

	if (this->getrChild() != nullptr)
		hR = this->getrChild()->getSubTreeHeight();
	else
		hR = -1;

	hMax = (hL > hR) ? hL : hR;

	return (hMax + 1);
}

template <typename T>
void TElement<T>::deletePostOrder() {

	if (this->getlChild() != nullptr)
		this->getlChild()->deletePostOrder();

	if (this->getrChild() != nullptr)
		this->getrChild()->deletePostOrder();

	delete this;
}

template <typename T>
class RBTree {
	TElement<T>* root;
	int size;

public:
	RBTree() {
		root = nullptr;
		size = 0;
	}

	~RBTree() {
		// zwolnic pamiec dla wszystkich TElement
		clearTree();
	}

	void add(const T&, int(*compare)(const T&, const T&));
	void rotateLeft(TElement<T>*, TElement<T>*);
	void rotateRight(TElement<T>*, TElement<T>*);
	void traversePreOrder(void(*fun)(TElement<T>*));
	void traverseInOrder(void(*fun)(TElement<T>*));
	void traversePostOrder(void(*fun)(TElement<T>*));
	TElement<T>* search(const T&, int(*compare)(const T&, const T&));
	void clearTree();
	int getHeight();
	string treeInOrderToStr(int level = -1);
	string treePreOrderToStr(int level = -1);
};

template <typename T>
void RBTree<T>::add(const T& data, int(*compare)(const T&, const T&)) {
	TElement<T>* child = new TElement<T>(data);

	if (size == 0) {
		root = child;
		root->setColor(Color::BLACK);
		size++;

		return;
	}

	TElement<T>* tmp = root;
	TElement<T>* tmpParent = nullptr;
	int result;

	while (tmp != nullptr) {
		tmpParent = tmp;
		result = compare(child->getData(), tmp->getData());

		if (result > 0) // child->getData() > tmp->getData();
			tmp = tmp->getrChild();
		else // child->getData() <= tmp->getData();
			tmp = tmp->getlChild();
	}

	child->setParent(tmpParent);

	result = compare(child->getData(), child->getParent()->getData());

	if (result > 0) // child->getData() > child->getParent()->getData()
		child->getParent()->setrChild(child);
	else
		child->getParent()->setlChild(child);

	tmpParent = nullptr;
	tmp = nullptr;

	// przekolorowanie
	while ((child != root) && (child->getParent()->getColor() == Color::RED)) {

		// rodzic czerwony, trzy przypadki
			
		if ((child->getUncle() != nullptr) && (child->getUncle()->getColor() == Color::RED)) {

			// 1* stryj jest czerwony

			child->getParent()->setColor(Color::BLACK);
			child->getUncle()->setColor(Color::BLACK);
			// nie trzeba sprawdzac czy dziadek istnieje, bo rodzic jest czerwony
			child->getGrandParent()->setColor(Color::RED);
			child = child->getGrandParent();
		}
		else {
			// 2* i 3* stryj czarny i...
			// nie trzeba sprawdzac czy dziadek istnieje, bo rodzic jest czerwony
			if (child->getParent() == child->getGrandParent()->getlChild()) {

				// ...rodzic jest lewym potomkiem dziadka
				if (child == child->getParent()->getlChild()) {

					// ...i dziecko jest lewym potomkiem rodzica

					child->getParent()->setColor(Color::BLACK);
					// nie trzeba sprawdzac czy dziadek istnieje, bo rodzic jest czerwony
						
					child->getGrandParent()->setColor(Color::RED);

					// rotacja w prawo rodzic-dziadek
					rotateRight(child->getParent(), child->getGrandParent());
				}
				else {

					// ...i dziecko jest prawym potomkiem rodzica

					// rotacja w lewo dziecko-rodzic
					TElement<T>* tmp = child->getParent();
					rotateLeft(child, tmp);
					child = tmp;
					child->getParent()->setColor(Color::BLACK);
					// nie trzeba sprawdzac czy dziadek istnieje, bo rodzic jest czerwony
					child->getGrandParent()->setColor(Color::RED);

					// rotacja w prawo rodzic-dziadek
					rotateRight(child->getParent(), child->getGrandParent());
				}
			}
			else {

				// ...rodzic jest prawym potomkiem dziadka
				if (child == child->getParent()->getlChild()) {

					// ...i dziecko jest lewym potomkiem rodzica

					// rotacja w prawo dziecko-rodzic
					TElement<T>* tmp = child->getParent();
					rotateRight(child, tmp);
					child = tmp;
					child->getParent()->setColor(Color::BLACK);
					// nie trzeba sprawdzac czy dziadek istnieje, bo rodzic jest czerwony
					child->getGrandParent()->setColor(Color::RED);

					// rotacja w lewo rodzic-dziadek
					rotateLeft(child->getParent(), child->getGrandParent());
				}
				else {

					// ...i dziecko jest prawym potomkiem rodzica

					child->getParent()->setColor(Color::BLACK);
					child->getGrandParent()->setColor(Color::RED);

					// rotacja w lewo rodzic-dziadek
					rotateLeft(child->getParent(), child->getGrandParent());
				}
			}
		}
	}
		
	// rodzic czarny - ustawiamy korzen na czarny, koniec
	root->setColor(Color::BLACK);
	size++;
}

template <typename T>
void RBTree<T>::rotateLeft(TElement<T>* elem, TElement<T>* elemParent) {
	TElement<T>* g = elem->getGrandParent();
	TElement<T>* lCh = elem->getlChild();

	elem->setlChild(elemParent);
	elemParent->setParent(elem);
	elem->setParent(g);

	if (elem->getParent() != nullptr) { // nowy rodzic istnieje
		if (elem->getParent()->getlChild() == elemParent) {
			// ...elem bedzie jego lewym dzieckiem
			elem->getParent()->setlChild(elem);
		}
		else if (elem->getParent()->getrChild() == elemParent) {
			// ...elem bedzie jego prawym dzieckiem
			elem->getParent()->setrChild(elem);
		}
	}
	else {
		root = elem;
	}

	if (lCh != nullptr) { // przepinamy lewe dziecko elementu
		lCh->setParent(elemParent);
		elemParent->setrChild(lCh);
	}
	else {
		elemParent->setrChild(nullptr);
	}
}

template <typename T>
void RBTree<T>::rotateRight(TElement<T>* elem, TElement<T>* elemParent) {
	TElement<T>* g = elem->getGrandParent();
	TElement<T>* rCh = elem->getrChild();

	elem->setrChild(elemParent);
	elemParent->setParent(elem);
	elem->setParent(g);

	if (elem->getParent() != nullptr) { // nowy rodzic istnieje
		if (elem->getParent()->getrChild() == elemParent) {
			// ...elem bedzie jego prawym dzieckiem
			elem->getParent()->setrChild(elem);
		}
		else if (elem->getParent()->getlChild() == elemParent) {
			// ...elem bedzie jego lewym dzieckiem
			elem->getParent()->setlChild(elem);
		}
	}
	else {
		root = elem;
	}

	if (rCh != nullptr) { // przepinamy prawe dziecko elementu
		rCh->setParent(elemParent);
		elemParent->setlChild(rCh);
	}
	else {
		elemParent->setlChild(nullptr);
	}
}

template <typename T>
void RBTree<T>::traversePreOrder(void(*fun)(TElement<T>* el)) { // kolejnosc: element=>lChild=>rChild
	root->traversePreOrder(fun);
}

template <typename T>
void RBTree<T>::traverseInOrder(void(*fun)(TElement<T>* el)) { // kolejnosc: lChild=>rChild=>element
	root->traverseInOrder(fun);
}

template <typename T>
void RBTree<T>::traversePostOrder(void(*fun)(TElement<T>* el)) { // kolejnosc: element=>lChild=>rChild
	root->traversePostOrder(fun);
}

template <typename T>
TElement<T>* RBTree<T>::search(const T& cmpData, int(*compare)(const T&, const T&)) {
	if (size == 0) {
		cout << "Brak elementow w drzewie" << endl << endl;
		return nullptr;
	}

	//cout << "Dane szukanego elementu:" << endl << cmpData << endl << endl;

	TElement<T>* tmp = root;
	int result;

	while (tmp != nullptr) {
		result = compare(cmpData, tmp->getData());

		if (result == 0) { // znaleziono element
			//cout << "Znaleziono element" << endl;

			// wypisanie samego elementu (bez dzieci!)
			//cout << tmp->elemToStr();

			return tmp;
		}
		else if (result < 0) { // idziemy w lewe poddrzewo
			tmp = tmp->getlChild();
		}
		else { // idziemy w prawe poddrzewo
			tmp = tmp->getrChild();
		}
	}
	//cout << "Brak pasujacego elementu w drzewie" << endl;
	return nullptr;
}

template <typename T>
void RBTree<T>::clearTree() {
	if (size > 0) {
		root->deletePostOrder();
		size = 0;
		cout << "Pomyslnie wyczyszczono drzewo" << endl;
	}
	else {
		cout << "Nie mozna wyczyscic drzewa - drzewo jest juz puste" << endl;
	}
}

template <typename T>
int RBTree<T>::getHeight() {
	return root->getSubTreeHeight();
}

template <typename T>
string RBTree<T>::treeInOrderToStr(int level) {
	stringstream s;
	s << "Rozmiar drzewa: " << size << endl;
	s << "Kolejnosc elementow (in-order):" << endl;
	root->elemInOrderToStr(s, level);
	return s.str();
}

template <typename T>
string RBTree<T>::treePreOrderToStr(int level) {
	stringstream s;
	s << "Rozmiar drzewa: " << size << endl;
	s << "Kolejnosc elementow (pre-order):" << endl;
	root->elemPreOrderToStr(s, level);
	return s.str();
}

#endif