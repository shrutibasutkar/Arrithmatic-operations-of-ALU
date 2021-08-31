
//*********************************************************************************************************************************
//       Author:            Shruti Basutkar
//       Creation Date:     11/07/2019
//     
//*********************************************************************************************************************************

#include<iostream>		
#include<string>        
#include<cstring>		
#include<sstream>		
#include <cstdlib>      
#include<fstream>  		
#include<cmath>
using namespace std;	

ofstream output; 		

/***************************************************************************************************
*int HexToDec(char digit):
*Purpose: This function is use to convert single digit from Hexdecimal to Decimal. It has been used in 
*		  following functions to perform arithmatic operation digit by digit.
***************************************************************************************************/
int HexToDec(char digit)
{
	int hex;
	if((int) digit >= 48 && (int) digit <= 57)		
		hex = (int)digit -48;  						   
	else if ((int)digit >= 65 && (int)digit <= 70)	
		hex = (int)digit - 55;						
	
	return hex;
}

/***************************************************************************************************
*void makeSameOperandLength(string& Operand1, string& Operand2):
*Purpose: This function will help to make same length of two passing string parameters.
*		  This is require in the following arithmatic functions to perform arithmatic operation on 
*		  hexadecimal values.
***************************************************************************************************/
void makeSameOperandLength(string& Operand1, string& Operand2)
{
	int MaxOpLen;									
	int MinOpLen;									 
	
	if(Operand1.length() >= Operand2.length())		
	{
		MaxOpLen = Operand1.length();				
		MinOpLen = Operand2.length();				
	}
	else 
	{
		MaxOpLen = Operand2.length();
		MinOpLen = Operand1.length();
	}		
	
	/********************
	*If Operand2 is small in length then make it's length equal  	
	*to MaxOpLen by inserting no. of Zeroes equal to "lenDiff"
	********************/
	int lenDiff;									
	lenDiff = MaxOpLen - MinOpLen;	
	
	if(Operand1.length() >= Operand2.length())		
		Operand2.insert(0, lenDiff, '0');			 
	else
		Operand1.insert(0, lenDiff, '0');
}
/***************************************************************************************************
*string Addition(string& Operand1, string& Operand2)):
*Purpose: This function performs "Addition (+)" arithmatic operation digit by digit.

***************************************************************************************************/
string Addition(string& Operand1, string& Operand2)
{
	makeSameOperandLength(Operand1, Operand2);		
	
	int Len = Operand1.length();					
	char Sum[Len];									
	string SumString;								
	int CarryBit = 0;								
	int Op1Digit;									
	int Op2Digit;									
	
	for(int i=(Len-1);  i >= 0; --i)             
	{												
		Op1Digit = HexToDec(Operand1[i]); 			
		Op2Digit = HexToDec(Operand2[i]);			
		
		int temp;
		temp = Op1Digit + Op2Digit + CarryBit;		
		if(temp >= 16)								
		{
			Sum[i] = temp - 16;
			CarryBit = 1;							
		}											
		else 
		{
			Sum[i] = temp;							
			CarryBit = 0;
		}
	}	
	
	if(CarryBit == 1)							
		SumString = SumString + '1';
		
	for (int i=0; i < Len; i++)						
	{												
		if(Sum[i] < 10)
			Sum[i] += 48;
		else
			Sum[i] += 55;
		SumString = SumString + Sum[i];				
	}		
	return SumString;							
}
/***************************************************************************************************
*string Mul(string& Operand1, string& Operand2):
*Purpose: This function performs "Multiplication (*)" arithmatic operation digit by digit.

***************************************************************************************************/
string Mul(string& Operand1, string& Operand2)
{
	int Op2Len = Operand2.length();					
	int Op2Digit;
	int zeroCount = 0;								
	string MulFinal;								
	string Mul[Op2Len];								
	
	if (Operand2 == "0")							
		return "0";
	
	for(int i = Op2Len-1; i >= 0; --i)				
	{
		Op2Digit = HexToDec(Operand2[i]);			
		for(int j=1; j <= Op2Digit ; j++)			
			Mul[i] = Addition(Mul[i], Operand1);	
		
		for(int n = 0; n < zeroCount; n++)			
			Mul[i] = Mul[i] + '0';
			
		zeroCount ++;								 
	}
	for(int i=0; i < Op2Len; i++)					
	MulFinal = Addition(MulFinal, Mul[i]);			
	
	return MulFinal;								
}
/***************************************************************************************************
*string Power(string& Operand1, string& Operand2):
*Purpose: This function performs "Power ($)" arithmatic operation digit by digit.
***************************************************************************************************/
string Power(string& Operand1, string& Operand2)
{
	int Len = Operand2.length();
	int powNo = HexToDec(Operand2[Len-1]);			
	string PowerAns= "1";							
	
	for(int i=1; i<= powNo; i++)					
	{
		PowerAns = Mul(Operand1, PowerAns);			
	}
	
	return PowerAns;								
}

/***************************************************************************************************
*string Compliment(string& Operand1):
*Purpose: This function performs "16's compliment", which we will use in Subtraction function.
***************************************************************************************************/
string Compliment(string& Operand1)
{
	int OpLen = Operand1.length();					
	int OpDigit;									
		
	char ComplimentChar[OpLen];						
	string ComplimentStr;							
	
	// get 15's compliment of operand
	for(int i = OpLen-1; i >= 0; --i)				
	{												
		OpDigit = HexToDec(Operand1[i]);			
		ComplimentChar[i] = 15 - OpDigit;			
	}

	for(int i=0; i<OpLen; i++)						
	{
		if(ComplimentChar[i] < 10)
			ComplimentChar[i] += 48;
		else
			ComplimentChar[i] += 55;
		
		ComplimentStr = ComplimentStr + ComplimentChar[i];	
	}
	
	string one = "1";								
	ComplimentStr = Addition(ComplimentStr, one );	
	
	return ComplimentStr;							
}

/***************************************************************************************************
*string subtraction(string& Operand1, string& Operand2):
*Purpose: This function performs "subtraction (-)" arithmatic operation digit by digit.
***************************************************************************************************/
string subtraction(string& Operand1, string& Operand2)
{
	string SubString;									
	
	int Len;										
	makeSameOperandLength(Operand1, Operand2);			
	
	Len = Operand1.length();							
	string Operand2Compli;								
	Operand2Compli = Compliment(Operand2);				
	
	SubString = Addition(Operand1, Operand2Compli);		
	
	if (SubString.length() != Len)						
		SubString.erase(SubString.begin() + 0);
		
	return SubString;									
	
}

/***************************************************************************************************
*void Division(string& Operand1, string& Operand2):
*Purpose: This function performs "Division (/)" arithmatic operation digit by digit.
***************************************************************************************************/
void Division(string& Operand1, string& Operand2)
{
	string counter = "0";								
	string one = "1";																
	string remainder;										
	string quotient;									
	
	makeSameOperandLength(Operand1, Operand2);			
	
	while(Operand1 >= Operand2)							
	{
		Operand1 = subtraction(Operand1, Operand2);		
		counter = Addition(counter, one);					
	}
	remainder = Operand1;								
	quotient = counter;									
			
	cout<<"quotient "<<quotient<<", "<<"remainder "<<remainder<<endl;		
	output<<"quotient "<<quotient<<", "<<"remainder "<<remainder<<endl;		
}

/***************************************************************************************************
*int main(int argc, char** argv):
*Purpose: Main() function will test all arithmatic operation created in this program.
***************************************************************************************************/
int main(int argc, char** argv){
	fstream myFile;                                                     /	
	myFile.open(argv[1]);                                          		
	output.open(argv[2]);												
	if(!myFile)                                                        
		cout<<"Error while opening File: "<<argv[1]<<endl;
    else                                                               
	{  
		cout<<"\nFile open successfully here is the result: " <<endl;   // Prompt messege for successful opening of file		
		string input;													
		string Operand1;												
		string Operand2;												
		int operatorPlace;															
		int len;																										
		char Operator;													
		
			while(getline(myFile, input))                             
			{
				len = input.length();									
				
				for(int i=0; i<=len; i++)								
				{
					if((input[i] == '+') || (input[i] == '-') || (input[i] == '*') ||(input[i] == '/') || (input[i] == '$'))
					{
						operatorPlace = i;
						Operator = input[i];
						
						break;											
					}				
					if(i==len)
						cout<<"\nNo Operator here."<<endl;		
				}	
				
				stringstream ss(input);									
				getline(ss, Operand1,Operator);							
				getline(ss, Operand2,'=');								
				
				if(Operator == '+')										
				{
					cout<<input<<Addition(Operand1, Operand2)<<endl;
					output<<input<<Addition(Operand1, Operand2)<<endl;					
				}
				
				if(Operator == '*')									
				{
					cout<<input<<Mul(Operand1, Operand2)<<endl;
					output<<input<<Mul(Operand1, Operand2)<<endl;
				}
				
				if(Operator == '$')									
				{
					cout<<input<<Power(Operand1, Operand2)<<endl;
					output<<input<<Power(Operand1, Operand2)<<endl;
				}
				
				if(Operator == '-')										
				{
					cout<<input<<subtraction(Operand1, Operand2)<<endl;
					output<<input<<subtraction(Operand1, Operand2)<<endl;
				}
				
				if(Operator == '/')										
				{
					cout<<input; 
					output<<input; Division(Operand1, Operand2);
				}
			}		
	}		
	return 0;	
}





	
