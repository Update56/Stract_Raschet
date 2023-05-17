#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <iomanip>

using namespace std;

ifstream fin("input.dat");   //открываем файлы 
ofstream fout("output.dat"); //для ввода и вывода данных

struct Node //структура узла дерева
{
    int key;
    Node* left;
    Node* right;
};
Node* newNode(int key) //функция для создания нового узла
{
    Node* node = new Node;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insert(Node* node, int key) //функция для добавления узла в дерево
{
    if (node == NULL) //если дерево пустое, создаем новый узел
        return newNode(key);
    if (key < node->key) //иначе идем влево или вправо в зависимости от значения ключа
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node; //возвращаем измененное дерево
}

Node* deleteNode(Node* root, int key) //функция для удаления узла из дерева
{
    if (root == NULL) //базовый случай
        return root;
    if (root->key < key)  //если значение ключа узла меньше искомого ключа, идем вправо
        root->right = deleteNode(root->right, key);
    else if (root->key > key) //если значение ключа узла больше искомого ключа, идем влево
        root->left = deleteNode(root->left, key);
    else //если нашли узел с искомым ключом
    {
        if (root->left == NULL) //если у узла нет потомков, просто удаляем его
        {
            Node* temp = root->right;
            delete(root);
            return temp;
        }
        else if (root->right == NULL) 
        {
            Node* temp = root->left;
            delete(root);
            return temp;
        }
        Node* temp = root->right; //если у узла есть два потомка, находим наименьший элемент в правом поддереве
        while (temp->left != NULL)
            temp = temp->left;        
        root->key = temp->key; //меняем ключ корневого узла на ключ минимального элемента в правом поддереве
        root->right = deleteNode(root->right, temp->key); //удаляем минимальный элемент в правом поддереве
    }
    return root;
}

//функция для вывода дерева в виде рисунка
void printTree(Node const* node, string const& rpref = "", string const& cpref = "", string const& lpref = "") {
    if (!node) 
        return;
    if (node->right)
        printTree(node->right, rpref + "  ", rpref + "/", rpref + "| ");
    cout << cpref << to_string(node->key) << endl;
    fout << cpref << to_string(node->key) << endl;
    if (node->left)
        printTree(node->left, lpref + "| ", lpref + "\\", lpref + "  ");
}

int main() 
{
    system("Color F0");
    setlocale(LC_ALL, "Russian");  
    int num_vert;    //читаем исходные 
    fin >> num_vert; //данные из файла
    Node* root = NULL; //создаем корневой узел дерева   
    for (int i = 0; i < num_vert; i++) //строим исходное дерево с помощью цикла
    {
        int key;
        fin >> key;
        root = insert(root, key);
    }

    cout << "Исходное дерево:\n"; //выводим исходное дерево 
    fout << "Исходное дерево:\n"; //в виде рисунка
    printTree(root);

    int key;    //читаем значение ключа 
    fin >> key; //удаляемой вершины из файла
    root = deleteNode(root, key); //удаляем вершину с заданным ключом из дерева

    cout << "\nДерево после удаления вершины с ключом " << key << ":\n"; //выводим результат 
    fout << "\nДерево после удаления вершины с ключом " << key << ":\n"; //в виде рисунка
    printTree(root);

    fin.close();  //закрываем 
    fout.close(); //файлы
    return 0;
}