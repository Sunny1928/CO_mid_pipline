# 2022計組期末專題 - CPU pipeline

## 環境
* Ubuntu 22.04.1 LTS
* Vscode
* C/C++ standard: C11
* C/C++ compiler: g++
> Windows系統可以編譯，但因為cmd指令不同，clean、clean-all無法使用


## 如何使用

> 使用makefile的方式避免編譯環境上的問題，你只需要確保你有開發環境中的編譯器及make的工具 \
> 如果沒有make的工具，在Linux系統的cmd中輸入 
> ```cmd 
> sudo apt install make
> ```


首先，開啟你的bash界面，並輸入以下指令，將此專案下載到本地端

```cmd
cd Desktop
git clone https://github.com/Sunny1928/CO_mid_pipline.git
```
進入 CO_mid_pipline 中，並進行編譯
```cmd
cd CO_mid_pipline
make
```
開始執行
```cmd
#使用預設
./main 

# 放入檔案路徑
./main <file_path>
```
清除所有.o檔，不包含執行檔
```cmd
make clean
```
清除所有.o檔，包含執行檔
```cmd
make clean-all
```

## 專案架構
```
CO-mid_pipline
├── main.cpp
├── Makefile
├── README.md
├── lib
│   ├── include
│   │   ├── CPU_pipeline.h
│   │   ├── EX.h
│   │   ├── ID.h
│   │   ├── IF.h
│   │   ├── MEM.h
│   │   └── WB.h
│   └── src
│       ├── CPU_pipeline.cpp
│       ├── EX.cpp
│       ├── ID.cpp
│       ├── IF.cpp
│       ├── MEM.cpp
│       └── WB.cpp
└── test_data
    ├── q1.txt
    ├── q2.txt
    ├── q3.txt
    ├── q4.txt
    ├── q5.txt
    ├── q6.txt
    ├── q7.txt
    └── q8.txt

```
## 程式流程
<img src="https://github.com/Sunny1928/CO_mid_pipline/blob/main/Flow_Chart.png" width = "70%">

## 程式說明
程式碼中,我們的ID所用到的rs,rt,rd為IF/ID register,EX用的為ID/EX register,以此類推
## 遇到問題

## 分工

## Contributors
|Name|Github Link|
| :-----|:-----|
|Yu-Yi Chuang | https://github.com/Sunny1928|
|Yi-Cheng Liao |https://github.com/yeeecheng| 
