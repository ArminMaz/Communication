#include <iostream>
#include <string.h>
#include <math.h>
#include <stdio.h>
using namespace std;

int numberOfCities = 0;
const double pie = 3.141592653;

class City;
int findIndexOfTheName(City[], string);

class City{
    
    public:
    string name;
    string type;
    string textMessage;
    double textSize, callLenght, videoCallLength, videoCallWidth, videoCallHeight;
    bool text = false, voice = false, video = false;

    City(){

    }

    void availblities(){
        if(type.find("TEXT") != std::string::npos){
            text = true;
        }
        if(type.find("VOICE") != std::string::npos){
            voice = true;
        }
        if(type.find("VIDEO") != std::string::npos){
            video = true;
        }
    }
    
    //Functions for text
    public:
    void getTextMessage(){
        getline(cin, textMessage);
    }
    virtual void setTextSize(){
    }
    void printTextPrice(){
        if(textSize >= 0){
            cout << "Price: " << textSize * 40 << endl;
        }else{
            cout << "Price: 0" << endl;
        }
    }

    //Functions for calls
    public:
    void getCallLenght(){
        cin >> callLenght;
    }
    void getVideoCallValues(){
        cin >> callLenght;
        scanf("%d*%d", &videoCallWidth, &videoCallHeight);
    }
    virtual void setCallLenght(){
    }
    void printVoiceCallPrice(int** vector, int index1, int index2){
        cout << "Price: " << (pow(callLenght, 2) * vector[index1][index2] / 10) << endl;
    }
    void printVideoCallPrice(int ** vector, int index1, int index2){
        cout << "Price: " << (callLenght * log((videoCallHeight * videoCallWidth)) * vector[index1][index2]) / 10 << endl;
    }

    virtual string identifier(){
    }
    
};

class UnSafe : public City{
    public:
    string identifier(){
        return "UnSafe";
    }
    public:
    void setTextSize(){
        textSize = textMessage.length() - 3;
    }

    void setCallLenght(){

    }


};

class SemiSafe : public City{
    public:
    string identifier(){
        return "Semi-Safe";
    }
    public:
    void setTextSize(){
        textSize = textMessage.length() - 3;
        textSize = (log(textSize) * 100 + 20);
    }

    void setCallLenght(){
        callLenght *= pow(pie, 2);
    }
};

class Safe : public City{
    public:
    string identifier(){
        return "Safe";
    }
    public:
    void setTextSize(){
        textSize = textMessage.length() - 3;
        textSize = (log(pow(textSize, 2)) * 200 + 30);
    }

    void setCallLenght(){
        callLenght *= log(callLenght);
    }



};

class Fast : public City{

    public:
    void setTextSize(){
        textSize = textMessage.length() - 3;
        textSize *= ceil(textSize / 140);
    }
};

int findIndexOfTheName(City town[], string name){
    int counter;
    for(counter = 0; counter < numberOfCities; counter++){
        if(town[counter].name == name){
            return counter;
        }
    }
    return -1;
}

City* addElementToArray(City a[], int* numberOfCities){

    City* b = new City[(*numberOfCities + 1)];
    int counter;
    
    for(counter = 0; counter < *numberOfCities; counter++){
        b[counter] = a[counter];
    }

    delete[] a; 
    *numberOfCities += 1;

    return b;
    
}

City* getValues(){

    City* city = new City[0];
    string name;

    while(1){
        cin >> name;
        if(name == "#"){
            break;
        }
        city = addElementToArray(city, &numberOfCities);
        city[numberOfCities - 1].name = name;
        getline(cin, city[numberOfCities - 1].type);
        city[numberOfCities - 1].availblities();
    }

    return city;
}

int** getDistance(City town[]){
    
    int ** vector = new int*[numberOfCities];
    for(int counter = 0; counter < numberOfCities; counter++){
        vector[counter] = new int[numberOfCities];
    }
    string name1, name2;
    
    for(int i = 0; i < numberOfCities; i++){
        for(int j = 0; j < numberOfCities; j++){
            vector[i][j] = -1;
        }
    }
    
    while(1){
        cin >> name1;
        if(name1 == "$"){
            break;
        }
        cin >> name2;
        cin >> vector[findIndexOfTheName(town, name1)][findIndexOfTheName(town, name2)];
        vector[findIndexOfTheName(town, name2)][findIndexOfTheName(town, name1)] = vector[findIndexOfTheName(town, name1)][findIndexOfTheName(town, name2)];
    }


    return vector;
}

void textFunction(City* town,int** vector, City* pointer, int index1, int index2){

    pointer->getTextMessage();

    if(town[index1].text && town[index2].text){
        if(vector[index1][index2] < 0){
            cout << "No path found" << endl;
        }else{
            pointer->setTextSize();
            cout << "Distance: " << vector[index1][index2] << ", ";
            pointer->printTextPrice();
        }
    }else{
            cout << "TEXT is not availble in this path." << endl;
    }

}

void voiceCallFunction(City* town,int** vector, City* pointer, int index1, int index2){

    pointer->getCallLenght();

    if(town[index1].voice && town[index2].voice){
        if(vector[index1][index2] < 0){
            cout << "No path found" << endl;
        }else{
            pointer->setCallLenght();
            cout << "Distance: " << vector[index1][index2] << ", ";
            pointer->printVoiceCallPrice(vector, index1, index2);
        }
    }else{
        cout << "VOICE_CALL is not availble in this path." << endl;
    }
}

void videoCallFunction(City* town, int** vector, City* pointer, int index1, int index2){

    pointer->getVideoCallValues();

    if(town[index1].video && town[index2].video){
        if(vector[index1][index2] < 0){
            cout << "No path found" << endl;
        }else{
            pointer->setCallLenght();
            cout << "Distance: " << vector[index1][index2] << ", ";
            pointer->printVideoCallPrice(vector, index1, index2);
        }
    }else{
        cout << "VIDEO_CALL is not availble in this path." << endl;
    }
}

void program(City* town, int** vector){
    
    string firstInput, secondInput, mode, textMessage;
    int voiceCallLength, videoCallLength, videoWidth, videoHeight;
    int index1, index2;
    bool endProgram = false;
    UnSafe unsafe;
    SemiSafe semiSafe;
    Safe safe;
    Fast fast;
    City* pointer = &unsafe;

    while(1){

        cin >> firstInput;
        if(firstInput == "END"){
            break;
        }

        //Entering the mode:
        if(firstInput == "Safe"){
            pointer = &safe;
            continue;
        }
        if(firstInput == "Unsafe"){
            pointer = &unsafe;
            continue;
        }
        if(firstInput == "Semi-Safe"){
            pointer = &semiSafe;
            continue;
        }
        if(firstInput == "Fast"){
            if(pointer->identifier() == "UnSafe"){
                pointer = &fast;
            }else{
                cout << "Not provided for this level of security." << endl;
            }
            continue;
        }
        cin >> secondInput;
        if(secondInput == "END"){
            break;
        }
        cin >> mode;
        if(mode == "END"){
            break;
        }

        //Finding index of cities
        index1 = findIndexOfTheName(town, firstInput);
        index2 = findIndexOfTheName(town, secondInput);

        if(index1 == -1 || index2 == -1){
            cout << "Invalid city names." << endl;
            continue;
        }

        //Performing the order
        if(mode == "TEXT"){
            textFunction(town, vector, pointer, index1, index2);
        }else if(mode == "VOICE_CALL"){
            voiceCallFunction(town, vector, pointer, index1, index2);
        }else if(mode == "VIDEO_CALL"){
            videoCallFunction(town, vector, pointer, index1, index2);
        }else{
            cout << "Invalid Command" << endl;
        }
    }
}


int main(){
    City* town = getValues();
    int** vector = getDistance(town);
    program(town, vector);
    return 0;
}