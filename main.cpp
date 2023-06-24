#define WAIT false
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cin;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;
using std::to_string;
using std::stoi;
using std::ostream;


class Data
{
    public:
    char letter; // 1 буква
    int data; // 3 цифры
    string letters; // 2 буквы

    Data(){
        letter = ' ';
        data = 0;
        letters = "";
    }

    Data(string s){
        this->letter = s[0];
        this->data = std::stoi(s.substr(1, 3));
        this->letters = s.substr(4, 2);
    };

};

class Node 
{ 
    public:
    Data key;
    Node *left; 
    Node *right;
}; 

bool isEquel(char a1, int n1, string b1, char a2, int n2, string b2);
bool isLess(char a1, int n1, string b1, char a2, int n2, string b2);
bool isMore(char a1, int n1, string b1, char a2, int n2, string b2);

bool operator ==(const Data &d1, const Data &d2);
bool operator <(const Data &d1, const Data &d2);
bool operator >(const Data &d1, const Data &d2);

ostream& operator<< (ostream &out, const Data &key);

bool operator ==(const Data &d1, const Data &d2){
    
    bool res = isEquel(d1.letter, d1.data, d1.letters, d2.letter, d2.data, d2.letters);
    return res;
};

bool operator <(const Data &d1, const Data &d2){
    bool res = isLess(d1.letter, d1.data, d1.letters, d2.letter, d2.data, d2.letters);
    return res;
};

bool operator >(const Data &d1, const Data &d2){
    bool res = isMore(d1.letter, d1.data, d1.letters, d2.letter, d2.data, d2.letters);
    return res;
};

bool isEquel(char a1, int n1, string b1, char a2, int n2, string b2){

    if((a1 == a2) && (n1 == n2) && (b1 == b2))
        return true;
    else
        return false;
};

bool isLess(char a1, int n1, string b1, char a2, int n2, string b2){
    if((a1 < a2) && (n1 < n2) && (b1 < b2))
        return true;
    else
        if((a1 == a2) && (n1 == n2) && (b1 < b2))
            return true;
        else
            if((a1 == a2) && (n1 < n2))
                return true;
            else
                if(a1 < a2)
                    return true;
                else
                    return false;
};

bool isMore(char a1, int n1, string b1, char a2, int n2, string b2){
    if((a1 > a2) && (n1 > n2) && (b1 > b2))
        return true;
    else
        if((a1 == a2) && (n1 == n2) && (b1 > b2))
            return true;
        else
            if((a1 == a2) && (n1 > n2))
                return true;
            else
                if(a1 > a2)
                    return true;
                else
                    return false;
};

ostream& operator<< (ostream &out, const Data &key){
    // Вывод незначащих нулей - заполнить отсутствующие цифры в числе
    // Перегрузка вывода ключа
    if(key.data < 10)
        out << key.letter << "00" <<  key.data << key.letters;
    else
        if(key.data < 100)
            out << key.letter << "0" <<  key.data << key.letters;
                else
                    out << key.letter << "" <<  key.data << key.letters;
    return out;
};


// Функция для получения максимального
// из двух целых чисел
int max(int a, int b); 
int height(Node *N);

Node* newNode(Data key);

Node* insert(Node* node, Data key);

Node* deleteNode(Node* root, Data key);

Node * maxValueNode(Node* node);

void preOrder(Node *root);
void print(Node *node, int level);
void print(Data *root, bool preOrder);

// Функция для получения максимального
// из двух целых чисел
int max(int a, int b){ 
    return (a > b)? a : b; 
} 

/* функция, которая выделяет
новый узел с заданным ключом и
указателями nullptr влево и вправо. */
Node* newNode(Data key){
    Node* node = new Node();
    node->key = key;

    node->left = nullptr;
    node->right = nullptr;
    // добавление листьев
    
    return(node);
}

Node *search(Node *node, Data key){

    if (node == nullptr)
        return node;
    if (key < node->key)
        return search(node->left, key);
    else if (key > node->key)
        return search(node->right, key);    
    else // допускаются повторяющиеся ключи
        return node;
}

// функция добавления узла в дерево
Node* insert(Node* node, Data key){ 
    if (node == nullptr)
        return newNode(key);
    
    if(node->key == key)
        node->right = insert(node->right, key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);    
    else 
        return node;

    return node; 
}

// Рекурсивная функция для удаления узла 
// с заданным ключом из поддерева с 
// заданный корень. Он возвращает корень
// измененного поддерева.
Node* deleteNode(Node *root, Data key){ 
    //выполняется удаление листа
    if (root == NULL)
        return root;

    // Если ключ, подлежащий удалению, меньше 
    // чем ключ корня, то он лежит
    // в левом поддереве
    if (key <  root->key)
        root->left = deleteNode(root->left, key); 

    // Если ключ, подлежащий удалению, больше 
    // чем ключ корня, то он лежит 
    // в правом поддереве
    else if(key > root->key)
        root->right = deleteNode(root->right, key); 

    // если ключ совпадает с ключом root, то 
     // Это узел, подлежащий удалению
    else
    {  
        // узел только с одним элементом или без элемента 
        if((root->left == NULL) ||
            (root->right == NULL)){
            Node *temp = root->left ? 
                        root->left : 
                        root->right; 

            // нет ключа
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else // случай если ребенок 1
            *root = *temp; // удаляем ребенка
            free(temp);
        } 
        else
        { 
            // узел с двумя элементами: Получить порядок 
             // преемник (наибольший в левом поддереве)
            Node* temp = maxValueNode(root->left); 

            // копирует ключ 
             //для этого узла
            root->key = temp->key;

            // удаляет root
            root->left = deleteNode(root->left, temp->key);
        } 
    } 

//если в дереве был один узел то возвращаемся

    return root; 
} 

/* Учитывая непустое двоичное дерево поиска,
верните узел с максимальным значением ключа
, найденным в этом дереве.  */
Node * maxValueNode(Node* node) { 
    Node* current = node; 

    //цикл для углубления по дереву
    while (current->right != nullptr) 
        current = current->right; 
    return current; 
}

// Служебная функция для печати 
// прямого обхода дерева. 
void preOrder(Node *root)
{
    if(root != nullptr)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Служебная функция для печати 
// обратного обхода дерева. 
void postOrder(Node* root) 
{
    if (root != nullptr)
    {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
}

Node* DeleteAll(Node *node){
    while(node)
        node = deleteNode(node, node->key);
    return node;
}

void print(Node *node, int level = 0)
{
    if(node){
        print(node->right, level + 1);

        for(int i = 0; i < level; i++) cout<<"  ";

        cout << node->key << endl;
        // cout << endl;

        print(node->left, level + 1);
    }

    if(level == 0){
        cout << endl;
        if(WAIT)
            std::cin.get();
    }
        
    
}

string randKey() {//рандомайзер
    char letter_1 = (int)'A' + rand() % ('Z' - 'A' + 1);
    int data = rand() % 1000;
    char letter_2 = (int)'A' + rand() % ('Z' - 'A' + 1);
    char letter_3 = (int)'A' + rand() % ('Z' - 'A' + 1);

    string data_ = "";
    if (data < 10)
        data_ = "00" + to_string(data);
    else
        if (data < 100)
            data_ = "0" + to_string(data);
        else
            data_ = to_string(data);

    string out = letter_1 + data_ + letter_2 + letter_3;
    return out;
}


int main()
{ 
    Node *root = nullptr;

    setlocale(0, "");

  //  vector <string> v;
  //      for (int i = 0; i < 5; i++)
    //        v.push_back(randKey());
      //  for (auto i : v)
        //    root = insert(root, Data(i));
    for(int i = 103; i < 109; i++)
         root = insert(root, Data("A" + to_string(i)+"AA"));
         print(root);
     root = insert(root, Data("B006BB"));
     print(root);
     cout<< "удаление элемента(элементов): "<<endl;
        for(int i = 103; i <= 118; i++)
        root = deleteNode(root, Data("A" + to_string(i) + "AA"));
         print(root);
         
     root = DeleteAll(root);

    print(root);
    preOrder(root);
    cout << endl;
    postOrder(root);
    return 0;
}


