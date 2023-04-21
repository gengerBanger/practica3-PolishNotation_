#include <iostream>
#include <string>
#include <map>
struct List_ch {
    char data;
    List_ch *tail;
};
struct List_str{
    std :: string data;
    List_str *tail;
};
class Stack_ch {
    List_ch * curr = nullptr;
public :
    void itemPush(char value){
        List_ch * item = new List_ch;
        if(curr == nullptr){
            curr = item;
            item->tail = nullptr;
        }
        else{
            item->tail = curr;
            curr = item;
        }
        item->data = value;
    }
    void itemOut(std::string &str) {
    if(!empty()){
        List_ch ** buff = new List_ch*(curr);
        if( curr->data != '(' and curr->data != ')') {
            str.push_back(curr->data);
            str.push_back(' ');
        }
        curr = curr->tail;
        delete *buff;
        delete buff;
    }
    else std :: cout <<"Stack is empty"<<'\n';
    }
    void stackOut(){
    if(!empty()){
        List_ch * buff = curr;
        std :: cout << "~~Stack : ";
        while(buff){
            std :: cout << buff->data << " ";
            buff = buff->tail;
        }
        std :: cout << "\n      head^\n\n";
    }
    else std :: cout <<"~~Stack is empty~~"<<'\n';
}
    List_ch * GetCurr(){
        return curr;
    }
    bool empty(){
        if(curr == nullptr) return true;
        else return false;
    }
};
class Stack_str {
    List_str * curr = nullptr;
public :
    void itemPush(std :: string value){
        List_str * item = new List_str;
        if(curr == nullptr){
            curr = item;
            item->tail = nullptr;
        }
        else{
            item->tail = curr;
            curr = item;
        }
        item->data = value;
    }
    std :: string itemOut() {
        if(!empty()){
            List_str ** buff = new List_str*(curr);
            std :: string buff_str;
            buff_str = curr->data;
            curr = curr->tail;
            delete *buff;
            delete buff;
            return buff_str;
        }
        else std :: cout <<"Stack is empty"<<'\n';
    }
    void stackOut(){
        if(!empty()){
            List_str * buff = curr;
            std :: cout << "~~Stack : ";
            while(buff){
                std :: cout << buff->data << " ";
                buff = buff->tail;
            }
            std :: cout << "\n      head^\n\n";
        }
        else std :: cout <<"~~Stack is empty~~"<<'\n';
    }
    List_str * GetCurr(){
        return curr;
    }
    bool empty(){
        if(curr == nullptr) return true;
        else return false;
    }
};
void reversingString(std :: string &str){
    std :: string reverse_str;
    for(int i = str.length() - 1; i >= 0;i--){
        reverse_str.push_back(str[i]);
    }
    str = reverse_str;
}
class ReverseOrStraight_Notation{
    bool flagCreation;
    int ReverseOrStraight_flag;
    int checkPriority(char num) {
        switch(num){
            case '(':{
                return ReverseOrStraight_flag;
            }
            case'+':case'-':{
                return 2;
            }
            case'*':case'/':{
                return 3;
            }
            case')':{
                return -ReverseOrStraight_flag;
            }
            default : {
                return 0;
            }
        }
    }
    void outResult(std :: string &new_str, Stack_ch &sta){
        sta.stackOut();
        std :: cout << "~~String :"<< new_str<<" \n\n";
    }
    bool checkString(std :: string str){
        for(int i = 0; i < str.length(); i++) {
            if(LetterCheck(str[i]) and (LetterCheck(str[i + 1]))) return false;
            if ((checkPriority(str[i]) == checkPriority(str[i + 2])) and str[i + 1] == ' ')return false;
            if(((checkPriority(str[i]) == 2) or (checkPriority(str[i]) == 3)) and ((checkPriority(str[i + 1]) == 2) or (checkPriority(str[i + 1]) == 3))) return false;
            if (((checkPriority(str[i]) == 2) or (checkPriority(str[i]) == 3) or (checkPriority(str[i]) == -1)) and i == 0)return false;
            if (((checkPriority(str[i]) == 2) or (checkPriority(str[i]) == 3) or (checkPriority(str[i]) == 1)) and
                i == str.length() - 1) return false;
            if(checkPriority(str[i]) == 1 and checkPriority(str[i + 1]) == -1 )return false;
        }
        return true;
    }
    void processing(std :: string str,std :: string &new_str, Stack_ch &sta){
        std :: string buffStr;
        for(int i = 0; i < str.length();i++) {
            buffStr.clear();
            switch (checkPriority(str[i])) {
                case 0:{
                    do{
                        buffStr+=str[i++];
                    }while(checkPriority(str[i]) == 0 && i < str.length());
                    i--;
                    new_str += buffStr + ' ';
                    break;
                }
                case 1:{
                    sta.itemPush(str[i]);
                    break;
                }
                case 2: case 3: {
                    if(sta.empty()) {
                        sta.itemPush(str[i]);
                    }
                    else{
                        if (checkPriority(str[i]) > checkPriority(sta.GetCurr()->data)){
                            sta.itemPush(str[i]);
                        }
                        else{
                            while(!sta.empty() && checkPriority(sta.GetCurr()->data) >= checkPriority(str[i])){
                                sta.itemOut(new_str);
                            }
                            sta.itemPush(str[i]);
                        }
                    }
                    break;
                }
                case -1:
                {
                    while(checkPriority(sta.GetCurr()->data) != 1){
                        sta.itemOut(new_str);
                    }
                    sta.itemOut(new_str);
                    break;
                }
            }
            outResult(new_str,sta);
        }
        while(!sta.empty()){
            sta.itemOut(new_str);
        }
    }
    void removingSpaces(std :: string &str){
        for(int i = 0; i < str.length(); i++){
            if ((str[i] == ' ') && (str[i + 1] == ' ')) {
                while (!((str[i] == ' ') && (str[i + 1] != ' '))) {
                    str.erase(str.begin() + i);
                }
            }
        }
    }
    bool LetterCheck(char ch){
        return (ch >= 'A'&& ch <= 'Z') || (ch >= 'a'&& ch <= 'z');
    }
    void initialization(std :: string &str){
        std :: map <char,std :: string> storage;
        for(int i = 0; i < str.length(); i++){
            if(LetterCheck(str[i])){
                storage[str[i]] = '0';
            }
        }
        if(!storage.empty()){
            for( auto it = storage.begin();it != storage.end();it++){
                std :: cout <<"~~enter "<< it->first << " value~~\n";
                std :: cin >>it->second;
            }
            for(int i = 0; i < str.length(); i++){
                if(LetterCheck(str[i])){
                    char *g = new char (str[i]);
                    str.erase(i, 1);
                    str.insert(i,storage[*g]);
                    delete g;
                }
            }
        }
    }
    void checkChar(char ch, Stack_str &sta){
        switch (ch) {
            case'+':
            {
                double i1(std:: stod(sta.itemOut())), i2(std :: stod(sta.itemOut()));
                sta.itemPush(std ::to_string(i1 + i2));
                break;
            }
            case'-':
            {
                double i1(std:: stod(sta.itemOut())), i2(std :: stod(sta.itemOut()));
                if (ReverseOrStraight_flag == 1)sta.itemPush(std ::to_string(i2 - i1));
                else sta.itemPush(std ::to_string(i1 - i2));
                break;
            }
            case'*':
            {
                double i1(std:: stod(sta.itemOut())), i2(std :: stod(sta.itemOut()));
                sta.itemPush(std ::to_string(i1 * i2));
                break;
            }
            case'/':
            {
                double i1(std:: stod(sta.itemOut())), i2(std :: stod(sta.itemOut()));
                if (ReverseOrStraight_flag == 1) sta.itemPush(std ::to_string(i2 / i1));
                else  sta.itemPush(std ::to_string(i1 / i2));
                break;
            }
        }
    }
    public :
    std :: string result;
    ReverseOrStraight_Notation(std :: string str, Stack_ch sta, int key){
        ReverseOrStraight_flag = key;
        if(checkString(str)){
            initialization(str);
            if(ReverseOrStraight_flag == 1) std :: cout << "-----String : " << str << '\n';
            else{
                std :: cout << "-----String : " << str << '\n';
                reversingString(str);
            }
            processing(str, result,sta);
            removingSpaces(result);
            flagCreation = true;
        }
        else{
            flagCreation = false;
        }
    }
    ReverseOrStraight_Notation(std :: string str, int key){
        ReverseOrStraight_flag = key;
        result = str;
    }
    void calculation(Stack_str sta){
        if(!result.empty()){
            if(ReverseOrStraight_flag == -1) reversingString(result);
            std :: string buffStr;
            for(int i = 0; i < result.length(); i++){
                buffStr.clear();
                switch (checkPriority(result[i])) {
                    case 0:{
                        do{
                            if(result[i] != ' ')buffStr += result[i++];
                            else {
                                i++;
                                break;
                            }
                        }while(checkPriority(result[i]) == 0 && i < result.length());
                        i--;
                        if(!buffStr.empty())sta.itemPush(buffStr);
                        break;
                    }
                    case 2: case 3:{
                        if (result[i] != ' ')checkChar(result[i], sta);
                        break;
                    }
                }
                sta.stackOut();
            }
            std :: cout << "~~Result : " << std :: stod(sta.itemOut())<< " ~~\n";
        }
    }
    void output(){
        if(flagCreation && ReverseOrStraight_flag == 1) std :: cout <<"Reverse Notation :"<< result <<'\n';
        else{
            if(flagCreation && ReverseOrStraight_flag == -1) std :: cout <<"Straight Notation :"<< result <<'\n';
            else std :: cout <<"Invalid input\n";
        }
    }
};
int main() {
    Stack_ch new_stack;
    Stack_str str_stack;
    short int key_str(-1), key_rev(1);
    std :: string str;
    bool flagRepeat = true;
    std :: cout << std :: fixed;
    std :: cout.precision(2);
    char key;
    while(flagRepeat){
        std :: cout << "\t~~What orm will the expression take~~\n1) Common expression\n2) Straight notation\n3) Reverse notation\n0) Exit\n";
        std :: cin >> key;
        std :: cin.clear();
        while(std :: cin.get() != '\n');
        std :: cout << "\t~~Enter a mathematical expression~~\n";
        getline(std :: cin, str);
        switch (key) {
            case '1':{
                std :: cout << "\t~~Which notation do you want to build~~\n1) Straight\n2) Reverse\n";
                std :: cin.clear();
                while(std :: cin.get() != '\n');
                std :: cin >> key;
                switch (key) {
                    case'1':{
                        ReverseOrStraight_Notation str_notation(str,new_stack,key_str);
                        reversingString(str_notation.result);
                        str_notation.output();
                        std :: cin.clear();
                        while(std :: cin.get() != '\n');
                        str_notation.calculation(str_stack);
                        break;
                    }
                    case'2':{
                        ReverseOrStraight_Notation rev_notation(str,new_stack,key_rev);
                        rev_notation.output();
                        std :: cin.clear();
                        while(std :: cin.get() != '\n');
                        rev_notation.calculation(str_stack);
                        break;
                    }
                    default :{
                        std :: cout <<"error";
                    }
                }
                break;
            }
            case '2':{
                ReverseOrStraight_Notation str_notation(str,key_str);
                str_notation.calculation(str_stack);
                break;
            }
            case '3':{
                ReverseOrStraight_Notation rev_notation(str,key_rev);
                rev_notation.calculation(str_stack);
                break;
            }
            case'0':{
                flagRepeat = false;
                break;
            }
            default:{
                std :: cout << "error\n";
            }
        }
    }
    system("pause");
    return 0;
}