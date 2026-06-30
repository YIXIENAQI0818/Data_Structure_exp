#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>
#include <iomanip>
#include <chrono>

using namespace std;

#define MAX_FLGHT 3000

typedef struct 
{
    int Flight_id;//航班ID
    int Departure_date;//启航日期
    bool Flight_type;//航班类型
    string Flight_no;//航班编号
    int Departure_airport;//启航机场ID
    int Arrival_airport;//抵达机场ID
    float Departure_time;//启航时间
    float Arrival_time;//抵达时间
    int Airplane_id;//飞机ID
    int Airplane_model;//飞机机型
    int Air_fares;//基础费用
    int Peak_rates;//旺季价格
    int Off_rates;//淡季价格
}Flight;

class Flight_node
{
    public:
        Flight flight_node_data;
        Flight_node* next;
        Flight_node* prev;

        Flight_node(): flight_node_data(), next(nullptr), prev(nullptr)
        {}
        Flight_node(Flight x): flight_node_data(x), next(nullptr), prev(nullptr) 
        {}
};

class Data_List
{
    private:
        Flight_node* head;//头指针
        Flight_node* tail;//尾指针
        int size;//链表长度

    public:
        
        //初始化链表
        Data_List() : head(nullptr), tail(nullptr), size(0)
        {}

        //销毁链表释放内存
        ~Data_List()
        {
            while(head != nullptr)
            {
                Flight_node* temp = head;
                head = head->next;
                delete temp;
                
            }    
            tail = nullptr;
        }

        //清空链表
        void clear_list()
        {
            Flight_node* current = head;
            while (current != nullptr)
            {
                Flight_node* temp = current;
                current = current->next; 
                delete temp;             
            }

            head = nullptr;
            tail = nullptr;
            size = 0;
        }

        //检查链表是否为空
        bool List_Empty()
        {
            return head == nullptr;
        }

        //添加节点
        void add(Flight x)
        {
            Flight_node* new_node = new Flight_node(x);
            if(head == nullptr)
            {
                head = new_node;//如果链表为空，头尾指针指向新节点
                tail = new_node;
            }
            else
            {
                tail->next = new_node;//如果链表不为空，尾节点的next指向新节点  
                new_node->prev = tail;
                tail = new_node;
            }
            size++;
        }

        //得到头结点  
        Flight_node* get_head()
        {
            return head;
        }        

        //数据初始化1
        void Initialize_Data_List()
        {
            //初始计时
            auto start = chrono::steady_clock::now();

            Flight current_flight;
            string line;

            //读取文件
            ifstream file("Flight_Data2024.csv");
            if(!file.is_open())
            {
                cout << "File not found." << endl;
                return;
            }

            //读取第一行
            getline(file, line);

            //读取数据
            while(getline(file, line))
            {
                stringstream ss(line);

                string str;
                getline(ss , str , ',');
                current_flight.Flight_id = stoi(str);

                getline(ss , str , ',');
                current_flight.Departure_date = stoi(str);

                getline(ss , str , ',');
                if(str == "Intl")
                    current_flight.Flight_type = true;
                else
                    current_flight.Flight_type = false;

                getline(ss , str , ',');
                current_flight.Flight_no = str;

                getline(ss , str , ',');
                current_flight.Departure_airport = stoi(str);

                getline(ss , str , ',');
                current_flight.Arrival_airport = stoi(str);

                getline(ss , str , ',');
                current_flight.Departure_time = stof(str);

                getline(ss , str , ',');
                current_flight.Arrival_time = stof(str);

                getline(ss , str , ',');
                current_flight.Airplane_id = stoi(str);

                getline(ss , str , ',');
                current_flight.Airplane_model = stoi(str);

                getline(ss , str , ',');
                current_flight.Air_fares = stoi(str);

                getline(ss , str , ',');
                current_flight.Peak_rates = stoi(str);

                getline(ss , str , ',');
                current_flight.Off_rates = stoi(str);

                this -> add(current_flight);
            }

            file.close();

            //结束计时
            auto end = chrono::steady_clock::now();

            //计算时间差
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

            
            cout << "Data has been initialized. The time taken for this operation: " << duration << " milliseconds." << endl;

            //初始化时就进行一次排序，避免逆民
            this -> Sort_Data_List();

        }

        //数据排序2
        void Sort_Data_List()
        {
            //初始计时
            auto start = chrono::steady_clock::now();

            //头尾为空或只有一个节点时，无需排序
            if(head == nullptr || head -> next == nullptr)
                return;

            //对链表的冒泡排序算法
            bool swapped = true;
            Flight_node* current = head;
            Flight_node* last_node = nullptr;

            while(swapped)
            {
                swapped = false;
                current = head;

                while(current -> next != last_node)
                {
                    if(current -> flight_node_data.Departure_airport < current -> next -> flight_node_data.Departure_airport)
                    {
                        swap(current -> flight_node_data , current -> next -> flight_node_data);
                        swapped = true;
                    }

                    else if(current -> flight_node_data.Departure_airport == current -> next -> flight_node_data.Departure_airport
                            && current -> flight_node_data.Arrival_airport < current -> next -> flight_node_data.Arrival_airport)
                    {
                        swap(current -> flight_node_data , current -> next -> flight_node_data);
                        swapped = true;
                    }

                    else if(current -> flight_node_data.Departure_airport == current -> next -> flight_node_data.Departure_airport
                            && current -> flight_node_data.Arrival_airport == current -> next -> flight_node_data.Arrival_airport)
                    {
                        float current_duration = current -> flight_node_data.Arrival_time - current -> flight_node_data.Departure_time;
                        float next_duration = current -> next -> flight_node_data.Arrival_time - current -> next -> flight_node_data.Departure_time;
                        if(current_duration > next_duration)
                        {
                            swap(current -> flight_node_data , current -> next -> flight_node_data);
                            swapped = true;
                        }
                    }
                    current = current -> next;
                }
                last_node = current;
            }

            //尾部计时
            auto end = chrono::steady_clock::now();

            //计算时间差
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

            cout << "Data has been sorted. The time taken for this operation: " << duration << " miliseconds." << endl;
        }

        //数据查询3.1,输出所有基础费用为素数的航班ID
        void Search_Date_List1()
        {
            //初始计时
            auto start = chrono::steady_clock::now();

            Flight_node* current = head;
            int count = 0;
            while(current != nullptr)
            {
                if(current -> flight_node_data.Air_fares % 2 == 1)
                {
                    count++;
                    cout << "The flight ID of the No." << count << " flight with a base fare that is a prime number is " << current -> flight_node_data.Flight_no << endl;
                }
                current = current -> next;
            }

            //尾部计时
            auto end = chrono::steady_clock::now();

            //计算时间差
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

            cout << "Data has been searched. The time taken for this operation: " << duration << " miliseconds." << endl;

        }

        //数据查询3.2
        void Search_Date_List2()
        {

            cout << "Please enter the departure airport ID and the arrival airport ID (e.g.34,50):" << endl;
            int departure_airport , arrival_airport;
            char comma;
            string choice;
            int count = 0;

            //检查输入合法性
            while(true)
            {
                cin >> departure_airport >> comma >> arrival_airport;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max() , '\n');
                    cout << "Invalid input , please enter again." << endl;
                }
                else
                {
                    cout << "Your entered departure airport ID is " << departure_airport << endl;
                    cout << "Your entered arrival airport ID is " << arrival_airport << endl;
                    cout << "YES or NO?" << endl;
                    cin >> choice;

                    if(choice == "YES" || choice == "yes")
                    {
                        break;
                    }
                    else if(choice == "NO" || choice == "no")
                    {
                        cout << "Please enter the departure airport ID and the arrival airport ID again(e.g.34,88):" << endl;
                    }
                    else
                    {
                        cout << "Invalid input, Please enter the departure airport ID and the arrival airport ID again(e.g.34,88):" << endl;
                    }
                }    
            }
            cout << setfill('-') << setw(90) << "-" << setfill(' ') << endl;

            //初始计时
            auto start = chrono::steady_clock::now();

            Flight_node* current = head;
            int min_air_fares = 114514;
            int min_peak_rates = 114514;
            int min_off_rates = 114514;

            //遍历链表分别求三列的最小值
            while(current != nullptr)
            {
                if(current -> flight_node_data.Departure_airport == departure_airport && current -> flight_node_data.Arrival_airport == arrival_airport)
                {
                    if(current -> flight_node_data.Air_fares < min_air_fares)
                        min_air_fares = current -> flight_node_data.Air_fares;

                    if(current -> flight_node_data.Peak_rates < min_peak_rates)
                        min_peak_rates = current -> flight_node_data.Peak_rates;

                    if(current -> flight_node_data.Off_rates < min_off_rates)
                        min_off_rates = current -> flight_node_data.Off_rates;  
                }
                current = current -> next;
            }

            //再次遍历链表，找到满足鞍点的航班ID
            current = head;
            while(current != nullptr)
            {
                if(current -> flight_node_data.Departure_airport == departure_airport && current -> flight_node_data.Arrival_airport == arrival_airport)
                {
                    if(current -> flight_node_data.Air_fares == min_air_fares
                    && current -> flight_node_data.Air_fares > current -> flight_node_data.Peak_rates
                    && current -> flight_node_data.Air_fares > current -> flight_node_data.Off_rates)
                    {
                        count++;
                        cout << "The flight ID of saddle point " << count << " based on Air_fares is: " << current -> flight_node_data.Flight_id << endl;
                    }

                    if(current -> flight_node_data.Peak_rates == min_peak_rates
                    && current -> flight_node_data.Peak_rates > current -> flight_node_data.Air_fares
                    && current -> flight_node_data.Peak_rates > current -> flight_node_data.Off_rates
                    )
                    {
                        count++;
                        cout << "The flight ID of saddle point " << count << " based on Peak_rates is: " << current -> flight_node_data.Flight_id << endl;
                    }

                    if(current -> flight_node_data.Off_rates == min_off_rates
                    && current -> flight_node_data.Off_rates > current -> flight_node_data.Air_fares
                    && current -> flight_node_data.Off_rates > current -> flight_node_data.Peak_rates
                    )
                    {
                        count++;
                        cout << "The flight ID of saddle point " << count << " based on Off_rates is: " << current -> flight_node_data.Flight_id << endl;
                    }
                }
                current = current -> next;
            }

            //如果没找到鞍点，输出提示信息
            if(count == 0)
                cout << "No saddle point found." << endl;

            //尾部计时
            auto end = chrono::steady_clock::now();

            //计算时间差
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

            cout << "Data has been searched. The time taken for this operation: " << duration << " miliseconds." << endl;


        }

        //数据查询3.3
        void Search_Date_List3(Data_List& list2)
        {
            cout << "Please Enter the Airplane ID(e.g. 40):" << endl;
            int airplane_id;

            while(true)
            {
                cin >> airplane_id;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max() , '\n');
                    cout << "Invalid input , please enter again(e.g. 40):" << endl;
                }
                else if(airplane_id < 1 || airplane_id > 142)
                    cout << "Invalid airplane ID , please enter again(e.g. 40):" << endl;
                else
                    break;
                
            }

            //初始计时
            auto start = chrono::steady_clock::now();

            Flight_node* current = head;
            Flight current_flight_data;
            while(current != nullptr)
            {
                if(current -> flight_node_data.Airplane_id == airplane_id)
                {
                    current_flight_data = current -> flight_node_data;
                    list2.add(current_flight_data);
                }
                current = current -> next;
            }


            current = list2.get_head();
            Flight_node* last_node = nullptr;
            if(current == nullptr || current -> next == nullptr)
                return;

            bool swapped = true;

            while(swapped)
            {
                current = list2.get_head();
                swapped = false;
                while(current -> next != last_node)
                {
                    if(current -> flight_node_data.Departure_time > current -> next -> flight_node_data.Departure_time)
                    {
                        swap(current -> flight_node_data , current -> next -> flight_node_data);
                        swapped = true;
                    }
                    current = current -> next;
                }
                last_node = current;
            }

            cout << left << setw(15) << "Flight ID"
            << setw(15) << "Departure date" 
            << setw(15) << "Departure airport" 
            << setw(15) << "Arrival airport" 
            << setw(15) << "Departure Time" 
            << setw(15) << "Arrival Time" << endl;

            cout << setfill('-') << setw(90) << "-" << setfill(' ') << endl;

            current = list2.get_head();
            while(current != nullptr)
            {
                cout << left << setw(15) << current -> flight_node_data.Flight_id
                << setw(15) << current -> flight_node_data.Departure_date 
                << setw(15) << current -> flight_node_data.Departure_airport
                << setw(15) << current -> flight_node_data.Arrival_airport 
                << setw(15) << current -> flight_node_data.Departure_time 
                << setw(15) << current -> flight_node_data.Arrival_time << endl;
                current = current -> next;
            }

            cout << setfill('-') << setw(90) << "-" << setfill(' ') << endl;


            //尾部计时
            auto end = chrono::steady_clock::now();

            //计算时间差
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

            cout << "Data has been searched. The time taken for this operation: " << duration << " miliseconds." << endl;
        }

        //新链表制造4.1
        void Delete_Airplane_model(Data_List& data_list3)
        {
            cout << "Please enter the airplane model you want to delete(e.g. 4):" << endl;
            int airplane_model;

            //检查输入合法性
            while(true)
            {
                cin >> airplane_model;
                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a valid airplane model(e.g. 4):" << endl;
                }
                else if(airplane_model < 1 || airplane_model > 4)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Only four types of airplane models are available: 1, 2, 3, and 4. Please select one and enter it(e.g. 4):" << endl;
                }
                else
                    break;
            }


            //初始计时
            auto start = chrono::steady_clock::now();

            //遍历链表，将选定的机型的航班信息从原链表中删除，并加入到新链表中
            Flight_node* current = head;
            while(current != nullptr)
            {
                if(current -> flight_node_data.Airplane_model == airplane_model)
                {
                    //加入新链表
                    data_list3.add(current -> flight_node_data);
                    data_list3.size++;
                    cout << current -> flight_node_data.Flight_id << " has been added to the new list(data_list3)." << endl;

                    //分头结点，尾结点，中间节点分别考虑删除原链表中的节点
                    if(current == head)//头
                    {
                        head = current -> next;
                        if(head != nullptr)
                        {
                            head -> prev = nullptr;
                        }
                        else
                        {
                            tail = nullptr;
                        }
                    }
                    else if(current == tail)//尾
                    {
                        tail = current -> prev;
                        tail -> next = nullptr;
                    }
                    else //中间
                    {
                        current -> prev -> next = current -> next;
                        current -> next -> prev = current -> prev;
                    }
                    delete current;
                    this -> size--;
                }
                current = current -> next;  
            }
            

            //结束计时
            auto end = chrono::steady_clock::now();

            //计算时间差
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

            cout << "All flight information of airplane model " << airplane_model << " has been transferred from the original list to the new list. The time taken for this operation: " << duration << " miliseconds." << endl;

        }
};


int main()
{
    Data_List data_list;
    Data_List data_list2;
    Data_List data_list3;

    data_list.Initialize_Data_List();

    //操作菜单
    cout << setfill('-') << setw(90) << "-" << setfill(' ') << endl;
    cout << "menu:" << endl;
    cout << "1. Initialize Data List Again." << endl;
    cout << "2. Sort Data List Again." << endl;
    cout << "3.1 Query All Flight IDs with a Base Fare that is a Prime Number." << endl;
    cout << "3.2 Query the Flight ID of the Saddle Point" << endl;
    cout << "3.3 Query the Flight Schedule of an Airplane" << endl;
    cout << "4.1 Delete a Specific Airplane Model from the Original Data List and Add it to Another Data List." << endl;
    cout << "4.2 Sort the New Data list" << endl;
    cout << "4.3 Query All Flight IDs with a Base Fare that is a Prime Number in the New Data List" << endl;
    cout << "4.4 Query the Flight ID of the Saddle Point in the New Data List" << endl;
    cout << "5. Exit" << endl;
    cout << "Please enter your choice(e.g. 3.1):" << endl;
    double choice;

    //选择操作
    while(true)
    {
        cin >> choice ;
        cout << setfill('-') << setw(90) << "-" << setfill(' ') << endl;
        if(choice == 1)
        {
            data_list.clear_list();
            data_list.Initialize_Data_List();
        }
        else if(choice == 2)
        {
            data_list.Sort_Data_List();
        }
        else if(choice == 3.1)
        {
            data_list.Search_Date_List1();
        }
        else if(choice == 3.2)
        {
            data_list.Search_Date_List2();
        }
        else if(choice == 3.3)
        {
            data_list2.clear_list();
            data_list.Search_Date_List3(data_list2);
        }
        else if(choice == 4.1)
        {
            data_list3.clear_list();
            data_list.Delete_Airplane_model(data_list3);
        }
        else if(choice == 4.2)
        {
            if(!data_list3.List_Empty())
                data_list3.Sort_Data_List();
            else
                cout << "The new data list is empty, please perform operation 4.1 first." << endl;
        }
        else if(choice == 4.3)
        {
            if(!data_list3.List_Empty())
                data_list3.Search_Date_List1();
            else
                cout << "The new data list is empty, please perform operation 4.1 first." << endl;
        }
        else if(choice == 4.4)
        {
            if(!data_list3.List_Empty())
                data_list3.Search_Date_List2();
            else
                cout << "The new data list is empty, please perform operation 4.1 first." << endl;
        }
        else if(choice == 5)//退出程序操作
        {
            cout << "Thank you for using my program. Goodbye!" << endl;
            return 0;
        }
        else 
        {
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << setfill('-') << setw(90) << "-" << setfill(' ') << endl;  
        cout << "menu:" << endl;
        cout << "1. Initialize Data List Again." << endl;
        cout << "2. Sort Data List Again." << endl;
        cout << "3.1 Query All Flight IDs with a Base Fare that is a Prime Number." << endl;
        cout << "3.2 Query the Flight ID of the Saddle Point" << endl;
        cout << "3.3 Query the Flight Schedule of an Airplane" << endl;
        cout << "4.1 Delete a Specific Airplane Model from the Original Data List and Add it to Another Data List." << endl;
        cout << "4.2 Sort the New Data list" << endl;
        cout << "4.3 Query All Flight IDs with a Base Fare that is a Prime Number in the New Data List" << endl;
        cout << "4.4 Query the Flight ID of the Saddle Point in the New Data List" << endl;
        cout << "5. Exit" << endl;
        cout << "Please enter your next choice." << endl;
        
    }

}