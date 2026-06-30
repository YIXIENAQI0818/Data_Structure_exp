#include <iostream>
#include <cmath>
#include <string>
using namespace std;

using namespace std;
typedef struct {
    float x;
    float y;
    float z;
} Trip;

class Trip{
public:
    float x;
    float y;
    float z;

    //构造三元组
    Trip(float v1 , float v2 , float v3): x(v1) , y(v2) , z(v3) 
    {}  

    //销毁三元组
    ~Trip()
    {}

    //get函数
    void get(int i , float& e)
    {
        if(i < 1 || i > 3)
        {
            cout << "IndexError" << endl;
        }
        else
        {
            if(i == 1)
            {
                e = x;
            }
            else if(i == 2)
            {
                e = y;
            }
            else
            {
                e = z;
            }
        }
    }

    //put函数
    void put(int i , float e)
    {
        if(i < 1 || i > 3)
        {
            cout << "IndexError" << endl;
        }
        else
        {
            if(i == 1)
            {
                x = e;
            }
            else if(i == 2)
            {
                y = e;
            }
            else
            {
                z = e;
            }
        }
    }

    //判断是否升序
    int IsAscending()
    {
        if(x < y && y < z)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    //判断是否降序
    int IsDescending()
    {
        if(x > y && y > z)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    //找三元组中最大值
    float Max(float& e)
    {
        if(x > y && x > z)
        {
            e = x;
            return x;
        }
        else if(y > x && y > z)
        {
            e = y;
            return y;
        }
        else
        {
            e = z;
            return z;
        }
    }

    //找三元组中最小值
    float Min(float& e)
    {
        if(x < y && x < z)
        {
            e = x;
            return x;
        }
        else if(y < x && y < z)
        {
            e = y;
            return y;
        }
        else
        {
            e = z;
            return z;
        }
    }

    //实现向量的加法
    Trip operator+(const Trip& t) const
    {
        return Trip(x + t.x , y + t.y , z + t.z);
    }

    //实现向量的减法
    Trip operator-(const Trip& t) const
    {
        return Trip(x - t.x , y - t.y , z - t.z);
    }

    //实现向量的点乘
    float operator*(const Trip& t) const
    {
        return x * t.x + y * t.y + z * t.z;
    }

    //实现向量的叉乘
    Trip operator^(const Trip& t) const
    {
        return Trip(y * t.z - z * t.y , z * t.x - x * t.z , x * t.y - y * t.x)
    }
}



//以下是线性表及操作的尝试构建
class Data{
public:
    Trip data_triplet;
    Data* next;

    Data(Trip x): data_triplet(x) , next(nullptr) 
    {}
};


class Triplet {
private:
    Data* head; 

public:
    // InitList初始化三元组
    Triplet(): head(nullptr) 
    {}

    // DestroyList释放内存
    ~Triplet() 
    {
        Data* current = head;
        while (current != nullptr) {
            Data* temp = current;
            current = current->next;
            delete temp; // 释放当前节点
        }
    }

    // ClearList清空三元组
    void Triplet_clear() 
    {
        Data* current = head;
        while (current != nullptr) {
            Data* temp = current;
            current = current->next;
            delete temp; // 释放当前节点
        }
        head = nullptr; 
    }

    // ListEmpty判断三元组是否为空
    bool Triplet_empty() const
    {
        return head == nullptr;
    }

    // ListLength返回三元组的长度
    int Triplet_length() const
    {
        int length = 0l;
        Data* current = head;
        while (current != nullptr)
        {
            length++;
            current = current -> next;
        }
        return length;
    }

    // GetElem返回线性表中第i个三元组
    void Triplet_getElem(int i , Trip& element)
    {
        if(i < 1 || i > Triplet_length())
        {
            cout << "IndexError" << endl;
            return;
        }
        else
        {
            Data* current = head;
            while(i > 1)
            {
                current = current -> next;
                i--;
            }
            element = current -> data_triplet;
        }
    }

    // LocateElem返回线性表中第一个和给定三元组值相等的数据元素位置
    int Triplet_locateElem(Trip element)
    {
        Data* current = head;
        int count = 1;
        while(head != nullptr)
        {
            if((current -> data_triplet.x == element.x) && (current -> data_triplet.y == element.y) && (current -> data_triplet.z == element.z))
            {
                return count;
            }
            current = current -> next;
            count++;
        }
        return 0;
    }

    // PriorElem返回与给定三元组值相等的数据元素的前驱
    void Triplet_PriorElem(Trip element , Data* prior)
    {
        Data* current = head;
        Data* prior_node = current;
        while(current != nullptr)
        {
            if((current -> data_triplet.x == element.x) && (current -> data_triplet.y == element.y) && (current -> data_triplet.z == element.z))
            {
                prior = prior_node;
                return;
            }
            else
            {
                prior_node = current;
                current = current -> next;
            }
        }
    }

    // NextElem返回与给定三元组值相等的数据元素的后继
    void Triplet_NextElem(Trip element , Data* following)
    {
        Data* current = head;
        while(head != nullptr)
        {
            if((current -> data_triplet.x == element.x) && (current -> data_triplet.y == element.y) && (current -> data_triplet.z == element.z))
            {
                following = current -> next;
                return;
            }
            else
                current = current -> next;
        }
    }

    //ListInsert在线性表中第i个位置插入新的三元组
    void Triplet_insert(int i  , Trip element)
    {
        if(i < 1 || i > Triplet_length())
        {
            cout << "IndexError" << endl;
            return;
        }
        else
        {
            Data* current = head;
            while(i > 1)
            {
                current = current -> next;
                i--;
            }
            Data* new_node = new Data(element);
            new_node -> next = current -> next;
            current -> next = new_node;
        }
    }

    // ListDelete删除线性表中第i个位置的三元组
    void Triplet_delete(int i , Trip element)
    {
        if(i < 1 || i > Triplet_length())
        {
            cout << "IndexError" << endl;
            return;
        }
        else
        {
            Data* current = head;
            while(i > 1)
            {
                current = current -> next;
                i--;
            }
            element = current -> data_triplet;
            current -> next = current -> next -> next;
        }
    }

    // ListTraverse依次访问该线性表中所有三元组
    void Triplet_traverse()
    {
        Data* current = head;
        while(current != nullptr)
        {
            cout << "(" << current -> data_triplet.x << "," << current -> data_triplet.y << "," << current -> data_triplet.z << ")" << endl;
            current = current -> next;
        }
    }

    // ListGrowth在线性表末尾处添加新的三元组
    void Triplet_growth(Trip element)
    {
        Data* current = head;
        while(current -> next != nullptr)
        {
            current = current -> next;
        }
        else
        {
            Data* new_node = new Data(element);
            current -> next = new_node;
        }
    }

    // ListShrink删除线性表末尾处的三元组
    void Triplet_shrink()
    {
        Data* current = head;
        while(current -> next -> next != nullptr )
        {
            current = current -> next;
        }
        else
            current -> next = nullptr;
    }


    //设计并实现三元组的向量加法
    


};
