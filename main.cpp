#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <random>
#include <vector>
#include <stdexcept>
#include <unordered_set>

using namespace std;

template<typename KeyType, typename ValueType>
class Heap4
{
public:

    using KeyValueType = std::pair<const KeyType, ValueType>;

    vector<KeyType> v = {};

    bool empty() const noexcept;

    void insert(KeyType const & key, ValueType const & value)
    {

        this->v.push_back(key);
        this->sift_up(v.size()-1);
        //cout<<"przod: "<<v[0]<<endl;
    };

    void insert(KeyValueType const & key_value);

    KeyValueType const & peek() const noexcept;

    //KeyValueType pop() noexcept;

    size_t size() const noexcept;

    void pop()
    {
        if (!this->v.empty())
        {
            if (this->v.size() > 1) { std::swap(this->v.front(), this->v.back()); }

            this->v.pop_back();
            if (!this->v.empty()) { this->sift_down(0); }
        }
    }

    int child(int pos, int rank) const
    {
        return 2 * pos + rank + 1;
    }

    void sift_up(int pos)
    {
        while(pos>0)
        {
            KeyType parent;
            cout<<"rozwazam "<<v[pos]<<"  ";
            cout<<"size: "<<this->v.size();
            int pp = (pos-1)/4;
            cout<<"  parent pos : "<<pp<<"  ";
            parent = this->v[pp];
            cout<<"parent: "<<this->v[pp]<<endl;
            if(this->v[pp]>this->v[pos])
            {
                std::swap(this->v[pos],this->v[pp]);
                cout<<"swap "<<this->v[pp]<<" z "<<this->v[pos]<<endl;
            }
            pos=pp;
        }

    };

    void sift_down(int pos) {
        int best_pos = pos;

        for (int i = 0; i < 4; ++i)
        {
            int child_pos = this->child(pos, i);

            if (child_pos < this->v.size())
            {
                if (this->v[child_pos] < this->v[best_pos])
                {
                    best_pos = child_pos;
                }
            }
        }

        if (best_pos != pos)
        {
            std::swap(this->v[pos], this->v[best_pos]);
            this->sift_down(best_pos);
        }
    }
    void pt(int pos, int idt = 0)
    {
        if(pos<this->v.size()){

            this->pt(pos*4+4, idt+2);
            this->pt(pos*4+3, idt+2);
            for(int i = 0; i<=idt;i++)
            {
                cout<<"  ";
            }
            cout<<this->v[pos]<<endl<<endl;
            this->pt(pos*4+2, idt+2);
            this->pt(pos*4+1, idt+2);

        }
    }
    template<typename StreamType>
    void print(StreamType& stream) const
    {  for(int i = 0; i< this->v.size();i++)
            cout<<this->v[i]<<" ";
    };
};
int main()
{
    Heap4<int,int> heap;

    heap.insert(2,1);
    heap.insert(4,2);
    heap.insert(6,3);
    heap.insert(8,1);
    heap.insert(10,2);
    heap.insert(12,3);
    heap.insert(1,1);
    heap.pop();
    cout<<"print: \n"<<endl;
    heap.print(cout); cout<<endl;
    heap.pt(0);
    return 1;
}