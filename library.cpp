#include <bits/stdc++.h>
#include "myDataStructures.hpp"
using namespace std;

int main(){
    Heap<int> h;
    h.insert(-1);
    cout<<h.top()<<' ';
    h.insert(0);
    cout<<h.isEmpty()<<'\n';
    cout<<h.top()<<' ';
    cout<<h.isEmpty()<<"\n\n";

    Stack<int>st;
    st.push(12);
    st.push(2);
    st.push(3);
    st.pop();
    cout<<st.top()<<' ';
    cout<<st.isEmpty()<<' ';
    st.pop();
    st.pop();
    cout<<st.isEmpty();

    cout<<"\n\n";

    Queue<int> q;
    q.push(12);
    q.push(22);
    cout<<q.front()<<' ';
    q.pop();
    cout<<q.front()<<' ';
    cout<<q.isEmpty()<<' ';
    q.pop();
    cout<<q.isEmpty();

    cout<<"\n\n";

    BinarySearchTree<int> abc;
    abc.insert(1);
    abc.insert(11);
    abc.insert(2);
    abc.insert(7);
    abc.insert(3);
    abc.insert(-1);
    abc.insert(-3);
    abc.insert(-2);
    abc.remove(1);
    cout<<'\n';
    abc.inorderPrint();
    cout<<'\n';
    abc.remove(7);
    abc.inorderPrint();

    RangeMinimumQuery<int, function<int(const int&, const int&)>> rmqMin([](const int& a, const int& b) ->int { return min(a, b); });
    RangeMinimumQuery<int, function<int(const int&, const int&)>> rmqMax([](const int& a, const int& b) ->int { return max(a, b); });
    RangeMinimumQuery<int, function<int(const int&, const int&)>> rmqLCM([](const int& a, const int& b) ->int { return (a / __gcd(a, b)) * b;});
    RangeMinimumQuery<int, function<int(const int&, const int&)>> rmqGCD([](const int& a, const int& b) -> int {return __gcd(a,b);});
    return 0;
}