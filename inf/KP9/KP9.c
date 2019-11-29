#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define MAXSTRING 100
#define MAXELEM 100

int n;
struct ln
{
  int key;
  char str[MAXSTRING];
}line[MAXELEM];

void shakesort()
{
  int  i, k, left, right;
  struct ln t;
  left = 1;
  right = n-1;
  do
  {
    for (i = right; i >= left; i--)
    {
      if (line[i - 1].key>line[i].key)
      {
        t = line[i - 1];
        line[i - 1] = line[i];
        line[i] = t;
        k = i;
      }
    }
    left=k+1;
    for (i = left; i <= right; i++)
    {
      if (line[i - 1].key>line[i].key)
      {
        t = line[i - 1];
        line[i - 1] = line[i];
        line[i] = t;
        k = i;
      }
    }
    right=k-1;
  } while (left<right);
}

void sprint()
{
  printf("\nKey:\tElement:\n");
  for (int i = 0; i<n; i++)
    printf("%d %s", line[i].key, line[i].str);
}

void randomize()
{
  long a = time(0);
  srand(a);
}

void randperm()
{
  struct ln temp;
  for (int i = 0; i<n; i++)
  {
    int j = rand() % n;
    temp = line[i];
    line[i] = line[j];
    line[j] = temp;
  }
}

void revers()
{
  struct ln temp;
  for (int i = 0; i<n / 2; i++)
  {
    temp = line[i];
    line[i] = line[n- i-1];
    line[n- i-1] = temp;
  }
}

void bsearch1()
{
  int m, left = 0, right = n - 1;
  int key;
  printf("Enter key: ");
  scanf("%d", &key);
  while (left<right) {
    m = (left + right) / 2;
    if (key>line[m].key)
      left = m + 1;
    else  right = m;
  }
  if (key == line[left].key)
    printf("Key is found:\n%d %s", key, line[left].str);
  else printf("Key not found\n");
}

int menu() {
  int m;
  printf("\nProgram menu:\n");
  printf("1 - Print file\n");
  printf("2 - Shaker sorting\n");
  printf("3 - RandPermutation\n");
  printf("4 - Revers\n");
  printf("5 - Binary search\n");
  printf("0 - Exit\n");
  printf("\nEnter action: ");
  scanf("%d", &m);
  return m;
}

int main(int argc, char *argv[])
{
  FILE *f;
  int i;
  int m;
  int z = 0;
  if (argc==1)
 {if( (f=fopen("in1.txt","r")) == NULL ) {printf("File doesn't exists\n"); return 1;}}
else
if( (f=fopen(argv[1],"r")) == NULL ) {printf("File doesn't exists\n"); return 1;}
  n = 0;
  while (!feof(f))
  {
    fscanf(f, "%d", &line[n].key);
    fgets(line[n].str, MAXSTRING, f);
    n++;
  } n--;
  while (1)
  {
    m = menu();
    switch (m)
    {
    case 1: {sprint(); break; }
    case 2: {shakesort();z = 1; break; }
    case 3: {randperm(); z = 0; break; }
    case 4: {revers(); z = 0; break; }
    case 5: {if (z)bsearch1(); else printf("You should sort first\n"); break; }
    case 0: {fclose(f); return 0; }
    default: {printf("\nInvalide menu action\n"); break; }
    }
  }
}
