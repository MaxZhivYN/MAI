#include "MultiList.h"



MultiList::MultiList()
{
	count = 0;
}


MultiList::~MultiList() {}


bool MultiList::Add_elem(istream &file, bool is_cin) 
{
	shared_ptr<MultiList_Elem> node_new = stud_ending.last;
	if (!node_new) {  //  Если мультисписок пуст
		if (is_cin)
			stud_ending.first = make_shared<MultiList_Elem>();
		else
			stud_ending.first = make_shared<MultiList_Elem>(file);
		if (!stud_ending.first) return false;
		stud_ending.last = stud_ending.first;

		alph_ending.first = stud_ending.first;
		alph_ending.last = stud_ending.first;

		points_ending.first = stud_ending.first;
		points_ending.last = stud_ending.first;
		
	}
	else {
		if (is_cin)
			stud_ending.last->stud_way.next = make_shared<MultiList_Elem>();
		else
			stud_ending.last->stud_way.next = make_shared<MultiList_Elem>(file);
		
		//  Вставка в список студентов (всегда в конец списка)
		if (!stud_ending.last->stud_way.next) return false;
		stud_ending.last->stud_way.next->stud_way.prev = stud_ending.last;
		stud_ending.last = stud_ending.last->stud_way.next;
		node_new = stud_ending.last;

		shared_ptr<MultiList_Elem> i;
		shared_ptr<MultiList_Elem> prev_i;


		//  Вставка в список студентов отсортированных по алфавиту (производится методом, использующимся в сортировке вставкой)
		for (i = alph_ending.first; i && node_new->st.FIO > i->st.FIO; i = i->alph_way.next);
		if (i) {
			prev_i = i->alph_way.prev;
			if (prev_i) {
				prev_i->alph_way.next = node_new;
				node_new->alph_way.prev = prev_i;
			}
			else alph_ending.first = node_new;

			node_new->alph_way.next = i;
			i->alph_way.prev = node_new;
		}
		else {
			alph_ending.last->alph_way.next = node_new;
			node_new->alph_way.prev = alph_ending.last;
			alph_ending.last = node_new;
		}

		//  Вставка в список студентов отсортированных по сумме баллов (производится методом, использующимся в сортировке вставкой)
		for (i = points_ending.first; i && node_new->st.points > i->st.points; i = i->points_way.next);
		if (i) {
			prev_i = i->points_way.prev;
			if (prev_i) {
				prev_i->points_way.next = node_new;
				node_new->points_way.prev = prev_i;
			}
			else points_ending.first = node_new;

			node_new->points_way.next = i;
			i->points_way.prev = node_new;
		}
		else {
			points_ending.last->points_way.next = node_new;
			node_new->points_way.prev = points_ending.last;
			points_ending.last = node_new;
		}
	}
	count++;
	return true;
}

void MultiList::All_alph_print() 
{
	if (!stud_ending.first) {
		cout << "Список пуст." << endl;
		return;
	}
	for (shared_ptr<MultiList_Elem> i = alph_ending.first; i; i = i->alph_way.next) {
		cout << i->st.FIO << setw(15) << i->st.group_number << setw(15) << i->st.points << endl;
	}
}

void MultiList::Group_alph_print(int group) 
{
	if (!stud_ending.first) {
		cout << "Список пуст." << endl;
		return;
	}

	bool true_group = false;
	for (shared_ptr<MultiList_Elem> i = alph_ending.first; i; i = i->alph_way.next) {
		if (i->st.group_number == group) {
			cout << i->st.FIO << setw(15)  << i->st.points << endl;
			if (!true_group) true_group = true;
		}
	}

	if (!true_group) {
		cout << "В указанной вами группе нет студентов в списке." << endl;
	}
}


void MultiList::Group_points_print(int group) 
{
	if (!stud_ending.first) {
		cout << "Список пуст." << endl;
		return;
	}

	bool true_group = false;
	for (shared_ptr<MultiList_Elem> i = points_ending.last; i; i = i->points_way.prev) {
		if (i->st.group_number == group) {
			cout << i->st.FIO << setw(15)  << i->st.points << endl;
			if (!true_group) true_group = true;
		}
	}

	if (!true_group) {
		cout << "В указанной вами группе нет студентов в списке." << endl;
	}
}


void MultiList::All_points_print(int points) 
{
	if (!stud_ending.first) {
		cout << "Список пуст." << endl;
		return;
	}

	bool true_group = false;
	for (shared_ptr<MultiList_Elem> i = points_ending.first; i && i->st.points < points; i = i->points_way.next) {
		cout << i->st.FIO << setw(15) << i->st.group_number << setw(15) << i->st.points << endl;
		if (!true_group) true_group = true;
	}

	if (!true_group) {
		cout << "Студентов с суммой балов ниже указаной не обнаружено." << endl;
	}
}


void MultiList::Print()
{
	if (!stud_ending.first) {
		cout << "Список пуст." << endl;
		return;
	}
	for (shared_ptr<MultiList_Elem> i = stud_ending.first; i; i = i->stud_way.next) {
		cout << i->st.FIO << setw(15) << i->st.group_number << setw(15) << i->st.points << endl;
	}
}


bool MultiList::Save() 
{
	if (!stud_ending.first) {
		cout << "Вы не добавили ни одого студента." << endl;
		return false;
	}
	ofstream file;
	string file_name;
	cout << "Введите название файла: ";
	cin >> file_name;
	cout << endl;
	file.open(file_name);
	if (!file.is_open()) return false;
	
	file << count << endl;

	for (shared_ptr<MultiList_Elem> i = stud_ending.first; i; i = i->stud_way.next) {
		file << i->st.FIO << " " << i->st.Birth_Date << " " << i->st.group_number << " " << i->st.points << endl;
	}
	return true;
}


bool MultiList::Load()
{
	ifstream file;
	string file_name;
	cout << "Введите название файла: ";
	cin >> file_name;
	cout << endl;
	file.open(file_name);
	if (!file.is_open()) return false;
	
	if (stud_ending.first) {
		DeleteList(stud_ending.first);

		stud_ending.first.reset();
		stud_ending.last.reset();

		alph_ending.first.reset();
		alph_ending.last.reset();

		points_ending.first.reset();
		points_ending.last.reset();
	}

	size_t local_count;
	file >> local_count;
	
	for (size_t i = 0; i < local_count; ++i) {
		if(!Add_elem(file, false)) return false;
	}

	return true;
}


void MultiList::DeleteList(shared_ptr<MultiList_Elem> listelem)
{
	if (listelem) {
		DeleteList(listelem->stud_way.next);
			
		listelem->alph_way.next.reset();
		listelem->alph_way.prev.reset();

		listelem->stud_way.next.reset();
		listelem->stud_way.prev.reset();

		listelem->points_way.next.reset();
		listelem->points_way.prev.reset();
	}
}