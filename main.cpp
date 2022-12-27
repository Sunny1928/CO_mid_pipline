#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "IF.h"
using namespace std;

static int cycle = 0;

class WB{
public:
    string opcode;
    string signal;
    int rs;
    int rt;
    int rd;
    int RegWriteValue;
    WB(){
        opcode = "null";
        signal = "null";
        rs = -1;
        rt = -1;
        rd = -1;
        RegWriteValue = -1;
    }
    void intoWB(string op, string sig, int s, int t, int d, int rwv, int rmv, int *reg){
        opcode=op;
        if(opcode == "null") {
            return;
        }
        signal="     "+sig.substr(5,7);

        rs=s;
        rt=t;
        rd=d;
        RegWriteValue = rwv;
        if(opcode == "lw"){
            reg[rt] = rmv;
        }
        else if(opcode == "add"){
            reg[rd] = RegWriteValue;
        }
        else if(opcode == "sub"){
            reg[rd] = RegWriteValue;
        }
        // add sub

    }
    
    void printResult(){
        if(opcode == "null") cout<<setw(5)<<"wb"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(8)<<'|'<<setw(6)<<'|'<<setw(6)<<'|'<< setw(12)<<'|'<<setw(15)<<'|'<<setw(16)<<'|'<<endl;
        else cout<<setw(5)<<"wb"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd<<'|'<<endl;
    }
};

class MEM{
public:
    string opcode;
    string signal;
    int rs;
    int rt;
    int rd;
    int ALUresult;
    int ReadmemValue;
    
    MEM(){
        opcode = "null";
        signal = "null";
        rs = -1;
        rt = -1;
        rd = -1;
        ALUresult = -1;
        ReadmemValue = -1;
    }
    void intoMEM(string op, string sig, int s, int t, int d, int aluresult, int wd, int *mem){
        opcode=op;
        rs=s;
        rt=t;
        rd=d;
        ALUresult = aluresult;
        if(opcode == "null") {
            return;
        }
        signal="  "+sig.substr(2,7);
        
        // memory
        if(opcode == "lw"){
            ReadmemValue = mem[ALUresult];
        }else if(opcode == "sw"){
            mem[ALUresult] = wd;
        }
    }
    void printResult(){
        if(opcode == "null") cout<<setw(5)<<"mem"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(8)<<'|'<<setw(6)<<'|'<<setw(6)<<'|'<< setw(12)<<'|'<<setw(15)<<'|'<<setw(16)<<'|'<<endl;
        else cout<<setw(5)<<"mem"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd
                    <<'|'<<setw(8) <<'|'<<setw(6) <<'|' <<setw(6) <<'|' << setw(11)<<ALUresult<<'|'<<setw(14)<<ReadmemValue<<'|'<<setw(16)<<'|'<<endl;
;
    }
};

class EX{
public:
    string opcode;
    string signal;
    int rs;
    int rt;
    int rd;
    int reg1;
    int reg2;
    int ALUresult;
    int offset;

    EX(){
        opcode = "null";
        signal = "null";
        rs = -1;
        rt = -1;
        rd = -1;
        reg1 = -1;
        reg2 = -1;
        offset = -1;
    }
    void intoEX(string op, string sig, int s, int t, int d, int o, int r1, int r2){
        opcode=op;
        signal = sig;
        rs=s;
        rt=t;
        rd=d;
        reg1 = r1;
        reg2 = r2;
        offset = o;

        if(opcode == "null") {
            return;
        }

        if(opcode == "add"){
            ALUresult = reg1+reg2;
        }else if(opcode == "sub"){
            ALUresult = reg1-reg2;
        }else if(opcode == "lw"){
            ALUresult = reg1+offset/4;
        }else if(opcode == "sw"){
            ALUresult = reg1+offset/4;
        }
    }

    void printResult(){
        if(opcode == "null") cout<<setw(5)<<"ex"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(8)<<'|'<<setw(6)<<'|'<<setw(6)<<'|'<< setw(12)<<'|'<<setw(15)<<'|'<<setw(16)<<'|'<<endl;
        else cout<<setw(5)<<"ex"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd<<'|'<<setw(7)<<offset<<'|'<<setw(5)<<reg1<<'|'<<setw(5)<<reg2<<'|'<<setw(11)<<ALUresult<<'|'<<setw(15) <<'|'<<setw(16) <<'|'<<endl;
    }
};

class ID{
public:
    string opcode;
    string signal;
    int rs;
    int rt;
    int rd;
    int offset;

    int reg1;
    int reg2;
    
    ID(){
        opcode = "null";
        signal = "null";
        rs = -1;
        rt = -1;
        rd = -1;
        reg1 = -1;
        reg2 = -1;
    }
    void intoID(vector<string> o, int *reg){
        opcode=o[0];
        if(opcode == "null") {
            return;
        }
        signal="";
        rs=0;
        rt=0;
        rd=0;
        offset=0;
        if(opcode == "lw"){
            signal = "0101011";
            rt = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
            rs = stoi(o[2].substr(o[2].find('$')+1, o[2].find(')')));
            offset = stoi(o[2].substr(0, o[2].find('(')));
            this->readReg(reg);
        }
        else if(opcode == "sw"){
            signal = "x10010x";
            rt = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
            rs = stoi(o[2].substr(o[2].find('$')+1, o[2].find(')')));
            offset = stoi(o[2].substr(0, o[2].find('(')));
            this->readReg(reg);

        }
        else if(opcode == "add" || opcode == "sub"){
            signal = "1000010";
            rd = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
            rs = stoi(o[2].substr(o[2].find('$')+1, o[2].find(',')));
            rt = stoi(o[3].substr(o[3].find('$')+1, o[3].length()));
            this->readReg(reg);
        }
        else if(opcode == "beq"){
            signal = "x01000x";
            rs = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
            rt = stoi(o[2].substr(o[2].find('$')+1, o[2].length()));
            offset = stoi(o[3]);
            this->readReg(reg);
        }
    }
    void readReg(int *reg){
        if(opcode == "lw"){
            reg1 = reg[rs];
        }else{
            reg1 = reg[rs];
            reg2 = reg[rt];
        }
    }

    bool beq(){
        return reg1 == reg2;
    }


    void printResult(){
        if(opcode == "null") cout<<setw(5)<<"id"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(8)<<'|'<<setw(6)<<'|'<<setw(6)<<'|'<< setw(12)<<'|'<<setw(15)<<'|'<<setw(16)<<'|'<<endl;
        else cout<<setw(5)<<"id"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd<<'|'<<setw(7)<<offset<<'|'<<setw(5)<<reg1<<'|'<<setw(5)<<reg2<<'|'<<setw(12) <<'|'<<setw(15) <<'|'<<setw(16) <<'|'<<endl;
    }
    
};



class Pipelined{
public:
    IF ifo;
    ID ido;
    EX exo;
    MEM memo;
    WB wbo;
    bool again;
    int reg[32];
    int mem[32];

    Pipelined(){
        again = false;
        reg[0] = 0;
        for(int i=1; i<32; i++){
            reg[i]=1;
        }
        for(int i=0; i<32; i++){
            mem[i]=1;
        }
    }

    // RegDst ALUSrc Branch MemRead MemWrite RegWrite MemtoReg
    void circle(vector<string> arr){
            // else if((exo.opcode == "sw" || exo.opcode == "lw" || exo.opcode == "add" || exo.opcode == "sub") &&
        
        for(int index = 0; index<arr.size(); index++){
            // cout<<"index: "<<index<<endl;
            // cout<<"size: "<<arr.size()<<endl;
        do{
            // cout<<exo.opcode<<' ' << ido.rs <<' '<< exo.rt <<' '<< ido.rt <<' '<< exo.rt <<' '<< ido.rt <<' '<< exo.rd << endl;
            // cout<<memo.opcode<<' ' << ido.rs <<' '<< memo.rt <<' '<< ido.rt <<' '<< memo.rt <<' '<< ido.rt <<' '<< memo.rd << endl;
            if(memo.signal[5] == '1' &&  ido.opcode !="null" &&
                (ido.rs == memo.rt || ido.rt == memo.rt || ido.rt == memo.rd)){
                    // cout<<"s1"<<endl;
                wbo.intoWB(memo.opcode, memo.signal, memo.rs, memo.rt, memo.rd, memo.ALUresult, memo.ReadmemValue, reg);
                memo.intoMEM(exo.opcode, exo.signal, exo.rs, exo.rt, exo.rd, exo.ALUresult, exo.reg2, mem);
                exo.intoEX("null", "null", -1, -1, -1, -1, -1, -1);
                ido.readReg(reg);
                again = true;
            }
            // sw, lw in ex 1000010
            else if(exo.signal[5] == '1' && ido.opcode !="null" &&
                (ido.rs == exo.rt || ido.rt == exo.rt || ido.rt == exo.rd)){
                    // cout<<"s2"<<endl;
                wbo.intoWB(memo.opcode, memo.signal, memo.rs, memo.rt, memo.rd, memo.ALUresult, memo.ReadmemValue, reg);
                memo.intoMEM(exo.opcode, exo.signal, exo.rs, exo.rt, exo.rd, exo.ALUresult, exo.reg2, mem);
                exo.intoEX("null", "null", -1, -1, -1, -1, -1, -1);
                ido.readReg(reg);
                again = true;
            }
            // sub add
            else if(memo.signal[6] == '0' &&
                (ido.rs == memo.rd || ido.rt == memo.rd)){
                    // cout<<"s3"<<endl;
                    // cout<<memo.opcode<<' ' << ido.rs <<' '<< memo.rd <<' '<< ido.rt <<' '<< memo.rd << endl;
                wbo.intoWB(memo.opcode, memo.signal, memo.rs, memo.rt, memo.rd, memo.ALUresult, memo.ReadmemValue, reg);
                memo.intoMEM(exo.opcode, exo.signal, exo.rs, exo.rt, exo.rd, exo.ALUresult, exo.reg2, mem);
                exo.intoEX("null", "null", -1, -1, -1, -1, -1, -1);
                ido.readReg(reg);
                again = true;
            }
            else if(exo.signal[6] == '0' &&
                (ido.rs == exo.rd || ido.rt == exo.rd)){
                    // cout<<"s4"<<endl;
                    wbo.intoWB(memo.opcode, memo.signal, memo.rs, memo.rt, memo.rd, memo.ALUresult, memo.ReadmemValue, reg);
                    memo.intoMEM(exo.opcode, exo.signal, exo.rs, exo.rt, exo.rd, exo.ALUresult, exo.reg2, mem);
                    exo.intoEX("null", "null", -1, -1, -1, -1, -1, -1);
                    ido.readReg(reg);
                    again = true;
            }
            else{
                // cout<<"s5"<<endl;
                wbo.intoWB(memo.opcode, memo.signal, memo.rs, memo.rt, memo.rd, memo.ALUresult, memo.ReadmemValue, reg);
                memo.intoMEM(exo.opcode, exo.signal, exo.rs, exo.rt, exo.rd, exo.ALUresult, exo.reg2, mem);
                exo.intoEX(ido.opcode, ido.signal, ido.rs, ido.rt, ido.rd, ido.offset, ido.reg1, ido.reg2);
                if(ido.opcode == "beq" && ido.beq()){
                    // cout<<"s6"<<endl;
                    ido.readReg(reg);
                    index = index+ ido.offset-1;
                    vector<string> n;
                    n.push_back("null");
                    ido.intoID(n, reg);
                }
                else ido.intoID(ifo.value, reg);
                ifo.intoIF(arr[index]);
                again = false;
            }

            cycle++;
            cout<<"cycle: "<<cycle<<endl;
            cout<<setw(5)<<"stage"<<'|'<<setw(5)<<"op"<<'|'<<setw(8)<<"signal"<<'|'<<setw(3)<<"rs"<<'|'<<setw(3)<<"rt"<<'|'<<setw(3)<<"rd"<<'|'<<setw(7)<<"offset"<<'|'<<setw(5)<<"reg1"<<'|'<<setw(5)<<"reg2"<<'|'<<setw(11)<<"ALUresult"<<'|'<<setw(14)<<"ReadmemValue"<<'|'<<setw(15)<<"RegWriteValue"<<'|'<<endl;
            ifo.printResult();
            ido.printResult();
            exo.printResult();
            memo.printResult();
            wbo.printResult();
            cout<<"reg ";
            for(int i = 0; i<32; i++){
                cout<<reg[i]<<' ';
            }
            cout<<endl;
            cout<<"mem ";
            for(int i = 0; i<32; i++){
                cout<<mem[i]<<' ';
            }
            cout<<endl;
            cout<<endl;
            
        }while(again);
        }
        
        
    }
};

int main(){
    ifstream ifs(".\\test_data\\q1.txt",ios::in);
    if(!ifs.is_open()){
        cout<<"fail to open this file"<<endl;
        return 1;
    }

    stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    string s;

    vector<string> arr;
    while(getline(ss, s)){
        // cout<<s<<endl;;
        arr.push_back(s);
    }
    arr.push_back("null");
    arr.push_back("null");
    arr.push_back("null");
    arr.push_back("null");
    
    Pipelined pipe;
    pipe.circle(arr);

    return 0;
}