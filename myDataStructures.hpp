#include<bits/stdc++.h>
using namespace std;

/*                      Min Heap                                  */
/* poate fi folosit si ca max heap adaugand numerele in heap cu - */
template<typename T> class Heap{
private:
    vector<T> heap;
    unsigned int len;
    void heapUp();
    void heapDown();
public:
    Heap():len(0){ heap.emplace_back(T());}
    void insert(const T n);
    T top();
    bool isEmpty(){ return !(this->len);}
};

template<typename T> void Heap<T>::heapUp(){
    int n = this->len;
    while(heap[n]<heap[n/2] && n>1){
        swap(heap[n],heap[n/2]);
        n /= 2;
    }
}

template<typename T> void Heap<T>::heapDown() {
    int i=1;
    while(true){
        int son = 0;
        if((2*i) <= this->len){
            son = 2*i;
            if(son+1 <= this->len && heap[son+1] < heap[son])
                son += 1;
        }
        if(son && heap[son] < heap[i]){
            swap(heap[son],heap[i]),i=son;
        }
        else
            break;
    }
}

template<typename T> void Heap<T>::insert(const T n){
    this->heap.emplace_back(n);
    this->len+=1;
    heapUp();
}

template<typename T> T Heap<T>::top() {
    try {
        if (heap.size()>=2) {
            T rez = heap[1];
            swap(heap[1], heap[this->len]);
            heap.pop_back();
            this->len -= 1;
            heapDown();
            return rez;
        }
        throw runtime_error("Heap is empty");

    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}



/*                        Stack                       */
template<typename T>  class Stack{
private:
    unsigned int len;
    struct nod{
        T value;
        nod* next;
        nod(): next(NULL){}
    }*vf;
public:
    Stack():vf(NULL),len(0){}
    void push(T n);
    void pop();
    T top();
    bool isEmpty(){ return !(this->len);}
};

template<typename T> void Stack<T>::push(T n) {
    if(this->vf == NULL)
        this->vf = new nod,this->vf->value = n;
    else{
        nod *p= new nod;
        p->value = n,p->next = this->vf,this->vf = p;
    }
    this->len += 1;
}

template<typename T> T Stack<T>::top(){
    return this->vf->value;
}

template<typename T> void Stack<T>::pop(){
    nod *aux = this->vf;
    this->vf = this->vf->next;
    delete aux;
    this->len -= 1;
}



/*                   Queue                         */
template<typename T> class Queue{
private:
    struct nod{
        T value;
        nod* next;
        nod():next(NULL){}
    }*fr,*bk;
    unsigned int len;
public:
    Queue():fr(NULL),bk(NULL),len(0){}
    void push(T n);
    void pop();
    T front();
    bool isEmpty(){ return !(this->len);}
};

template<typename T> void Queue<T>::push(T n){
    if(this->fr==NULL and this->bk==NULL){
        this->fr = new nod;
        this->fr->value = n , this->bk=this->fr;
    }
    else{
        nod* p=new nod;
        p->value = n , this->bk->next=p , this->bk=p;
    }
    this->len -= 1;
}

template<typename T> T Queue<T>::front() {
    return this->fr->value;
}

template<typename T> void Queue<T>::pop(){
    nod *aux = this->fr;
    this->fr = this->fr->next;
    delete aux;
    this->len -= 1;
}



/*            Binary search tree              */

template<typename T> class BinarySearchTree {
private:
    struct nod {
        T value;
        nod* left;
        nod* right;
        nod() : left(NULL), right(NULL) {}
    }*root;

    nod* inorderSuccesor(nod* nodc);
    void _insert(T n, nod*& nodc);
    bool _search(T n, nod* nodc);
    void _delete(T n, nod*& nodc);
    void _inorderPrint(nod* root);

public:
    BinarySearchTree() : root(NULL) {}
    void insert(T n);
    bool search(T n);
    void remove(T n);
    void inorderPrint();
};

template<typename T> typename BinarySearchTree<T>::nod* BinarySearchTree<T>::inorderSuccesor(nod* nodc) {
    while (nodc->left != NULL) {
        nodc = nodc->left;
    }
    return nodc;
}

template<typename T> void BinarySearchTree<T>::_insert(T n, BinarySearchTree::nod*& nodC) {
    if (nodC == NULL) {
        nodC = new nod;
        nodC->value = n;
    } else {
        if (nodC->value > n)
            _insert(n, nodC->left);
        else
            _insert(n, nodC->right);
    }
}

template<typename T> bool BinarySearchTree<T>::_search(T n, nod* nodc) {
    if (nodc == NULL)
        return false;
    else {
        if (nodc->value == n)
            return true;
        else {
            if (nodc->value > n)
                return _search(n, nodc->left);
            else
                return _search(n, nodc->right);
        }
    }
}

template<typename T> void BinarySearchTree<T>::_delete(T n, BinarySearchTree::nod*& nodc) {
    if (nodc == NULL) {
        return; // Dacă nodul este NULL, nu facem nimic
    }

    if (nodc->value > n) {
        // Dacă valoarea nodului este mai mare decât n, căutăm în stânga
        _delete(n, nodc->left);
    } else if (nodc->value < n) {
        // Dacă valoarea nodului este mai mică decât n, căutăm în dreapta
        _delete(n, nodc->right);
    } else {
        // Am găsit nodul de șters
        if (nodc->left == NULL && nodc->right == NULL) {
            // Nodul este frunză
            delete nodc;
            nodc = NULL;
        } else if (nodc->left == NULL) {
            // Nodul are doar copilul drept
            nod* aux = nodc;
            nodc = nodc->right;
            delete aux;
        } else if (nodc->right == NULL) {
            // Nodul are doar copilul stâng
            nod* aux = nodc;
            nodc = nodc->left;
            delete aux;
        } else {
            // Nodul are ambii copii
            nod* succesor = inorderSuccesor(nodc->right);
            nodc->value = succesor->value;
            _delete(succesor->value, nodc->right);
        }
    }
}

template<typename T> void BinarySearchTree<T>::_inorderPrint(nod* nodc) {
    if (nodc != NULL) {
        _inorderPrint(nodc->left);
        cout << nodc->value << " ";
        _inorderPrint(nodc->right);
    }
}

template<typename T> void BinarySearchTree<T>::insert(T n) {
    _insert(n, this->root);
}

template<typename T> bool BinarySearchTree<T>::search(T n) {
    return _search(n, this->root);
}

template<typename T> void BinarySearchTree<T>::remove(T n) {
    _delete(n, this->root);
}

template<typename T> void BinarySearchTree<T>::inorderPrint() {
    _inorderPrint(this->root);
}


/*                      Range minimum query                    */

template<typename T, typename F = function<T(const T&, const T&)>>
class RangeMinimumQuery {
private:
    unsigned int len;
    vector<vector<T>> rmq; // vom avea min din secventa ce incepe pe poz i si lungime 2^p
    vector<int> exp; // exponentul celei mai mari puteri de 2 mai mică sau egală cu i
    F func; // Funcția de reducere (implicit std::gcd)
    void constructMatrix();

public:
    // Constructor implicit folosind std::gcd
    RangeMinimumQuery(F f): len(0), func(f) {}

    template<typename U, typename G> friend istream& operator>>(istream& in, RangeMinimumQuery<U, G>& rmqObj);
    T idempotentQuery(int x, int y);
};

template<typename T, typename F>
istream& operator>>(istream& in, RangeMinimumQuery<T, F>& rmqObj) {
    in >> rmqObj.len;

    int rows = static_cast<int>(ceil(log(rmqObj.len + 1) / log(2))) + 1;
    rmqObj.rmq.resize(rows);

    for (auto& row : rmqObj.rmq)
        row.resize(rmqObj.len + 1);

    for (unsigned int i = 1; i <= rmqObj.len; ++i)
        in >> rmqObj.rmq[0][i];

    rmqObj.exp.resize(rmqObj.len + 1);

    rmqObj.constructMatrix();

    return in;
}

template<typename T, typename F>
void RangeMinimumQuery<T, F>::constructMatrix() {
    int i, j, poz;
    for (i = 1; (1 << i) <= this->len; i += 1) {
        for (j = 1; j + (1 << i) - 1 <= this->len; j += 1) {
            this->rmq[i][j] = func(this->rmq[i - 1][j], this->rmq[i - 1][j + (1 << (i - 1))]);
        }
    }

    int e = 0;
    this->exp[1] = 0;
    for (i = 2; i <= this->len; i += 1) {
        if ((1 << (e + 1)) <= i)
            this->exp[i] = e + 1, e += 1;
        else
            this->exp[i] = e;
    }
}

template<typename T, typename F>
T RangeMinimumQuery<T, F>::idempotentQuery(int x, int y) {
    int lin, sar;
    lin = this->exp[y - x + 1];
    sar = (1 << lin);
    return func(this->rmq[lin][x], this->rmq[lin][y - sar + 1]);
}