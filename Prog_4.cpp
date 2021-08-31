
//*********************************************************************************************************************************
//       Author:            Shruti Manikrao Basutkar
//       Creation Date:     11/07/2019
//       Modification Date: 11/24/2019
//       Purpose:           This program is performs following arrithmatic operations:   
//							Addition(+), Subtraction (-), Multiplication(*), Division(/) and Power($) on hexadecimal oeprands.
//       Description:       Five separate function are created for each of above specified operations i.e
//							"string Addition(string& Operand1, string& Operand2)", "string Mul(string& Operand1, string& Operand2)", 
//							"string subtraction(string& Operand1, string& Operand2)", void Division(string& Operand1, string& Operand2), 
//							and "string Power(string& Operand1, string& Operand2)". 
//							
//							The program receives input file and output file while executing program. This input file contains
//							few examples to test the arithmatic operations. 
//			
//							The output file will store the result of the examples in the input text file. 
//							 
//							The "fstream" header file is used for input and output filestream.
//*********************************************************************************************************************************

#include<iostream>		// preprocessor directive required for input and output
#include<string>        // Declare String type variable
#include<cstring>		// Perform operation on C-style string
#include<sstream>		// perform various operation on string object
#include <cstdlib>      // For converting to integer function atoi
#include<fstream>  		// Required for file function
#include<cmath>
using namespace std;	// ”using” directive

ofstream output; 		// Output of arithmatic operation on input file will store in output file

/***************************************************************************************************
*int HexToDec(char digit):
*Purpose: This function is use to convert single digit from Hexdecimal to Decimal. It has been used in 
*		  following functions to perform arithmatic operation digit by digit.
***************************************************************************************************/
int HexToDec(char digit)
{
	int hex;
	if((int) digit >= 48 && (int) digit <= 57)		// Check if char value is in the range of 48 to 57 (According to ASCII data)
		hex = (int)digit -48;  						// Subtracting 48 from the Char value to convert into corresponding Decimal value   
	else if ((int)digit >= 65 && (int)digit <= 70)	// Check if the char value is in the range of 65 to 70
		hex = (int)digit - 55;						// Subtracting 55 from the Char value to convert into corresponding Decimal value 
	
	return hex;
}

/***************************************************************************************************
*void makeSameOperandLength(string& Operand1, string& Operand2):
*Purpose: This function will help to make same length of two passing string parameters.
*		  This is require in the following arithmatic functions to perform arithmatic operation on 
*		  hexadecimal values.
* Description: This is a function, takes two passing arguments of string data type. Function will 
*			   check length of each passing arguments, if length of one of the argument is less 
*   		   than other, then it will make it same length as other argument by padding leading zeroes
*			   to it. Number of zeroes to be padded is equal to difference between lengths of 
* 			   two arguments which calculated and stored "int lenDiff" 
***************************************************************************************************/
void makeSameOperandLength(string& Operand1, string& Operand2)
{
	int MaxOpLen;									// To store Maximum Operand length 
	int MinOpLen;									// To store Minimum Operand length 
	
	if(Operand1.length() >= Operand2.length())		// Check if Operand1 length is greater or equal
	{
		MaxOpLen = Operand1.length();				// Then MaxOpLen will same as Operand1 length
		MinOpLen = Operand2.length();				// and MinOpLen will same as Operand2 length
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
	int lenDiff;									// difference between to operand length
	lenDiff = MaxOpLen - MinOpLen;	
	
	if(Operand1.length() >= Operand2.length())		
		Operand2.insert(0, lenDiff, '0');			 
	else
		Operand1.insert(0, lenDiff, '0');
}
/***************************************************************************************************
*string Addition(string& Operand1, string& Operand2)):
*Purpose: This function performs "Addition (+)" arithmatic operation digit by digit.
*Description: This Funtion will takes two string arguments as passing paramenteres and returns string
*			  as a result. Addition performed one digit at a time. For this, each digit first get converted 
*			  into decimal, after addition each get stored in array of char "Sum[]".
*			  After addition on all digits presented in operands, all character in array Sum will get 
* 			  converted into corresponding Hex value.  Finally each char in Sum[] append to 
*             "SumString" to store final value. 
***************************************************************************************************/
string Addition(string& Operand1, string& Operand2)
{
	makeSameOperandLength(Operand1, Operand2);		// Makes two operands length equal
	
	int Len = Operand1.length();					
	char Sum[Len];									// to store char after each digit's addition
	string SumString;								// to return final result as string
	int CarryBit = 0;								// CarryBit is zero initially
	int Op1Digit;									// to store one digit of Operand1
	int Op2Digit;									// to store one digit of Operand2
	
	for(int i=(Len-1);  i >= 0; --i)             	// to perform addition on each digits of operands 
	{												// from LSB to MSB
		Op1Digit = HexToDec(Operand1[i]); 			// to perform addition, converted each digit of operands
		Op2Digit = HexToDec(Operand2[i]);			// into corresponding decimal
		
		int temp;
		temp = Op1Digit + Op2Digit + CarryBit;		// stores addition in "temp"
		if(temp >= 16)								// compares "temp" with 16 to get corresponding hex value
		{
			Sum[i] = temp - 16;
			CarryBit = 1;							// CarryBit will be generated if addition
		}											// is greater than 16
		else 
		{
			Sum[i] = temp;							// if addition is less than 16, no carryBit will be generated
			CarryBit = 0;
		}
	}	
	
	if(CarryBit == 1)								// if carrybit is present,then it added to the final result 
		SumString = SumString + '1';
		
	for (int i=0; i < Len; i++)						// each char in "Array Sum[]" has
	{												// corresponding hex value
		if(Sum[i] < 10)
			Sum[i] += 48;
		else
			Sum[i] += 55;
		SumString = SumString + Sum[i];				// each char in Sum[] gets appended to the Sumstring one by one
	}		
	return SumString;								// returns final result in hex
}
/***************************************************************************************************
*string Mul(string& Operand1, string& Operand2):
*Purpose: This function performs "Multiplication (*)" arithmatic operation digit by digit.
*Description: This Funtion will takes two string arguments as passing paramenteres and returns string
*			  as a result. Multiplication performed one digit at a time. Each digits of operand2 from
* 			  LSB to MSB multiply operand1. "int zeroCount" is used to pad zeroes to the result of 
* 			  after each multiplication of Operand2's digit with Operand1. The result after these 
*			  multiplication stored in array Mul[]. Final multiplication will get By adding all 
* 			  elements in Mul[] array.
***************************************************************************************************/
string Mul(string& Operand1, string& Operand2)
{
	int Op2Len = Operand2.length();					// to store Operand2 length 
	int Op2Digit;
	int zeroCount = 0;								// after each multiplication of operand2 digit's, no. of zeroes get padded to multiplication answer
	string MulFinal;								// to store final result in MulFinal string
	string Mul[Op2Len];								// to store multiplication result after each of operand2 digit
	
	if (Operand2 == "0")							
		return "0";
	
	for(int i = Op2Len-1; i >= 0; --i)				// each digit of operand2 from LSB to MSB multiplies to operand1 
	{
		Op2Digit = HexToDec(Operand2[i]);			// convert hex char of operand2's digit into decimal
		for(int j=1; j <= Op2Digit ; j++)			// addition will be performed for operand2's digit times
			Mul[i] = Addition(Mul[i], Operand1);	// call Addition function for adding operand1 with itself
		
		for(int n = 0; n < zeroCount; n++)			// after each addition, no. of zeroes as per zerocount are padded with result
			Mul[i] = Mul[i] + '0';
			
		zeroCount ++;								// zerocount increases by one after each multiplication 
	}
	for(int i=0; i < Op2Len; i++)					// all results stored in array Mul[] are added together
	MulFinal = Addition(MulFinal, Mul[i]);			
	
	return MulFinal;								// returns final result of string
}
/***************************************************************************************************
*string Power(string& Operand1, string& Operand2):
*Purpose: This function performs "Power ($)" arithmatic operation digit by digit.
*Description: This Funtion will takes two string arguments as passing paramenteres and returns string
*			  as a result. Power operation performs multiplication by operand2 times. 
***************************************************************************************************/
string Power(string& Operand1, string& Operand2)
{
	int Len = Operand2.length();
	int powNo = HexToDec(Operand2[Len-1]);			// to store operand2 digit 
	string PowerAns= "1";							// to store final result of power
	
	for(int i=1; i<= powNo; i++)					// multiplication performed for operand2 digits times
	{
		PowerAns = Mul(Operand1, PowerAns);			// calls Multiplication function
	}
	
	return PowerAns;								// returns final result
}

/***************************************************************************************************
*string Compliment(string& Operand1):
*Purpose: This function performs "16's compliment", which we will use in Subtraction function.
**Description: This Funtion will takes one string arguments as passing paramentere and returns string
*			   as a result. 
***************************************************************************************************/
string Compliment(string& Operand1)
{
	int OpLen = Operand1.length();					// to store length of operand
	int OpDigit;									// to store decimal value of each digit in operand
		
	char ComplimentChar[OpLen];						// to store char value in the array
	string ComplimentStr;							// to store final result of the compliment function
	
	// get 15's compliment of operand
	for(int i = OpLen-1; i >= 0; --i)				// Each digits of operand from LSB to MSB subtracted by 15	
	{												
		OpDigit = HexToDec(Operand1[i]);			
		ComplimentChar[i] = 15 - OpDigit;			// stores each char into to ComplimentChar[]
	}

	for(int i=0; i<OpLen; i++)						// converting decimal value into corresponding Hex value
	{
		if(ComplimentChar[i] < 10)
			ComplimentChar[i] += 48;
		else
			ComplimentChar[i] += 55;
		
		ComplimentStr = ComplimentStr + ComplimentChar[i];	// stores in string format
	}
	
	string one = "1";								// adding 1 to 15's compliment using addition function
	ComplimentStr = Addition(ComplimentStr, one );	
	
	return ComplimentStr;							// returns 16's compliment of operand
}

/***************************************************************************************************
*string subtraction(string& Operand1, string& Operand2):
*Purpose: This function performs "subtraction (-)" arithmatic operation digit by digit.
*Description: This Funtion will takes two string arguments as passing paramenteres and returns string
*			  as a result. For subtraction, Operand2's 16's complimented added with operand1.
***************************************************************************************************/
string subtraction(string& Operand1, string& Operand2)
{
	string SubString;									// to store final result 
	
	int Len;										
	makeSameOperandLength(Operand1, Operand2);			// Makes two operands lengths equal
	
	Len = Operand1.length();							// length of operands
	string Operand2Compli;								// to store compliment of operand2
	Operand2Compli = Compliment(Operand2);				// calling Compliment() function
	
	SubString = Addition(Operand1, Operand2Compli);		// addition of operand 1 with compliment of operand2
	
	if (SubString.length() != Len)						//discard carryBit at the end of subtraction
		SubString.erase(SubString.begin() + 0);
		
	return SubString;									// return  subtraction of two operands
	
}

/***************************************************************************************************
*void Division(string& Operand1, string& Operand2):
*Purpose: This function performs "Division (/)" arithmatic operation digit by digit.
*Description: This Funtion will takes two string arguments as passing paramenteres and displays 
*			  quotient and reminder as a result.
***************************************************************************************************/
void Division(string& Operand1, string& Operand2)
{
	string counter = "0";								// counter will count no. of subtraction
	string one = "1";									// will use for counter increment 							
	string remainder;									// stores remainder		
	string quotient;									// stores quotient
	
	makeSameOperandLength(Operand1, Operand2);			// Makes two operands length equal
	
	while(Operand1 >= Operand2)							// performs subtration till operand1 is greater than operand2
	{
		Operand1 = subtraction(Operand1, Operand2);		
		counter = Addition(counter, one);				// counter increment by 1		
	}
	remainder = Operand1;								// final operand1 after while loop will be remainder
	quotient = counter;									// counter gives quotient after while loop
			
	cout<<"quotient "<<quotient<<", "<<"remainder "<<remainder<<endl;		// prints final result on console
	output<<"quotient "<<quotient<<", "<<"remainder "<<remainder<<endl;		// prints final result in output file
}

/***************************************************************************************************
*int main(int argc, char** argv):
*Purpose: Main() function will test all arithmatic operation created in this program.
*Description: The main() function will take two "txt" file, one for read testdata and other for to 
*         	  display output during execution of program.         
***************************************************************************************************/
int main(int argc, char** argv){
	fstream myFile;                                                     // Create object of type fstream class	
	myFile.open(argv[1]);                                          		// open file input file
	output.open(argv[2]);												// open output file
	if(!myFile)                                                         // Error checker if file not exit
		cout<<"Error while opening File: "<<argv[1]<<endl;
    else                                                                // if file exist
	{  
		cout<<"\nFile open successfully here is the result: " <<endl;   // Prompt messege for successful opening of file		
		string input;													// reads line as input from file
		string Operand1;												// stores operand1 from input line
		string Operand2;												// stores operand2 from input line
		int operatorPlace;												// finds out operator place in input line					
		int len;														// length of input line													
		char Operator;													// stores operator char i.e "+" or "-" or "*" or "$" or "/"
		
			while(getline(myFile, input))                               // file read line by line	
			{
				len = input.length();									// total length of input line
				
				for(int i=0; i<=len; i++)								// checks operator in input line
				{
					if((input[i] == '+') || (input[i] == '-') || (input[i] == '*') ||(input[i] == '/') || (input[i] == '$'))
					{
						operatorPlace = i;
						Operator = input[i];
						
						break;											// if operator found come out from loop
					}				
					if(i==len)
						cout<<"\nNo Operator here."<<endl;		
				}	
				
				stringstream ss(input);									// stringstream object use to split input line 
				getline(ss, Operand1,Operator);							// separates operand1 from input line
				getline(ss, Operand2,'=');								// separates operand2 from input line
				
				if(Operator == '+')										// if operator is "+" perform addition by calling Addition() 
				{
					cout<<input<<Addition(Operand1, Operand2)<<endl;
					output<<input<<Addition(Operand1, Operand2)<<endl;					
				}
				
				if(Operator == '*')										// if operator is "*" perform Multiplication by calling Mul()
				{
					cout<<input<<Mul(Operand1, Operand2)<<endl;
					output<<input<<Mul(Operand1, Operand2)<<endl;
				}
				
				if(Operator == '$')										// if operator is "$" perform power operation by calling Power()
				{
					cout<<input<<Power(Operand1, Operand2)<<endl;
					output<<input<<Power(Operand1, Operand2)<<endl;
				}
				
				if(Operator == '-')										// if operator is "-" perform subtraction by calling subtraction()
				{
					cout<<input<<subtraction(Operand1, Operand2)<<endl;
					output<<input<<subtraction(Operand1, Operand2)<<endl;
				}
				
				if(Operator == '/')										// if operator is "/" perform Division by calling Division()
				{
					cout<<input; 
					output<<input; Division(Operand1, Operand2);
				}
			}		
	}		
	return 0;	
}





	