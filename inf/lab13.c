#include <stdio.h>
#include <ctype.h>

#include <inttypes.h>
#include <stdbool.h>

typedef uint32_t Set;
#define EMPTY_SET ((Set) 0UL)

Set set_insert(Set s, unsigned idx)
{
    return s | ((Set) 1UL << idx);
}


Set set_intersection(Set s1, Set s2)
{
    return s1 & s2;
}


bool is_latin(int c)
{
    c = tolower(c);
    return c >= 'a' && c <= 'z';
}

bool is_vowel(int c)
{
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}


int get_index(int c)
{
    if (islower(c)) {
        return c - 'a';
    }
    return c - 'A';
}

Set get_vowels(void)
{
    Set s = EMPTY_SET;
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    for (int i = 0; i < (int)(sizeof(vowels) / sizeof(vowels[0])); ++i) {
        s = set_insert(s, get_index(vowels[i]));
    }
    return s;
}






int main(void)
{
    bool result = false;
    
    Set letters_curr = EMPTY_SET;
    
    int c = 0;
    do {
        c = getchar();
        if (isspace(c) || iscntrl(c)) {
            if (set_intersection(letters_curr, get_vowels()) == get_vowels()) {
                result = true;
                break;
            }
            letters_curr = EMPTY_SET;
        } else {
            if (is_vowel(c)) {
                letters_curr = set_insert(letters_curr, get_index(c));
            }
        }
    } while (c != EOF);
                    
    printf(result ? "Yes\n" : "No\n");
    return 0;
}