#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <unordered_set>
#include <fstream>
#include <sstream>
using namespace std;

// 定义机场信息的结构体
struct Airport {
    int id;                // 机场 ID
    string fullName;       // 机场全名
    string country;        // 国家
    string province;       // 省份
    string name;           // 机场名称
};

typedef struct 
{
    int Flight_id;//航班ID
    tm Departure_date;//启航日期
    bool Flight_type;//航班类型
    int Flight_no;//航班编号
    int Departure_airport;//启航机场ID
    int Arrival_airport;//抵达机场ID
    tm Departure_time;//启航时间
    tm Arrival_time;//抵达时间
    int Airplane_id;//飞机ID
    int Airplane_model;//飞机机型
    int Air_fares;//基础费用
}Flight;

bool operator==(const Flight& lhs, const Flight& rhs) 
{
    // 比较所有成员变量
    return (lhs.Flight_id == rhs.Flight_id) &&
           (lhs.Departure_date.tm_year == rhs.Departure_date.tm_year &&
            lhs.Departure_date.tm_mon == rhs.Departure_date.tm_mon &&
            lhs.Departure_date.tm_mday == rhs.Departure_date.tm_mday) &&
           (lhs.Flight_type == rhs.Flight_type) &&
           (lhs.Flight_no == rhs.Flight_no) &&
           (lhs.Departure_airport == rhs.Departure_airport) &&
           (lhs.Arrival_airport == rhs.Arrival_airport) &&
           (lhs.Departure_time.tm_hour == rhs.Departure_time.tm_hour &&
            lhs.Departure_time.tm_min == rhs.Departure_time.tm_min &&
            lhs.Departure_time.tm_sec == rhs.Departure_time.tm_sec) &&
           (lhs.Arrival_time.tm_hour == rhs.Arrival_time.tm_hour &&
            lhs.Arrival_time.tm_min == rhs.Arrival_time.tm_min &&
            lhs.Arrival_time.tm_sec == rhs.Arrival_time.tm_sec) &&
           (lhs.Airplane_id == rhs.Airplane_id) &&
           (lhs.Airplane_model == rhs.Airplane_model) &&
           (lhs.Air_fares == rhs.Air_fares);
}

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

    public:
        
        //初始化链表
        Data_List() : head(nullptr), tail(nullptr)
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
        }

        //检查链表是否为空
        bool List_Empty()
        {
            return head == nullptr;
        }

        //添加节点
        void add(Flight_node* new_node)
        {

            if(head == nullptr)
            {
                head = new_node;
                tail = new_node;
            }
            else
            {
                tail -> next = new_node;
                new_node -> prev = tail;
                tail = new_node;
            }

        }

        //删除节点
        void delete_node(int Flight_id)
        {
            Flight_node* current = head;
            int flag = 1;
            while(current != nullptr)
            {
                if(current -> flight_node_data.Flight_id == Flight_id)
                {
                    if(current == head)
                    {
                        head = head->next;
                        if(head != nullptr)
                        {
                            head->prev = nullptr;
                        }
                    }
                    else if(current == tail)
                    {
                        tail = tail->prev;
                        if(tail != nullptr)
                        {
                            tail->next = nullptr;
                        }
                    }
                    else
                    {
                        current -> prev -> next = current -> next;
                        current -> next -> prev = current -> prev;
                    }
                    flag = 0;
                }
                current = current -> next;
            }
            if(flag == 1)
            {
                cout << "No such flight." << endl;
            }
        }

        //更改节点
        void modify(int Flight_id, Flight_node* new_node)
        {
            Flight_node* current = head;
            while(current != nullptr)
            {
                if(current -> flight_node_data.Flight_id == Flight_id)
                {
                    if(current == head)
                    {
                        new_node -> next = current -> next;
                        head = new_node;

                    }
                    else if(current == tail)
                    {
                        new_node -> prev = current -> prev;
                        current -> prev -> next = new_node;
                        tail = new_node;
                    }
                    else
                    {
                        new_node -> prev = current -> prev;
                        new_node -> next = current -> next;
                        current -> prev -> next = new_node;
                        current -> next -> prev = new_node;
                    }

                }
                current = current -> next;
            }
        }

        //得到头结点  
        Flight_node* get_head()
        {
            return head;
        }        

        //读取文件并初始化链表
        void Initialize_Data_List()
        {

            string line;
            string filename = "D:\\C\\Flight_3\\flight-data.csv";

            //读取文件
            ifstream file(filename);
            //ifstream file("Flight_Data2024.csv");
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
                Flight_node* current_flight = new Flight_node;
                stringstream ss(line);

                string str;
                getline(ss , str , ',');
                current_flight -> flight_node_data.Flight_id = stoi(str);

                getline(ss , str , '/');
                current_flight -> flight_node_data.Departure_date.tm_mon = stoi(str);

                getline(ss , str , '/');
                current_flight -> flight_node_data.Departure_date.tm_mday = stoi(str);

                getline(ss , str , ',');
                current_flight -> flight_node_data.Departure_date.tm_year = stoi(str);

                getline(ss , str , ',');
                if(str == "Intl")
                    current_flight -> flight_node_data.Flight_type = true;
                else
                    current_flight -> flight_node_data.Flight_type = false;

                getline(ss , str , ',');
                current_flight -> flight_node_data.Flight_no = stoi(str);

                getline(ss , str , ',');
                current_flight -> flight_node_data.Departure_airport = stoi(str);

                getline(ss , str , ',');
                current_flight -> flight_node_data.Arrival_airport = stoi(str);

                getline(ss , str , '/');
                current_flight -> flight_node_data.Departure_time.tm_mon = stoi(str);

                getline(ss , str , '/');
                current_flight -> flight_node_data.Departure_time.tm_mday = stoi(str);

                getline(ss , str , ' ');
                current_flight -> flight_node_data.Departure_time.tm_year = stoi(str);

                getline(ss , str , ':');
                current_flight -> flight_node_data.Departure_time.tm_hour = stoi(str);

                getline(ss , str , ',');
                current_flight -> flight_node_data.Departure_time.tm_min = stoi(str);

                getline(ss , str , '/');
                current_flight -> flight_node_data.Arrival_time.tm_mon = stoi(str);

                getline(ss , str , '/');
                current_flight -> flight_node_data.Arrival_time.tm_mday = stoi(str);

                getline(ss , str , ' ');
                current_flight -> flight_node_data.Arrival_time.tm_year = stoi(str);

                getline(ss , str , ':');
                current_flight -> flight_node_data.Arrival_time.tm_hour = stoi(str);

                getline(ss , str , ',');
                current_flight -> flight_node_data.Arrival_time.tm_min = stoi(str);

                getline(ss , str , ',');
                current_flight -> flight_node_data.Airplane_id = stoi(str);

                getline(ss , str , ',');
                current_flight -> flight_node_data.Airplane_model = stoi(str);

                getline(ss , str , ',');
                current_flight -> flight_node_data.Air_fares = stoi(str);

                this -> add(current_flight);
            }

            file.close();

        }

};

int calculate_minutes(tm time1 , tm time2)
{
    return (((time2.tm_year - time1.tm_year) * 365 + (time2.tm_mon - time1.tm_mon) * 30 + (time2.tm_mday - time1.tm_mday)) *  24 + (time2.tm_hour - time1.tm_hour)) * 60 + (time2.tm_min - time1.tm_min);
}

vector<Airport> read_csv(const string& filename) 
{
    vector<Airport> data;
    ifstream file(filename);
    if(!file.is_open())
    {
        cerr << "Failed to open file: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    getline(file, line); // 跳过第一行

    while(getline(file, line))
    {
        Airport airport;
        stringstream ss(line);
        string field;
        getline(ss, field, ',');
        airport.id = stoi(field);
        getline(ss, field, '/');
        airport.country = field;
        getline(ss, field, '/');
        airport.province = field;
        getline(ss, field);
        airport.name = field;
        airport.fullName = airport.country + '/' + airport.province + '/' + airport.name;
        data.push_back(airport);
    }
    return data;
}

// 相似度计算函数
double improvedContainmentSimilarity(const string& query, const Airport& airport) 
{
    double result = 0;
    int querySet[26] = {0}, targetSet[26] = {0};

    if(airport.country == query || airport.province == query )
    {
        result ++;
    }

    // 填充查询和目标字符集
    for (char ch : query) 
    {
        if (isalpha(ch))
        querySet[tolower(ch) - 'a'] = 1;
    }   
    for (char ch : airport.name) 
    {
        if (isalpha(ch)) 
        targetSet[tolower(ch) - 'a'] = 1;
    }
    int inter = 0;
    for (int i = 0; i < 26; i++) 
    {
        if (querySet[i] && targetSet[i]) 
        {
            inter++;
        }

    }

    // 计算最长连续匹配长度
    int longestContinuous = 0, currentLen = 0;
    size_t j = 0; // 目标字符串的指针
    for (char ch : query) 
    {
        while (j < airport.name.size() && tolower(airport.name[j]) != tolower(ch)) 
        {
            j++;
            currentLen = 0; // 中断连续匹配
        }
        if (j < airport.name.size() && tolower(airport.name[j]) == tolower(ch)) 
        {
            currentLen++; // 增加连续匹配长度
            longestContinuous = max(longestContinuous, currentLen);
            j++;
        }
    }

    // 包含性得分
    double containmentScore = static_cast<double>(inter) / count(querySet, querySet + 26, 1);
    // 连续匹配得分
    double continuousMatchScore = static_cast<double>(longestContinuous) / query.size();

    // 综合得分
    const double w1 = 0.3, w2 = 0.7; // 权重：包含性、连续匹配
    result += (w1 * containmentScore + w2 * continuousMatchScore);
    return result;

}

// 搜索最相似的机场
void searchAirportsByImprovedSimilarity(const vector<Airport>& airports, const string& query) 
{
    vector<pair<const Airport*, double>> results;

    // 计算每个机场的相似度
    for (const auto& airport : airports) 
    {
        double similarity = improvedContainmentSimilarity(query, airport);
        results.push_back({&airport, similarity});
    }

    // 按相似度降序排序
    sort(results.begin(), results.end(), [](const auto& a, const auto& b) 
    {
        return a.second > b.second;
    });

    // 输出前5个结果
    cout << "Top 5 most similar airport names are as follows:\n";
    for (size_t i = 0; i < min(results.size(), size_t(5)); i++) 
        cout << fixed << setprecision(5) << results[i].first->name << "\n";
    
}

// 搜索直达航班
vector<Flight> findDirectFlight(Data_List& data_list ,int departureID, int arrivalID)
{
    Flight_node* current = data_list.get_head();
    vector<Flight> result;
    while (current != nullptr)
    {
        if(current -> flight_node_data.Departure_airport == departureID 
        && current -> flight_node_data.Arrival_airport == arrivalID)
        {
            result.push_back(current -> flight_node_data);
        }
        current = current -> next;
    }
    return result;
}

// 推荐同省的其他机场
vector<Flight> searchSuitableFlight(Data_List& data_list , vector<Airport> data , int departureID, int arrivalID) 
{
    vector<Flight> result;
    string departureProvince, arrivalProvince;
    vector<int> departureMaybe, arrivalMaybe;
    for (const auto& airport : data)
    {
        if(airport.id == departureID)
        {
            departureProvince = airport.province;
        }
        if(airport.id == arrivalID)
        {
            arrivalProvince = airport.province;
        }
    }
    for (const auto& airport : data)
    {
        if(airport.province == departureProvince)
        {
            departureMaybe.push_back(airport.id);
        }
        if(airport.province == arrivalProvince)
        {
            arrivalMaybe.push_back(airport.id);
        }
    }
    
    Flight_node* current = data_list.get_head();
    while (current != nullptr)
    {
        if(find(departureMaybe.begin() , departureMaybe.end() , current -> flight_node_data.Departure_airport) != departureMaybe.end()
        && find(arrivalMaybe.begin() , arrivalMaybe.end() , current -> flight_node_data.Arrival_airport) != arrivalMaybe.end())
        {
            result.push_back(current -> flight_node_data);
        }
        
        current = current -> next;
    }
    return result;

}

// 主程序
int main() {
    // 从 CSV 文件加载机场数据
    string filename = "Flight_3\\id2name.csv";
    vector<Airport> data = read_csv(filename);
    Data_List data_list;
    data_list.Initialize_Data_List();
    
    while(true)
    {
        cout << setfill('-') << setw(90) << "-" << setfill(' ') << endl; 
        cout << "Please choose a query:" << endl;
        cout << "1. Approximate search" << endl;
        cout << "2. Flight recommendation" << endl;
        cout << "9. Exit" << endl;

        int choice;
        string str;

        getline(cin , str);
        choice = stoi(str);

        if(choice == 1)
        {
            // 查询 1：相似机场名称
            cout << "Please enter the name of the airport you want to search for: " << endl;
            string line;
            getline(cin , line);
            searchAirportsByImprovedSimilarity(data , line);
        }
        else if(choice == 2)
        {
            // 查询 2：同省机场推荐
            cout << "Please enter the two airport ID you want to search for: " << endl;
            string line;
            int airportID1, airportID2;

            getline(cin, line);
            stringstream ss(line);
            getline(ss, line, ',');
            airportID1 = stoi(line);
            getline(ss, line);
            airportID2 = stoi(line);

            if(airportID1 > 79 || airportID1 < 0 || airportID2 > 79 || airportID2 < 0)
            {
                cout << "Invalid airport ID. " << endl;
                continue;
            }

            vector<Flight> result;
            result = findDirectFlight(data_list, airportID1, airportID2);

            if(result.empty())
            {
                cout << "No direct flight found. " << endl;
                result = searchSuitableFlight(data_list, data ,airportID1, airportID2);
                if(!result.empty())
                {
                    cout << "There are " + to_string(result.size()) + " direct ffights from airports in the same province as the arrival airport:" << endl;
                    for(int i = 0; i < result.size(); i++)
                    {
                        cout << "Flight ID: " << result[i].Flight_id 
                        << ", Flight_no: "<< result[i].Flight_no 
                        << ", Departure_time: " << result[i].Departure_time.tm_mon << "/" << result[i].Departure_time.tm_mday << "/" << result[i].Departure_time.tm_year << " " << result[i].Departure_time.tm_hour << ":" << result[i].Departure_time.tm_min
                        << ", Air_fair: " << result[i].Air_fares << endl;
                    }
                }
            
            }
            else
            {
                cout << "There are " + to_string(result.size()) + " direct flights from the departure airport to the arrival airport:" << endl;
                for(int i = 0; i < result.size(); i++)
                {
                        cout << "Flight ID: " << result[i].Flight_id 
                        << ", Flight_no: "<< result[i].Flight_no 
                        << ", Departure_time: " << result[i].Departure_time.tm_mon << "/" << result[i].Departure_time.tm_mday << "/" << result[i].Departure_time.tm_year << " " << result[i].Departure_time.tm_hour << ":" << result[i].Departure_time.tm_min
                        << ", Air_fair: " << result[i].Air_fares << endl;
                }
                cout << endl;

            }
        }
        else if(choice == 9)
        {
            cout << "Goodbye!" << endl;
            return 0;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }

    }


    return 0;
}