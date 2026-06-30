# Data Structure Experiments

> 数据结构课程实验 — 2024 秋 · 第三学期

**Author:** 程宣赫 (2023202250)

---

## 📁 目录结构

```
.
├── Homework1/                    # 实验一：三元组 ADT
│   └── Triplet.cpp               #   三元组的构造/销毁/读写/运算
│
├── Homework2_Flight/             # 实验二：航班数据管理系统（链表）
│   ├── software/
│   │   ├── Data_List.cpp         #   单链表实现航班 CRUD
│   │   └── Flight_Data2024.csv   #   航班数据集
│   ├── image1.png                #   程序截图
│   ├── 实验报告.pdf               #   实验报告
│   └── 用户使用手册.pdf            #   用户使用手册
│
├── Homework3_Flight2/            # 实验三：航班数据管理 v2
│   └── flight-data.csv           #   航班数据集
│
├── Homework4_Flight3/            # 实验四：航班航线搜索（图算法）
│   ├── Flight_3/
│   │   ├── Flight_search.cpp     #   图遍历 + 最短路径搜索
│   │   ├── flight-data.csv       #   航班数据
│   │   └── id2name.csv           #   机场 ID → 名称映射
│   └── id2name.csv               #   机场映射表
│
├── 数据结构2024实验手册-全部实验.pdf  # 课程实验手册
└── README.md
```

## 🔧 实验内容

| 实验 | 内容 | 核心知识点 |
|------|------|-----------|
| Homework1 | 三元组抽象数据类型 | 结构体、类封装、ADT 设计 |
| Homework2 | 航班数据管理系统 | 单链表、文件 I/O、CRUD 操作 |
| Homework3 | 航班数据管理 v2 | 数据结构优化 |
| Homework4 | 航线搜索系统 | 图论、BFS/DFS、最短路径、哈希映射 |

## 🛠 编译运行

```bash
# Homework1 — 三元组
g++ -o Triplet Homework1/Triplet.cpp && ./Triplet

# Homework2 — 航班链表管理
g++ -std=c++11 -o Data_List Homework2_Flight/software/Data_List.cpp && ./Data_List

# Homework4 — 航班图搜索
g++ -std=c++11 -o Flight_search Homework4_Flight3/Flight_3/Flight_search.cpp && ./Flight_search
```

## 📄 License

This repository is for educational purposes as part of the Data Structure coursework.
