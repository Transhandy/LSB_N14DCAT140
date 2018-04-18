#include <fstream>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <cmath>
using namespace std;
string BinToText(string bin){
	string result="";
	for(int i=0; i<bin.length(); i=i+8){
		int temp=0;
		int count=7;
		for(int j=0; j<8; j++){
			temp += (bin[i+j]-48)*pow(2,count--);
		}
		result+=(char)temp;
	} 	
	return result;
}
string TextToBin(string mess){
	string result = "";
	for(int i=0; i < mess.length(); i++){
		int temp = mess[i];
		string temp_byte="";
		for(int j=0; j<8; j++){
			temp_byte[j] = temp%2 + 48;   
			temp /=2;
		}
		for(int t=7; t>=0; t--){
			result += temp_byte[t];
		}	
	}
	return result;
}
int main(){
	string mess, bin_string="";
	long bmpsize;
	ifstream inbmp("ghitaed.bmp",ifstream::binary);
	inbmp.seekg (0,inbmp.end);
	bmpsize = inbmp.tellg();
	inbmp.seekg (0);
	char *buffer = new char[bmpsize];			
	inbmp.read (buffer,bmpsize);
	int header = 54;
	int count_zero=0;
	while(true){
		if(buffer[header]%2==0) {
			bin_string+="0";
			count_zero+=1;
		}
		else {
			bin_string +="1";
			count_zero=0;
		}
		header++;
		if(count_zero==8) break;
	}
	cout << BinToText(bin_string);
	delete[] buffer;
	inbmp.close();
}

