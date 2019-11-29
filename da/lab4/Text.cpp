#include "Text.h"


Text::Text(size_t Pattern_count)
{
	T = new TData[Pattern_count];
	count = Pattern_count;
	line = 1;
	pos = 0;
	local_index = 0;
}


Text::~Text() 
{
	delete[] T;
}


size_t Text::Get_result_index(size_t i)
{
	size_t id = local_index + i;
	if (id > count - 1) {
		return id - count;
	}
	else {
		return id;
	}
}



bool Text::Right_shift(size_t shift_count)
{
	char ch;
	size_t key;
	int i = 0;
	size_t result_index;

	

	
	while (i < shift_count) {
		while (true) {
			ch = getchar();
			if (ch == EOF) return false;
			if (isspace(ch)) {
				if (ch == '\n') {
					line++;
					pos = 0;
				}
			}
			else {
				ungetc(ch, stdin);
				break;
			}
		}

		cin >> key;
		pos++;

		result_index = Get_result_index(i);

		T[result_index].key = key;
		T[result_index].line = line;
		T[result_index].pos = pos;
		T[result_index].M = 0;
		
		i++;
	}

	local_index = Get_result_index(shift_count);

	return true;
}

void Text::TPrint()
{
	size_t result_index;
	for (size_t i = 0; i < count; ++i) {
		result_index = Get_result_index(i);
		cout << T[result_index].key << " ";
	}
	cout << endl;
}

TData Text::operator[](size_t index)
{
	return T[Get_result_index(index)];
}

void Text::Inc_M(size_t index, long M_value)
{
	T[Get_result_index(index)].M = M_value;
}