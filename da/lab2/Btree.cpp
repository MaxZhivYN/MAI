#include <algorithm>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include "BTree.h"
using namespace std;

BTree::BTree()
{
	root = nullptr;
}

BTree::~BTree() {
	if (root != nullptr)
		Delete_tree(root);
	delete root;
	//cout << "EXIT: BTree deleted" << endl;
}

void BTree::Print(char *keyZ)
{
	ofstream file_out;
	if (keyZ == nullptr)
		file_out.open("./file.txt");
	else
		file_out.open(keyZ);
	if (!file_out.is_open()) {
		cout << "ERROR: Incorrect path to file" << endl;
		return;
	}
	print_b_tree(file_out, root, 0);
	file_out.close();
}


void BTree::print_b_tree(ofstream &output, BNode *node, int level)
{
	short i;

	if (node != nullptr)
	{
		for (i = 0; i < level; i++) {
			if (i == level - 1)
				output << " + ";
			else
				output << " @ ";
		}
		for (i = 0; i < node->count; i++) {
			output << node->keys[i]->word << " " << node->keys[i]->number;
			if (i != node->count - 1)
				output << " # ";
		}


		/*
		if (node->children[0] != nullptr) {
			output << " !";
		}
		else {
			output << " #";
		}
		*/
		output << " %" << endl;
		for (i = 0; i < 2 * t; i++)
			print_b_tree(output, node->children[i], level + 1);
	}
}


void BTree::Print1()
{
	print_b_tree1(root, 0);
}


void BTree::print_b_tree1(BNode *node, int level)
{
	short i;

	if (node != nullptr)
	{
		for (i = 0; i < level; i++) {
			if (i == level - 1)
				cout << " + ";
			else
				cout << " @ ";
		}
		for (i = 0; i < node->count; i++) {
			cout << node->keys[i]->word << " " << node->keys[i]->number;
			if (i != node->count - 1)
				cout << " # ";
		}
		cout << " %" << endl;
		for (i = 0; i < 2 * t; i++)
			print_b_tree1(node->children[i], level + 1);
	}
}

void BTree::Print()
{
	print_b_tree(root, 0);
}


void BTree::print_b_tree(BNode *node, int level)
{
	short i;

	if (node != nullptr)
	{
		for (i = 0; i < level; i++) {
			if (i == 0)
				cout << "---";
			else
				cout << "---";
		}
		for (i = 0; i < node->count; i++) {
			cout << node->keys[i]->word;
			if (i != node->count - 1)
				cout << " ";
		}
		cout << endl;
		for (i = 0; i < 2 * t; i++)
			print_b_tree(node->children[i], level + 1);
	}
}


void BTree::Get_copy(char *buff, char *data_word, int word_count)
{
	//cout << word_count << endl;
	int i = 0;
	//data_word = new char[word_count + 1];
	while (true) {
		data_word[i] = buff[i];
		if (data_word[i] == '\0') break;
		i++;
	}
}


bool BTree::insert(Type_fly key)
{
	if (root == nullptr) {
		root = new BNode;
		memset(root, 0, sizeof(BNode));

		root->keys[0] = new Type;
		root->keys[0]->number = key.number;
		root->keys[0]->word_count = key.word_count;
		root->keys[0]->word = new char[key.word_count + 1];
		Get_copy(key.word, root->keys[0]->word, key.word_count);

		root->count++;
		return true;
	}
	else {
		BNode* node = root;
		int i;
		while (true) {
			if (node->count == (2 * t - 1)) {
				node = split(node);
			}

			i = 0;
			while (i < node->count && i < 2 * t - 1) {
				if (strcmp(node->keys[i]->word, key.word) < 0)
					++i;
				else break;
			}

			if (i < node->count) {
				if (strcmp(node->keys[i]->word, key.word) != 0) {
					if (node->children[0] == nullptr) {
						node->keys[node->count] = new Type;
						node->keys[node->count]->number = key.number;
						node->keys[node->count]->word_count = key.word_count;
						node->keys[node->count]->word = new char[key.word_count + 1];
						Get_copy(key.word, node->keys[node->count]->word, key.word_count);
						node->count++;

						for (int i = node->count - 1; i > 0; i--) {
							if (strcmp(node->keys[i - 1]->word, node->keys[i]->word) < 0) {
								break;
							}
							else {
								swap(node->keys[i - 1], node->keys[i]);
							}
						}
						return true;
					}
				}
				else return false;
			}
			else {
				if (node->children[0] == nullptr) {
					node->keys[node->count] = new Type;
					node->keys[node->count]->number = key.number;
					node->keys[node->count]->word_count = key.word_count;
					node->keys[node->count]->word = new char[key.word_count + 1];
					Get_copy(key.word, node->keys[node->count]->word, key.word_count);
					node->count++;

					for (int i = node->count - 1; i > 0; i--) {
						if (strcmp(node->keys[i - 1]->word, node->keys[i]->word) < 0) {
							break;
						}
						else {
							swap(node->keys[i - 1], node->keys[i]);
						}
					}
					return true;
				}
			}

			if (node->children[0] != nullptr)
				node = node->children[i];
			else return false;
		}
	}
}


void BTree::insert_to_node(Type *key, BNode *node) {
	node->keys[node->count] = key;
	node->count++;

	for (int i = node->count - 1; i > 0; i--) {
		if (strcmp(node->keys[i - 1]->word, node->keys[i]->word) < 0) {
			break;
		}
		else {
			swap(node->keys[i - 1], node->keys[i]);
		}
	}
}



BNode *BTree::split(BNode *node)
{
	BNode *node_left = new BNode;
	BNode *node_right = new BNode;
	for (int i = 0; i < 2 * t; ++i) {
		if (i < t - 1)
			node_left->keys[i] = node->keys[i];
		else if (i < 2 * t - 1)
			node_left->keys[i] = nullptr;
		if (i < t)
			node_left->children[i] = node->children[i];
		else
			node_left->children[i] = nullptr;
	}
	node_left->count = t - 1;
	node_right->count = t - 1;
	int id = t;
	for (int j = 0; j < 2 * t; ++j) {
		if (id < 2 * t - 1)
			node_right->keys[j] = node->keys[id];
		else if (j < 2 * t - 1)
			node_right->keys[j] = nullptr;
		if (id < 2 * t)
			node_right->children[j] = node->children[id];
		else node_right->children[j] = nullptr;
		++id;
	}
	BNode *pa = nullptr;
	int node_id_in_pa = -1;
	get_pa_and_node_id_in_pa(node->keys[0]->word, pa, node_id_in_pa);
	if (pa == nullptr) {
		node->keys[0] = node->keys[t - 1];
		node->children[0] = node_left;
		node->children[1] = node_right;

		for (int i = 1; i < node->count + 1; i++) {
			if (i < node->count)
				node->keys[i] = nullptr;
			if (i > 1)
				node->children[i] = nullptr;
		}

		node->count = 1;
		return node;
	}
	else {
		int node_parent_id = -1;
		while (pa->children[++node_parent_id] != node) {}
		for (int i = 2 * t - 1; i > node_parent_id; --i) {
			swap(pa->children[i - 1], pa->children[i]);
		}
		insert_to_node(node->keys[t - 1], pa);
		pa->children[node_parent_id] = node_left;
		pa->children[node_parent_id + 1] = node_right;
		delete node;
		return pa;
	}
}


void BTree::get_pa_and_node_id_in_pa(char *node_first_key, BNode* &node_parent, int &node_id_in_pa)
{
	BNode* node = root;
	int i;
	while (true) {
		i = 0;
		while (i < node->count) {
			if (node->keys[i] != nullptr) {
				if (strcmp(node->keys[i]->word, node_first_key) < 0) {
					++i;
				}
				else {
					break;
				}
			}
		}
		if (i < node->count) {
			if (strcmp(node->keys[i]->word, node_first_key) == 0) {
				return;
			}
		}
		node_parent = node;
		node_id_in_pa = i;
		node = node->children[i];
	}
}


Type *BTree::search(char *key)
{
	if (root != nullptr) {
		BNode* node = root;
		while (true) {
			int i = 0;
			while (i < node->count) {
				if (node->keys[i] != nullptr) {
					if (strcmp(node->keys[i]->word, key) < 0) {
						++i;
					}
					else {
						break;
					}
				}
			}

			if (i < node->count) {
				if (strcmp(node->keys[i]->word, key) == 0) {
					return node->keys[i];
				}
				else if (node->children[i] != nullptr) {
					node = node->children[i];
				}
				else return nullptr;
			}
			else if (node->children[i] != nullptr) {
				node = node->children[i];
			}
			else return nullptr;
		}
	}
	else {
		return nullptr;
	}
}


bool is_true_back_vector(MyVector<BNode*> &back_vector, BNode *node)
{
	int j = 0;
	for (int i = 0; i < back_vector.Size(); i++) {
		BNode *pa = back_vector[i];
		BNode *child = (i != back_vector.Size() - 1) ? back_vector[i + 1] : node;
		j = 0;
		while (true) {
			if (j < pa->count + 1 && j < 2 * t) {
				if (pa->children[j] == child) break;
			}
			else return false;
			j++;
		}
	}
	return true;
}




bool BTree::new_remove(char *key)
{
	if (root == nullptr) return false;
	int i;
	bool is_true_delete = true;
	BNode *node = root;
	shared_ptr<MyVector<BNode*>> back_vector(new MyVector<BNode*>);
	while (true) {

		i = 0;
		while (i < node->count) {
			if (node->keys[i] != nullptr) {
				if (strcmp(node->keys[i]->word, key) < 0) {
					++i;
				}
				else {
					break;
				}
			}
		}

		if (i < node->count) {
			if (strcmp(node->keys[i]->word, key) == 0) {
				if (node->children[0] == nullptr) {
					if (is_true_delete)
						remove_from_node(node, key, true);
					else
						remove_from_node(node, key, false);
						Node_fix(node, back_vector);
					return true;
				}
				else {
					back_vector->Push_Back(node);
					BNode* donner_node = node->children[i];

					while (donner_node->children[0] != nullptr) {
						back_vector->Push_Back(donner_node);
						donner_node = donner_node->children[donner_node->count];
					}



					Type* last_key_in_don_child_left = donner_node->keys[donner_node->count - 1];
					delete[] node->keys[i]->word;
					delete node->keys[i];

					node->keys[i] = last_key_in_don_child_left;

					node = donner_node;
					key = last_key_in_don_child_left->word;
					is_true_delete = false;
				}
			}
			else {
				if (node->children[0] != nullptr) {
					back_vector->Push_Back(node);
					node = node->children[i];
				}
				else return false;
			}
		}
 		else {
			if (node->children[0] != nullptr) {
				back_vector->Push_Back(node);
				node = node->children[i];
			}
			else return false;
		}
	}
}




int indic_1 = 0;

void BTree::get_pa_and_node_id_in_pa_all(BNode *node, BNode *node_parent, BNode* &node_out, int &node_id_in_pa)
{
	for (int i = 0; i < node_parent->count + 1; ++i) {
		if (node == node_parent) {
			indic_1++;
			return;
		}
		if (node_parent->children[i] != nullptr) {
			get_pa_and_node_id_in_pa_all(node, node_parent->children[i], node_out, node_id_in_pa);
		}
		if (indic_1) {
			node_out = node_parent;
			node_id_in_pa = i;
			indic_1 = 0;
		}
	}
}


void BTree::Node_fix(BNode *node, shared_ptr<MyVector<BNode*>> back_vector)
{
	bool refresh_Node_fix = true;
	int number = back_vector->Size();

	while (refresh_Node_fix) {

		if (node->count >= t - 1) return;

		if (node == root) {
			if (node->count > 0) return;
			else {
				BNode *new_root = node->children[0];
				delete root;
				root = new_root;
				return;
			}
		}

		if (number < 0) {
			cout << "ERROR in number of MyVector" << endl;
			break;
		}
		BNode *pa = (*back_vector)[--number];
		int node_id_in_pa = 0;


		for (int i = 0; i < pa->count + 1 && i < 2 * t; ++i) {
			if (pa->children[i] == node) {
				node_id_in_pa = i;
				break;
			}
		}
		/*
		if (node->count > 0)
			get_pa_and_node_id_in_pa(node->keys[0]->word, pa, node_id_in_pa);
		else
			get_pa_and_node_id_in_pa_all(node, root, pa, node_id_in_pa);
		*/
		int cmd = 0;
		if (node_id_in_pa == pa->count) { // ���� ��� ��������� ����  �� �����(����) ���� ������ ��������
			if (t - 1 < pa->children[node_id_in_pa - 1]->count)  // ���� � ����� ���� �� node ������ t - 1 ������
				cmd = 1;
			else
				cmd = 3;
		}
		else {
			if (node_id_in_pa == 0) { // ���� ��� ������ ���� �� ������(����) ��������
				if (t - 1 < pa->children[node_id_in_pa + 1]->count) // ���� � ������ ���� ������ t - 1 ������
					cmd = 2;
				else
					cmd = 4;
			}
			else {
				if (t - 1 < pa->children[node_id_in_pa - 1]->count) { // ���� � ����� ���� ������ t - 1 ������
					cmd = 1;
				}
				else {
					if (t - 1 < pa->children[node_id_in_pa + 1]->count) { // ���� � ������ ���� ������ t - 1 ������
						cmd = 2;
					}
					else
						cmd = 3;
				}
			}
		}


		switch (cmd) {
		case 1: // left restract: (left_node) --- (node)
			left_restruct(pa, node_id_in_pa);
			refresh_Node_fix = false;
			break;
		case 2: // right restract: (node) --- (right_node)
			right_restruct(pa, node_id_in_pa);
			refresh_Node_fix = false;
			break;
		case 3:	// left middle restract: (left_node) --- (node)
			get_node_for_middle_restract_left(pa, node_id_in_pa, pa->children[node_id_in_pa - 1]);
			for (int i = node_id_in_pa;; ++i) {
				if (i < pa->count)
					swap(pa->children[i], pa->children[i + 1]);
				else
					break;
			}

			delete pa->children[pa->count];
			pa->children[pa->count] = nullptr;
			remove_from_node(pa, pa->keys[node_id_in_pa - 1]->word, false);

			node = pa;
			break;
		case 4: // right middle restract: (node) --- (right_node)
			get_node_for_middle_restract_right(pa, node_id_in_pa, pa->children[node_id_in_pa]);
			for (int i = node_id_in_pa + 1;; ++i) {
				if (0 <= i && i < pa->count && i < 2 * t - 1)
					swap(pa->children[i], pa->children[i + 1]);
				else
					break;
			}

			delete pa->children[pa->count];
			pa->children[pa->count] = nullptr;
			remove_from_node(pa, pa->keys[node_id_in_pa]->word, false);

			node = pa;
			break;
		}
	}
}


void BTree::left_restruct(BNode *pa, int node_id_in_pa)  // (left_node) --- (node)		!upgrade: ��������� �� ���������� �������

{
	BNode *left_node = pa->children[node_id_in_pa - 1]; // Correct
	BNode *node = pa->children[node_id_in_pa]; // Correct

	// ������ � node: //
	if (node->children[0] != nullptr) { // �������� �� ������� ����� � node
		for (int i = node->count + 1; i > 0; --i) { // ����������� ������� ����� ��� ���������� ���������� ������� �� left_node  (0)[A]  (1)[B]  (2)[C]  (3)[D]  -->  (0)[ ]  (1)[A]  (2)[B]  (3)[C]  (4)[D]
			swap(node->children[i - 1], node->children[i]);
		}

		node->children[0] = left_node->children[left_node->count];
	}
	insert_to_node(pa->keys[node_id_in_pa - 1], node); // ������� �������� �� �������� � node

	// ������ � ������: // Correct
	pa->keys[node_id_in_pa - 1] = left_node->keys[left_node->count - 1]; // ������ ����� � ����� ��������� ������ �� left_node

	// ������ � left_node: // Correct
	left_node->children[left_node->count] = nullptr; // �������� ��������� ������� �� left_node // !upgrade: ������� ������� �������� ����� delete
	remove_from_node(left_node, left_node->keys[left_node->count - 1]->word, false); // �������� ��������� ����� �� left_node
}

void BTree::right_restruct(BNode *pa, int node_id_in_pa)  // (node) --- (right_node)
{
	BNode *right_node = pa->children[node_id_in_pa + 1];
	BNode *node = pa->children[node_id_in_pa];

	// ������ � node
	insert_to_node(pa->keys[node_id_in_pa], node); // ������� ����� �� ����� � node
	node->children[node->count] = right_node->children[0]; // ������� ������� ������� �� right_node � ����� ����� node

	// ������ � ������
	pa->keys[node_id_in_pa] = right_node->keys[0]; // ���������  ���� � ����� �� ������ ���� �� right_node

	// ������ � right_node
	if (right_node->children[0] != nullptr) { // �������� �� ������� ����� � right_node
		for (int i = 0; i < right_node->count; ++i) { // ������� ������� ���� � ����� ��� �������� � right_node
			swap(right_node->children[i], right_node->children[i + 1]);
		}
		right_node->children[right_node->count] = nullptr; // �������� ���������� (�������������) ���� � right_node
	}
	remove_from_node(right_node, right_node->keys[0]->word, false); // �������� ������ ����� �� right_node
}




void BTree::get_node_for_middle_restract_left(BNode *pa, int node_id, BNode *node_out) // node_id - id �������� ���� (������ � ���� ���������)
{
	for (int i = 0; i < t; ++i) {
		if (i < t - 1) {
			node_out->keys[i] = pa->children[node_id - 1]->keys[i];
		}

		node_out->children[i] = pa->children[node_id - 1]->children[i];
	}

	node_out->keys[t - 1] = pa->keys[node_id - 1];

	int j = 0;
	for (int i = t; i < 2 * t - 1; ++i) { // for ��� �����; 2 * t - 1 = t (���������� ����� �� ����� ����) + (t - 1) (���������� ����� �� ������ ����, -1 ������ ��� 1 ���� ��� ������ � ���� ���� ��������� ����)
		if (i < 2 * t - 2) {
			node_out->keys[i] = pa->children[node_id]->keys[j];
		}
		node_out->children[i] = pa->children[node_id]->children[j];
		++j;
	}

	node_out->count = 2 * t - 2;
}
/*
			(8)
	(3)			(10)
(1 2) (4) 	 (9)	(11)
*/

void BTree::get_node_for_middle_restract_right(BNode *pa, int node_id, BNode *node_out) // node_id - id �������� ���� (����� � ���� ���������)
{

	for (int i = 0; i < t - 1; ++i) {
		if (i < t - 2) {
			node_out->keys[i] = pa->children[node_id]->keys[i];
		}
		node_out->children[i] = pa->children[node_id]->children[i];
	}

	node_out->keys[t - 2] = pa->keys[node_id];

	int j = 0;
	for (int i = t - 1; i < 2 * t - 1; ++i) {
		if (i < 2 * t - 2) {
			node_out->keys[i] = pa->children[node_id + 1]->keys[j];
		}
		node_out->children[i] = pa->children[node_id + 1]->children[j];
		j++;
	}

	node_out->count = 2 * t - 2;
}


void BTree::remove_from_node(BNode *node, char *key, bool true_delete)
{
	int i = 0, cmd = 1;

	while (cmd) {
		switch (cmd) {
		case 1:
			if (strcmp(node->keys[i]->word, key) == 0)
				cmd = 2;
			else
				i++;
			break;
		case 2:
			if (i + 1 < node->count) {
				swap(node->keys[i], node->keys[i + 1]);
				i++;
			}
			else cmd = 0;
			break;
		}
	}
	if (true_delete) {
		delete[] node->keys[node->count - 1]->word;
		delete node->keys[node->count - 1];
	}
	node->keys[node->count - 1] = nullptr;
	node->count--;
}


int indic_is_btree = 0;

bool BTree::Is_BTree()
{
	if (root == nullptr) return true;

	vector<char*> vec;
	Is_BTree_help(root, vec);

	if (indic_is_btree) {
		vec.clear();
		return false;
	}
	for (int i = 0; i < (vec.size() - 1); ++i) {
		if (strcmp(vec[i], vec[i + 1]) > 0) {
			cout << "ERROR: character order" << endl;
			cout << "vec[" << i <<  "] = " << vec[i] << " > " << "vec[" << i + 1 << "] = " << vec[i + 1] << endl;
			vec.clear();
			return false;
		}
	}

	vec.clear();
	return true;
}


void BTree::Is_BTree_help(BNode *node, vector<char*> &vec)
{
	int children_count = 0;
		for (int i = 0; i < node->count + 1; ++i) {
		if (node->children[i] != nullptr)
			Is_BTree_help(node->children[i], vec);

		if (node->count < t - 1 && node != root) {
			cout << "ERROR in count of keys" << endl;
			indic_is_btree++;
		}

		if (i < node->count) {
			if (node->keys[i] == nullptr) {
				cout << "ERROR in keys" << endl;
				indic_is_btree++;
			}
			else
				vec.push_back(node->keys[i]->word);
		}

		if (node->children[i] != nullptr) {
			children_count++;
		}

	}
	if (children_count - 1 != node->count && children_count > 0) {
		cout << "ERROR: keys->count and children->count" << endl;
		indic_is_btree++;
	}
}

void BTree::Delete_tree(BNode *node)
{
	//cout << "sss" << endl;
	for (int i = 0; i < 2 * t; ++i) {
		//cout << "sss2" << endl;
		if (node->children[i] != nullptr) {
			//cout << "sss1" << endl;
			Delete_tree(node->children[i]);
		}
		if (i < 2 * t - 1) {
			if (i < node->count) {
				//cout << "1" << endl;
				delete[] node->keys[i]->word;
			}
			//cout << "2" << endl;
			delete node->keys[i];
		}
		//cout << "3" << endl;
		delete node->children[i];
	}
	//delete[] node->children;
	//delete[] node->keys;
	//cout << "4" << endl;
}

void BTree::Load_from_file(char *path_to_file)
{
	ifstream file;
	file.open(path_to_file);
	if (!file.is_open()) {
		cout << "ERROR: Incorrect path to file" << endl;
		return;
	}
	if (root != nullptr) {
		Delete_tree(root);
		delete root;
	}
	root = nullptr;
	root = Loader_help(root, file, 0);
}

BNode* BTree::Loader_help(BNode *node, ifstream &file, int level)
{
	int local_level = 0;
	char *keyZ = new char[2];
	node = new BNode;
	memset(node, 0, sizeof(BNode));


	node = Node_key_scan(node, file);


	do {
		file >> keyZ;
		local_level++;
	} while (strcmp(keyZ, "@") == 0);

	if (file.eof()) {
		delete[] keyZ;
		return node;
	}

	for (int i = 0; i < node->count + 1; i++) {  // ??????? ? ????? node
		if (local_level > level) {
			node->children[i] = Loader_help(node->children[i], file, local_level);
		}
		else break;
	}
	delete[] keyZ;
	return node;
}


BNode* BTree::Node_key_scan(BNode *node, ifstream &file)
{
	char keyZ[2];
	while (true) {  // ?????????? keys
		node->keys[node->count] = new Type;
		//node->keys[node->count]->word = new char[257];
		file >> node->keys[node->count]->word;
		file >> node->keys[node->count]->number;
		node->count++;
		file >> keyZ;
		if (strcmp(keyZ, "%") == 0) {
			break;
		}
	}
	return node;
}

void BTree::Create_empty_node(BNode *node)
{

	for (int i = 0; i < 2 * t; ++i) {
		if (i < 2 * t - 1) {
			node->keys[i] = nullptr;
		}
		node->children[i] = nullptr;
	}

	node->count = 0;
}




bool BTree::Save(const char *filename)
{
    FILE* f = fopen(filename, "wb");

    if (!f) {
        printf("ERROR: Can`t open the file %s", filename);
        return false;
    }
		bool ans = true;
    if(root){
    	ans = mSave(f, root);
		}

    fclose(f);

    return ans;
}


bool BTree::mSave(FILE *f, BNode *node)
{
    if (fwrite(&node->count, sizeof(node->count), 1, f) != 1) {
        return false;
    }

	bool leaf;
	if (node->children[0] == nullptr)
		leaf = true;
	else
		leaf = false;

    if (fwrite(&leaf, sizeof(leaf), 1, f) != 1) {
        return false;
    }

    for (size_t i = 0; i < node->count; ++i) {

        if (fwrite(&node->keys[i]->word_count, sizeof(node->keys[i]->word_count), 1, f) != 1) {
            return false;
		}

        if (fwrite(node->keys[i]->word, sizeof(char), node->keys[i]->word_count, f) != node->keys[i]->word_count) {
            return false;
        }

        if (fwrite(&node->keys[i]->number, sizeof(node->keys[i]->number), 1, f) != 1) {
            return false;
        }
    }

    if (node->children[0] != nullptr) {
        for (size_t i = 0; i < node->count + 1; ++i) {
            if (!mSave(f, node->children[i])) {
                return false;
            }
        }
    }

    return true;
}


bool BTree::Load(const char *filename)
{
    FILE* f = fopen(filename, "rb");

    if (!f) {
        printf("ERROR: Can`t open the file \n");
        return false;
    }

	BNode *rootNew = new BNode;
	memset(rootNew, 0, sizeof(BNode));
    bool ans = mLoad(f, rootNew);
    fclose(f);
    if (ans) {
		if (root != nullptr)
			Delete_tree(root);
		delete root;
        root = rootNew;
        return true;
    } else {
        if (root != nullptr)
			Delete_tree(root);
		delete root;
        return false;
    }
}

bool BTree::mLoad(FILE *f, BNode *node)
{
    //char buffer[257];

    if (fread(&node->count, sizeof(node->count), 1, f) != 1) {
        return true; //false?
    }
	bool leaf;
	if (fread(&leaf, sizeof(leaf), 1, f) != 1) {
        return false;
    }
    for (size_t i = 0; i < node->count; ++i) {
        node->keys[i] = new Type;


        if (fread(&node->keys[i]->word_count, sizeof(node->keys[i]->word_count), 1, f) != 1) {
            return false;
        }

		node->keys[i]->word = new char[node->keys[i]->word_count + 1];

        if (fread(node->keys[i]->word, sizeof(char), node->keys[i]->word_count, f) != node->keys[i]->word_count) {
            return false;
        }
        if (fread(&node->keys[i]->number, sizeof(node->keys[i]->number), 1, f) != 1) {
            return false;
        }
        node->keys[i]->word[node->keys[i]->word_count] = '\0';
    }

    if (!leaf) {
        for (size_t i = 0; i < node->count + 1; ++i) {
			node->children[i] = new BNode;
			memset(node->children[i], 0, sizeof(BNode));
            if (!mLoad(f, node->children[i])) {
                return false;
            }
        }
    }

    return true;
}
