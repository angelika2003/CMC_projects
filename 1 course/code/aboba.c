
//БАЗОВЫЕ АЛГОРИТМЫ
int gcd_recursive(int x, int y) {
    if (!y) {
        return x;
    }

    return gcd_recursive(y, x % y);
}

void swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int power_fast(int num, int deg) {
    int result = 1;

    while (deg) {
        if (deg % 2 == 0) {
            deg /= 2;
            num *= num;
        } else {
            deg--;
            result *= num;
        }
    }

    return result;
}

int gcd(int x, int y) {
    int tmp;

    while (y) {
        tmp = y;
        y = x % y;
        x = tmp;
    }

    return x;
}

int get_number(int x) {
    char c = getchar();

    while (c != ' ' && c != '\n') {
        x *= 10;
        x += c - '0';
        c = getchar();
    }

    return x;
}

void reverse(void) {
    int x;
    scanf("%d", &x);

    if (x) {
        reverse();
        printf("%d ", x);
    }
}

int is_prime(int x) {
    if (x == 1) {
        return 0;
    }

    int sq = (int)sqrt(x);

    for (int i = 2; i <= sq; i++) {
        if (x % i == 0) {
            return 0;
        }
    }

    return 1;
}

void print_array(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");
}

// ----------------------------------------------------
// СОРТИРОВКИ
// ----------------------------------------------------

void insertion_sort(int* a, int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];

        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

/* Если дадут задание на квиксорт, то надо будет отсортировать по заданному компаранду
 идешь i j слева и справа и если стоит слева от компаранда больше а там меньше свапаешь */
void quick_sort(int* a, int left, int right) {
    int i = left;
    int j = right;

    int comp = a[(left + right) / 2];

    while (i <= j) {
        while (i < right && a[i] < comp) {
            i++;
        }

        while (j > left && a[j] > comp) {
            j--;
        }

        if (i <= j) {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++, j--;
        }
    }

    if (i < right) {
        quick_sort(a, i, right);
    }

    if (j > left) {
        quick_sort(a, left, j);
    }
}

void bubble_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;

        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

// ----- ПИРАМИДАЛЬНАЯ СОРТИРОВКА -----
/* Правила пирамидальной сортировки (ДЛЯ НУМЕРАЦИИ С 1)!!!!
 1) a[i] - узел дерева элемент a[i/2] - родитель узла a[i]
 ЛИБО 2) a[i] - родитель, а дети у него a[2 * i] a[2 * i]
 
 ПРИЧЕМ a[i] >= a[2 * i] и a[i] >= a[2 * i + 1]
 ИЛИ a[i / 2] <= a[i]
 
 ДЛЯ НУМЕРАЦИИ С НУЛЯ (a[i] >= a[2 * i + 1] и a[i] >= a[2 * i + 2]
 
 ПРАВИЛО ЗАПОЛНЕНИЯ КУЧИ a[i] - корень  a[i + 1] - левый сын a[i + 2] - правый сын*/
void sift(int* a, int l, int r) {
    int j = 2 * l + 1;

    if (j < r && a[j] < a[j + 1]) {
        j++;
    }

    int x = a[l];

    while (j <= r && x < a[j]) {
        a[l] = a[j];
        a[j] = x;

        l = j, j = 2 * j + 1;

        if (j < r && a[j] < a[j + 1]) {
            j++;
        }
    }
}

void heapsort(int* a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        sift(a, i, n - 1);
    }

    for (int i = n - 1; i > 0; i--) {
        int tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;

        sift(a, 0, i - 1);
    }
}

// ------------- MERGE_SORT --------------

void merge(int x[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int x1[n1], x2[n2];

    for (int i = 0; i < n1; i++) {
        x1[i] = x[l + i];
    }

    for (int j = 0; j < n2; j++) {
        x2[j] = x[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (x1[i] <= x2[j]) {
            x[k++] = x1[i++];
        } else {
            x[k++] = x2[j++];
        }
    }

    while (i < n1) {
        x[k++] = x1[i++];
    }

    while (j < n2) {
        x[k++] = x2[j++];
    }
}

void merge_sort(int x[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;

        merge_sort(x, l, m);
        merge_sort(x, m + 1, r);

        merge(x, l, m, r);
    }
}

// ----------------------------------------------
// ----------------------------------------------
//СТРОКИ
// ----------------- KMP ------------------------

void prefix_function(char* pattern, int m, int* pi) {
    int j = 0;

    pi[0] = 0;

    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[j]) {
            j++;
            pi[i] = j;
            i++;
        } else {
            if (j) {
                j = pi[j - 1];
            } else {
                pi[i] = 0;
                i++;
            }
        }
    }
}

void KMP_search(char* text, char* pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    int pi[m];

    prefix_function(pattern, m, pi);

    int i = 0;  // index for text
    int j = 0;  // index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == m) {
            // Например,
            //   printf("Found pattern at index %d ", i - j);

            j = pi[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = pi[j - 1];
            } else {
                i++;
            }
        }
    }
}

// --------------- СПИСКИ ------------------

typedef struct List {
    int value;
    struct List* next;
} List;

void push_back(struct list** tail, int value) {
    struct list* tail_new = (struct list*)malloc(sizeof(struct list));
    tail_new->value = value;
    (*tail)->next = tail_new;

    if (tail != NULL) {
        tail_new->prev = *tail;
    }

    tail_new->next = NULL;
    *tail = tail_new;
}

void reverse_list(List** head) {
    List* cur = *head;
    List* prev = NULL;
    List* next = NULL;

    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    *head = prev;
}
void delete_list(List** head) {
    List* cur = *head;

    while (cur) {
        List* next = cur->next;
        free(cur);
        cur = next;
    }

    *head = NULL;
}

void push_front(struct list** head, int value) {
    struct list* new_node = (struct list*)malloc(sizeof(struct list));
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}

struct list* middle(struct list* head) {
    struct list* slow = head;
    struct list* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

struct list* merge(struct list* head_1, struct list* head_2) {
    struct list* new_head_cure = (list*)malloc(sizeof(list));
    new_head_cure->next = NULL;

    struct list* head_merged = new_head_cure;

    while (head_1 && head_2) {
        if (head_1->value < head_2->value) {
            new_head_cure->next = head_1;
            head_1 = head_1->next;
        } else {
            new_head_cure->next = head_2;
            head_2 = head_2->next;
        }
        new_head_cure = new_head_cure->next;
    }

    while (head_1) {
        new_head_cure->next = head_1;
        head_1 = head_1->next;
        new_head_cure = new_head_cure->next;
    }
    
    while (head_2) {
        new_head_cure->next = head_2;
        head_2 = head_2->next;
        new_head_cure = new_head_cure->next;
    }
    
    delete_list(&head_1);
    delete_list(&head_2);

    return head_merged->next;
}

struct list* merge_sort(struct list* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct list* left = head;
    struct list* right = middle(head);

    struct list* tmp = right->next;
    right->next = NULL;
    right = tmp;

    left = merge_sort(left);
    right = merge_sort(right);

    return merge(left, right);
}

//==================================
//ДЕРЕВЬЯ
//==================================

//-------------------------------------
//КРАСНО_ЧЕРНОЕ ДЕРЕВО
//------------------------------------
/* Красно-черное дерево - это дерево поиска, каждая вершина которого окрашена в красныф либо черный цвет
 св-ва
 0)Корень - черный
 1)каждая вершина имеет цвет
 2)каждый лист (==NULL) - черный
 3)если вершина красная, то ее сыновья черные
 4)все пути от корня до каждого листа имеют одинаковое кол-во черных вершин на своем пути*/

typedef struct rbtree {
    int key;
    char color;
    struct rbtree *left, *right, *parent;
} rbtree, *prtree;

//---------------------------------
//БИНАРНОЕ ДЕРЕВО ПОИСКА
//--------------------------------

typedef struct tree {
    int key;
    struct tree* parent;
    struct tree* left;
    struct tree* right;
} tree;

void print_tree(struct tree* root) {
    if (!root) {
        return;
    }
    
    print_tree(root->left);
    printf("%d ", root->key);
    
    print_tree(root->right);
}

void insert(struct tree* root, int key) {
    if (!root->left && root->key > key) {
        tree* new_node = malloc(sizeof(tree) * 1);
        new_node->key = key;
        root->left = new_node;
        new_node->parent = root;
        new_node->left = NULL;
        new_node->right = NULL;
        
        return;
    }
    else if (!root->right && root->key < key) {
        tree* new_node = malloc(sizeof(tree) * 1);
        new_node->key = key;
        root->right = new_node;
        new_node->parent = root;
        new_node->left = NULL;
        new_node->right = NULL;
        
        return;
    }
    
    if (key > root->key) {
        root = root->right;
        insert(root, key);
    }
    else if (key < root->key) {
        root = root->left;
        insert(root, key);
    }
    else {
        return;
    }
}

//ОЧЕНЬ ВАЖНАЯ ШТУКА ДЕЛАЮЩАЯ ОБХОД ДЕРЕВА И ЗАПИСЫВАЮЩАЯ В МАССИВ УКАЗАТЕЛИ ДЕРЕВА ПО ВОЗРАСТАНИЮ !
tree* cure = root;
tree* stack[200];
tree* nodes[200];

int top = 0;
int j = 0;
int nodes_count = 0;

if (!cure) {
    return 0;
}

while (1) {
    while (cure) {
        stack[++top] = cure;
        cure = cure->left;
    }
    
    cure = stack[top--];
    
    if (cure) {
        nodes[nodes_count++] = cure;
        cure = cure->right;
    } else {
        break;
    }
}
//-------------------------

int find_node(struct tree *node, int key) {
    while (node && key != node->key) {
        if (key > node->key) {
            node = node->right;
        }
        else {
            node = node->left;
        }
    }
    
    if (!node) {
        return 0;
    }
    
    return 1;
}

struct BT_node *BTdelete(struct BT_node**root ,struct BT_node *n) {
    struct BT_node *x, *y;
    y = (!n -> left || ! n -> right) ? n : BT_succ(n);
    x = y -> left ? y -> left : y -> right;
    if x
        x -> parent = y -> parent;
    if (!y -> parent)
        *root = x;
    else {
        if (y == y -> parent -> left)
            y -> parent -> left = x;
        else
            y -> parent -> right = x;
        
        if (y != n)
            n -> key = y -> key;
        
    return y;
}
//--------------------------------------------------------------------------
//AVL ДЕРЕВО
//--------------------------------------------------------------------------
typedef struct avlnode {
    char* server_name;
    long long server_ip;
    struct avlnode* right;
    struct avlnode* left;
    int height;
} avlnode;

int height(avlnode* node) {
    if (node) {
        return node->height;
    }

    return 0;
}

struct avlnode* single_rotate_left(avlnode* old_father) { //если высота правого поддерева стала больше левого больше чем на 1
    avlnode* new_father = old_father->left; //сам поворот "переподвешивание к новому отцу"
    old_father->left = new_father->right;
    new_father->right = old_father;

    new_father->height = max(height(new_father->left), height(new_father->right)) + 1; //корректируем высоты переставленных узлов
    old_father->height = max(height(old_father->left), height(old_father->right)) + 1;

    return new_father; //новый корень дерева
}

struct avlnode* single_rotate_right(avlnode* old_father) { //если высота левого поддерева стала больше правого больше чем на 1
    avlnode* new_father = old_father->right; //аналогично
    old_father->right = new_father->left;
    new_father->left = old_father;

    old_father->height = max(height(old_father->left), height(old_father->right)) + 1;
    new_father->height = max(height(new_father->left), height(new_father->right)) + 1;

    return new_father;
}

struct avlnode* double_rotate_right(avlnode* father) { //идет постепенная балансировка правого с несбалансированным ответвлением к общему авл виду
    father->right = single_rotate_left(father->right);

    return single_rotate_right(father);
}

struct avlnode* double_rotate_left(avlnode* father) {
    father->left = single_rotate_right(father->left);

    return single_rotate_left(father);
}

struct avlnode* insert(long long server_ip, char* server_name, avlnode* root) {
    if (root == NULL) { //если пустое дерево
        root = (avlnode*)malloc(sizeof(avlnode));
        root->server_name = (char*)calloc(MAX_LEN, sizeof(char));

        strcpy(root->server_name, server_name);
        root->server_ip = server_ip;
        root->height = 1;
        root->left = NULL;
        root->right = NULL;
    } else if (strcmp(server_name, root->server_name) > 0) { //если то, что вставляем больше ключа текущего узла, то идем направо
        root->right = insert(server_ip, server_name, root->right);

        if (height(root->right) - height(root->left) == 2) { //проверяем сохранилось ли после вставки св-во авл дерева и нужна ли балансировка
            if (strcmp(server_name, root->right->server_name) > 0) {
                root = single_rotate_right(root);
            } else {
                root = double_rotate_right(root);
            }
        }
    } else if (strcmp(server_name, root->server_name) < 0) { //если то, что вставляем меньше ключа текущего узла, то идем налево
        root->left = insert(server_ip, server_name, root->left);

        if (height(root->left) - height(root->right) == 2) { //проверяем сохранилось ли после вставки св-во авл дерева и нужна ли балансировка
            if (strcmp(server_name, root->left->server_name) < 0) {
                root = single_rotate_left(root);
            } else {
                root = double_rotate_left(root);
            }
        }
    }
    
    root->height = max(height(root->left), height(root->right)) + 1; //корректирока высоты

    return root;//возвращаем новый корень перестроенного авл дерева
}

struct avlnode* find(char* server_name, avlnode* node) {
    if (node == NULL || strcmp(server_name, node->server_name) == 0) { //нашлось\не нашлось 0 == дошли до конца и нечего дальше проверять
        return node;
    }

    if (strcmp(server_name, node->server_name) < 0) { //если искомая строка меньше той где находимся, то логично идти налево, где значения меньше
        return find(server_name, node->left);
    }

    return find(server_name, node->right);//иначе идем направо, где значения больше
}

void delete_avl_tree(avlnode* root) {
    if (root != NULL) {
        delete_avl_tree(root->left);
        delete_avl_tree(root->right);
        free(root);
    }
}
}

//===========================
//ВАРИАНТ ИЗ НИУ ВШЭ !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//============================

//НОМЕР НА СТРОКИ
 1 РЕШЕНИЕ (без динамики)
 #define N 100

 int main(void) {
     char s[N/2][N + 2];
     int j = 0;
     int ch = 0;

     char buf_s[N+2];
     char c;

     while ((c = getchar()) != '\n' && c != EOF) {
         // определена в <stdio.h>
         // прототип int ungetc( int character, FILE * filestream );
         // возвращает символ "character" в поток "filestream"
         ungetc(c, stdin);

         if (ch % 2 == 0) {
             fgets(buf_s, 102, stdin);
             printf("%s", buf_s);
         } else {
             fgets(s[j++], 102, stdin);
         }

         ch++;
     }

     for (int i = j - 1; i >= 0; i--) {
         printf("%s", s[i]);
     }

     return 0;
 }
 
 ----------------------------------------------
 #include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 102

int main(void) {
	char **telegram = (char**)calloc(sizeof(char*), MAX_SIZE);
	for (int i = 0; i < MAX_SIZE; i++) {
		telegram[i] = (char*)malloc(sizeof(char) * MAX_SIZE);
	}

	int j = 0;

	while (fgets(telegram[j], 102, stdin)) {
		j++;
	}

	printf("\n"); //

	for (int i = 1; i < j; i += 2) {
		printf("%s", telegram[i]);
	}

	j--;  //на последнюю строку указывает

	if (j % 2 != 0) {
		j--;
	}

	for (int i = j; i >= 0; i -= 2) {
		printf("%s", telegram[i]);
	}

	return 0;
}

 ======================================================
 2 РЕШЕНИЕ

 #define MAX_LEN 102

 int main(void) {
     char telegram = (char)malloc(sizeof(char*) * MAX_LEN);

     for (int i = 0; i < MAX_LEN; i++) {
         telegram[i] = (char*)malloc(sizeof(char) * MAX_LEN);
     }

     int len = 0, k = 0;
     char* str = malloc(sizeof(char) * MAX_LEN);
     char c;

     while (fgets(str, MAX_LEN, stdin)) {

         if (len % 2 == 0) {
             printf("%s", str);
         }
         else {
             strcpy(telegram[k], str);
             k++;
         }

         if ((c = getchar()) == '\n' || c == EOF) {
                           break;
         }

         ungetc(c, stdin);

         len++;
     }

     free(str);

     for (int i = k; i >= 0; i--) {
         printf("%s", telegram[i]);
         free(telegram[i]);
     }

     free(telegram);

     return 0;
 }
===========================
3 РЕШЕНИЕ

int main(void) {
    char** s = (char**)calloc(MAX_LEN, sizeof(char*));
    for (int i = 0; i < MAX_LEN; i++) {
        s[i] = (char*)calloc(MAX_LEN + 2, sizeof(char));
    }

    int i = 0;
    while (fgets(s[i], MAX_LEN + 2, stdin)) {
        if (i % 2 != 0) {
            printf("%s", s[i]);
        }
        i++;
    }

    if ((i - 1) % 2 != 0) {
        i--;
    }
    for (int j = i - 1; j >= 0; j -= 2) {
        printf("%s", s[j]);
    }

    for (int j = 0; j < MAX_LEN; j++) {
        free(s[j]);
    }
    free(s);

    return 0;
}

//НОМЕР НА ДЕРЕВО
int layer_size(struct Tree* root, int n) {
    if (!root) {
        return 0;
    }

    static int cnt;

    if (n == 1) {
        cnt++;
    } else {
        layer_size(root->left, n - 1);
        layer_size(root->right, n - 1);
    }

    return cnt;
}

int layer_size (struct Tree *root, int n) {
	if (root == NULL) {
		return 0;
	}

	if (n == 1) {
		if (root != NULL) {
			return 1;
		}
		return 0;
	}

	return layer_size(root->left, n - 1) + layer_size(root->right, n - 1);
}

//МАРКОВ
//удаляет все HE до стоп слова
//заменяет ssE на Ess
//стопается если встретило HEHEHEsHsE
#H->H#
#s->s#
#E->E#
HEHEHEsHsE#->1
*HE->*
H*E->*
*HsEE->ss*
*sEE->Ess*
*H->H*
*E->E*
*s->s*
*->
1=>HEHEHEsHsE
->*#

//интересеное задание
_____1_____
char h = '2';
const char e[] = "lestale";
const char* s = e + 2;

___2____ (так лучше не делать)
char h = '0' - 6;
const char s[] = "stale\0lest";
const char* e = s + 6;


//=========================
//НЕ СЖАТЫЙ БОР
//========================
#define MAX_LEN 2000
#define ALPHABET_LEN 26

typedef struct TreeNode {
    int value;
    
    struct TreeNode* branches[ALPHABET_LEN];
} TreeNode;

void add(char* str, TreeNode* root, int* count) {
    TreeNode* cure = root;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (cure->branches[str[i] - 'a'] == NULL) {
            cure->branches[str[i] - 'a']  = (TreeNode*)malloc(sizeof(TreeNode));
            (*count)++;
        }
        cure = cure->branches[str[i] - 'a'];
    }
}

int main(void) {
    int count = 1;
    struct TreeNode *root = (TreeNode*)malloc(sizeof(TreeNode));
    
    char* str = (char*)malloc(MAX_LEN * sizeof(char));
    
    fgets(str, MAX_LEN, stdin);
    int len = strlen(str) - 1;
    
    for (int i = 0; i < len; i++) {
        char* str_prefix = (char*)calloc(MAX_LEN, sizeof(char));
        
        for (int j = i, k = 0; j < len ; j++, k++) {
            str_prefix[k] = str[j];
        }
        
        add(str_prefix, root, &count);
        
        free(str_prefix);
    }
}

//======================
//побитовые операции
//======================

some_type swap_bits(some_type x, int i, int j) {
    unsigned bit_i = (x >> i) & 1;    // получение i-го бита
    unsigned bit_j = (x >> j) & 1;  // получение j-го бита

    if (bit_i && !bit_j) {
        x |= 1 << j;                 // устанавливаем j-й бит в 1
        x &= ~(1 << i);                // устанавливаем i-й бит в 0
    } else if (!bit_i && bit_j) {
        x |= 1 << i;                // устанавливаем i-й бит в 1
        x &= ~(1 << j);                // устанавливаем j-й бит в 0
    }

    return x;
}

some_type swap_bytes(some_type x) {
    unsigned shift = 8 * (sizeof(some_type) - 1);

    unsigned left_byte = (x >> shift) & 0xFF;
    unsigned right_byte = x & 0xFF;

    unsigned mask = (0xFF << shift) | 0xFF;
    x &= ~mask;                    // зануляем первый и последний байты

    x |= left_byte;             // переставляем байты
    x |= right_byte << shift;    // переставляем байты

    return x;
}

//перевод в сс
#define BASE 19

int main() {
    int x = 0;

    int c;

    while ((c = getchar()) != '\n') {
        x *= BASE;

        if (c >= '0' && c <= '9') {
            x += c - '0';
        } else if (c >= 'a' && c <= 'i') {
            x += 10 + (c - 'a');
        }
    }

    printf("%d\n", x);

    return 0;
}

//решето эретосфена

int main() {
    int a, b;
    scanf("%d%d", &a, &b);

    int prime[b + 1];

    prime[1] = 0;
    for (int i = 2; i <= b; prime[i++] = 1);

    for (int i = 2; i <= (int)sqrt(b); i++) {
        if (prime[i]) {
            for (int j = i * i; j <= b; j += i) {
                prime[j] = 0;
            }
        }
    }

    for (int i = a; i <= b; i++) {
        if (prime[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}

//проверка баланса скобок
int check_brackets(const char* s) {
    int n = strlen(s);

    char stack[n];

    char* t = stack;

    for (*t++ = '\0'; *s; s++) {
        if (*s == '(' || *s == '[') {
            *t++ = *s;
        } else if (*s == ')') {
            if (*(t - 1) != '(') {
                return 0;
            }

            *--t = ' ';
        } else if (*s == ']') {
            if (*(t - 1) != '[') {
                return 0;
            }

            *--t = ' ';
        }
    }

    return (*--t == '\0');
}

//////////////////////////////////////////////////////////////////////////////////////////////
*******************************************************************************************
#############################################################################################


#include <stdio.h>
#include <stdlib.h>

int a = 0;

struct tree {
	int key;
	int height;
	struct tree* left;
	struct tree* right;
};

int height(struct tree* root) {
	return root ? root->height : 0;
}

int max(int x, int y) {
	return x >= y ? x : y;
}

struct tree* LL_turn (struct tree* k2) {
	if (k2->key == 9) {
		a++;
	}

	//printf("L(%d) ", k2->key);

	struct tree* k1;

	k1 = k2->left;
	k2->left = k1->right; /* k1 != NULL */
	k1->right = k2;

	k2->height = max (height (k2->left), height (k2->right)) + 1;
	k1->height = max (height (k1->left), k2->height) + 1;

	return k1;
}

struct tree* RR_turn(struct tree* k2) {
	//printf("R(%d) ", k2->key);
	struct tree* k1;
	k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;

	k2->height = max (height (k2->right), height (k2->left)) + 1;
	k1->height = max (height (k1->right), k2->height) + 1;

	return k1;
}

struct tree* LR_turn (struct tree* k3) {
	k3->left = RR_turn(k3->left);

	return LL_turn(k3);
}

struct tree* RL_turn (struct tree* k3) {
	k3->right = LL_turn(k3->right);

	return RR_turn(k3);
}

struct tree* insert (int x, struct tree* t) {
	if (t == NULL) {
		t = (struct tree *)malloc (sizeof (struct tree));
		t->key = x;
		t->height = 1;
		t->left = t->right = NULL;
	} else if (x < t->key) {
		t->left = insert (x, t->left);
		if ((height (t->left) - height (t->right)) == 2) {
			if (x < t->left->key) {
				t = LL_turn (t);
			} else {
				t = LR_turn (t);
			}
		}
	} else if (x > t->key) {
		t->right = insert (x, t->right);
		if ((height (t->right) - height (t->left)) == 2) {
			if (x > t->right->key) {
				t = RR_turn (t);
			} else {
				t = RL_turn (t);
			}
		}
	}

	t->height = max (height (t->left), height (t->right)) + 1;
	return t;
}

void print_tree(struct tree* root) {
	if (root == NULL) {
		return;
	}
	print_tree(root->left);
	printf("%d(%d) ", root->key, root->height);
	print_tree(root->right);
}

int find(int x, struct tree* t) {
	if (t == NULL) {
		return -1;
	}

	if (x == t->key) {
		return t->key;
	}

	if (x > t->key) {
		return find(x, t->right);
	}

	return find(x, t->left);
}

int main(void) {
/*	struct Tree *root =NULL;
	root = insert(1, root);
	root = insert(2, root);
	root = insert(3, root);
	root = insert(9, root);
	root = insert(4, root);
	root = insert(5, root);
	root = insert(6, root);
	root = insert(7, root);
	root = insert(8, root);
	root = insert(10, root);

	return 0;*/

	for (int a1 = 1; a1 <= 10; a1++) {
		for (int a2 = 1; a2 <= 10; a2++) {
			for (int a3 = 1; a3 <= 10; a3++) {
				for (int a4 = 1; a4 <= 10; a4++) {
					for (int a5 = 1; a5 <= 10; a5++) {
						for (int a6 = 1; a6 <= 10; a6++) {
							for (int a7 = 1; a7 <= 10; a7++) {
								for (int a8 = 1; a8 <= 10; a8++) {
									for (int a9 = 1; a9 <= 10; a9++) {
										for (int a10 = 1; a10 <= 10; a10++) {

											if (a1 != a2 && a1 != a3 && a1 != a4 && a1 != a5 && a1 != a6 && a1 != a7 && a1 != a8 && a1 != a9 && a1 != a10) {
												if (a2 != a3 && a2 != a4 && a2 != a5 && a2 != a6 && a2 != a7 && a2 != a8 && a2 != a9 && a2 != a10) {
													if (a3 != a4 && a3 != a5 && a3 != a6 && a3 != a7 && a3 != a8 && a3 != a9 && a3 != a10) {
														if (a4 != a5 && a4 != a6 && a4 != a7 && a4 != a8 && a4 != a9 && a4 != a10) {
															if (a5 != a6 && a5 != a7 && a5 != a8 && a5 != a9 && a5 != a10) {
																if (a6 != a7 && a6 != a8 && a6 != a9 && a6 != a10) {
																	if (a7 != a8 && a7 != a9 && a7 != a10) {
																		if (a8 != a9 && a8 != a10) {
																			if (a9 != a10) {
																				root = NULL;
																				root = insert(a1, root);
																				root = insert(a2, root);
																				root = insert(a3, root);
																				root = insert(a4, root);
																				root = insert(a5, root);
																				root = insert(a6, root);
																				root = insert(a7, root);
																				root = insert(a8, root);
																				root = insert(a9, root);
																				root = insert(a10, root);
																				
																				if (a == 3) {
																					printf("%d %d %d %d %d %d %d %d %d %d\n", a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
																					
																				}

																				a = 0;
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	//printf("%d\n", find(50, root));
	//print_tree(root);
/*#include <stdio.h>
#include <stdlib.h>

struct tree {
	int x;
	struct tree *left;
	struct tree *right;
};

struct tree *create_new_node(int x) {
	struct tree *new = (struct tree *)malloc(sizeof(struct tree));
	new->x = x;
	new->left = NULL;
	new->right = NULL;

	return new;
}

void add_node(struct tree *head, int x) {
	if (x < head->x) {
		if (head->left == NULL) {
			head->left = create_new_node(x);
			return;
		}
		return add_node(head->left, x);
	}

	if (x > head->x) {
		if (head->right == NULL) {
			head->right = create_new_node(x);
			return;
		}
		return add_node(head->right, x);
	}
}

void print_tree(struct tree *head) {
	if (head == NULL) {
		return;
	}

	print_tree(head->left);
	printf("%d ", head->x);
	print_tree(head->right);
}

int main(void) {
	struct tree *head = create_new_node(5);
	add_node(head, 3);
	add_node(head, 7);

	struct tree *head1 = create_new_node(5);
	add_node(head1, 6);
	add_node(head1, 7);
	add_node(head1, 1);
	add_node(head1, 6);
	add_node(head1, 10);

	return 0;
}
	*/

	return 0;
}



////////list-sorts.c///////////////////////////
#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	struct Node* next;
};

void print_list(struct Node* head) {
	while (head) {
		printf("%d ", head->value);
		head = head->next;
	}
}

struct Node* create_new_node(int value) {
	struct Node* new_node = (struct Node*)calloc(1, sizeof(struct Node));
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}

void bubble_sort (struct Node* head, int len) {
	for (int i = 0; i < len; ++i) {
		struct Node*cur = head;
		while (cur->next) {
			int v1 = cur->value;
			int v2 = cur->next->value;
			if (v1 > v2) {
				cur->next->value = v1;
				cur->value = v2;
			}
			cur = cur->next;
		}

	}
}

struct Node* merge_sorted_lists(struct Node * head1, struct Node * head2) {
	//if NULL...
	struct Node* head = (head1->value <= head2->value) ? head1 : head2;
	struct Node* ans = head;
	if (head == head1) {
		head1 = head1->next;
	} else {
		head2 = head2->next;
	}

	while (head1 && head2) {

		int v1 = head1->value;
		int v2 = head2->value;

		if (v1 <= v2) {
			head->next = head1;
			head1 = head1->next;
		} else {
			head->next = head2;
			head2 = head2->next;
		}

		head = head->next;
	}

	if (head1 == NULL) {
		head->next = head2;
	} else {
		head->next = head1;
	}

	return ans;
}

struct Node *merge(struct Node *head, int len) {
	if (len == 1) {
		return head;
	}
	int part_len = len / 2;

	struct Node *head1 = head;
	part_len--;

	while (part_len) {
		head = head->next;
		part_len--;
	}
	struct Node *head2 = head->next;
	head->next = NULL;

	return merge_sorted_lists(merge(head1, len / 2 ), merge(head2, len - len / 2));
}

void delete(struct Node *head) {
	struct Node *next;
	while (head) {
		next = head->next;

		free(head);
		head = next;
	}
}

int main(void) {
	struct Node* head = create_new_node(15);
	head->next = create_new_node(6);
	head->next->next = create_new_node(1);
	head->next->next->next = create_new_node(11);
	head->next->next->next->next = create_new_node(2);

	head = merge(head, 5);

	print_list(head);

	return 0;
}
    
