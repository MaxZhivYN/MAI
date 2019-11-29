#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "vector.h"

#define t 2

struct Type_fly {
	unsigned long long number;
	char word[257];
	size_t word_count;
};


struct Type {
	unsigned long long number;
	char *word;
	size_t word_count;
};

struct BNode {
	Type *keys[2 * t- 1];
	BNode *children[2 * t];
	int count;
};

class BTree
{
public:
	BTree();
	~BTree();
	void Print();
	void Print(char *keyZ);
	void Print1();
	bool insert(Type_fly key);
	Type *search(char *key);
	bool new_remove(char *key);
	void Delete_tree(BNode *node);

	bool Save(const char *filename);
	bool Load(const char *filename);

	bool Is_BTree();
	void Load_from_file(char *file);
	void Get_copy(char *buff, char *data_word, int word_count);
	BNode *root;
private:
	void print_b_tree(BNode *a, int level);
	void print_b_tree(std::ofstream &output, BNode *node, int level);
	void print_b_tree1(BNode *node, int level);

	void insert_to_node(Type *key, BNode *node);
	BNode *split(BNode *node);
	void get_pa_and_node_id_in_pa(char *node_first_key, BNode* &node_out, int &node_id_in_pa);
	void get_pa_and_node_id_in_pa_all(BNode *node, BNode *node_parent, BNode* &node_out, int &node_id_in_pa);



	void remove_from_node(BNode *node, char *key, bool true_delete);
	void Node_fix(BNode *node, std::shared_ptr<MyVector<BNode*>> back_vector);
	void left_restruct(BNode* pa, int node_id_in_pa);
	void right_restruct(BNode* pa, int node_id_in_pa);
	void get_node_for_middle_restract_left(BNode *pa, int node_id, BNode *node_out);
	void get_node_for_middle_restract_right(BNode *pa, int node_id, BNode *node_out);

	void Is_BTree_help(BNode *node, std::vector<char*> &vec);

	
	BNode* Loader_help(BNode *node, std::ifstream &file, int level);
	void Create_empty_node(BNode *node);
	BNode* Node_key_scan(BNode *node, std::ifstream &file);

	bool mSave(FILE *f, BNode *node);
	bool mLoad(FILE *f, BNode *node);
};