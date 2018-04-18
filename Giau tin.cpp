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
	string mess, bin_string;
	long bmpsize, bin_len;
	cout<<"Nhap message muon giau: "<<endl;
	fflush(stdin);getline(cin,mess);
	bin_string=TextToBin(mess);
	bin_len = bin_string.length();
	ifstream inbmp("ghita.bmp", ifstream::binary);
	inbmp.seekg (0,inbmp.end); 
	bmpsize = inbmp.tellg();
	inbmp.seekg (0);
	if((bmpsize-54)  < bin_len){
		cout <<"Khong the giau tin vao anh duoc"<< endl;
		return 0;
	}
	else{
		ofstream outbmp("ghitaed.bmp", ofstream::binary);
		char* buffer = new char[bmpsize];
		inbmp.read(buffer,bmpsize);
		int header = 54;
		for(int i=0; i<bin_len; i++){
			buffer[header] >>= 1;
			buffer[header] <<=1;
			buffer[header] += (bin_string[i]-48);
			header++;
		}
		for(int j=1; j<=8; j++){
			buffer[header] >>= 1;
			buffer[header] <<=1;
			buffer[header] += 0;
			header++;
		}
		outbmp.write(buffer,bmpsize);
		cout << "Da hoan tat giau tin" << endl;
		delete[] buffer;
		inbmp.close();
		outbmp.close();
	}
	return 0;
}
