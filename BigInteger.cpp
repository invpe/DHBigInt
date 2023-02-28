#include "BigInteger.h"
using namespace std;

const string BigInteger::legalDigit = "0123456789-";

bool BigInteger::isLegal(){
	bool isLegal;
	if (str_int.length() == 1){
		isLegal = str_int.find_first_of(legalDigit.substr(0,legalDigit.length()-1)) != string::npos;
		return isLegal;
	}
	else{
		isLegal = true;
		isLegal &= (legalDigit.find(str_int.at(0))) != string::npos ;
		isLegal &= (str_int.substr(1).find_first_not_of(legalDigit.substr(0, legalDigit.length() - 1)) == string::npos);

		return isLegal;

	}
}

bool BigInteger::isZero(){

	
	if (str_int.find_first_not_of("0") == string::npos)
		return true;

	else if (str_int.at(0) == '-' && str_int.substr(1).find_first_not_of("0") == string::npos)
		return true;

		return false;
}

int BigInteger::cmp(const BigInteger& b) const{
	
	int thisLength = str_int.length();
	int cmpLength = b.GetInteger().length();

	if (thisLength > cmpLength) return 1;
	else if (thisLength < cmpLength) return -1;
	else {
		for (int i = 0; i < thisLength; i++){
			
			if (str_int.at(i) < b.GetInteger().at(i)) return -1;
			else if (str_int.at(i) > b.GetInteger().at(i)) return 1;
		}
		
		return 0;
	}
}

void BigInteger::simplifyZero(){
	unsigned int index = 0;
	string result = "";

	if (isZero()){
		str_int = "0";
		return ;
	}

	else if (str_int.at(0) == '-'){
		index = 1;
		result = "-";
		while (index < str_int.length() && str_int.at(index) == '0'){
			index++;
		}
		result.append(str_int.substr(index));
		str_int = result;

		return ;
	}
	else {
		index = 0;
		while (index < str_int.length() && str_int.at(index) == '0'){
			index++;
		}
		result = str_int.substr(index);
		str_int = result;

		return ;
	}
}


BigInteger::BigInteger(const BigInteger& b){
	str_int = b.GetInteger();
	simplifyZero();

}

BigInteger::BigInteger(const char* pstr):str_int(pstr){
	if (str_int.empty()){
		str_int = "0";
	}
	else if (!isLegal()){
		throw BigIntegerError("woot");
	}

	simplifyZero();
}

BigInteger::BigInteger(const string& str) :str_int(str){
	if (str_int.empty()){
		str_int = "0";
	}
	else if (!isLegal()){
		throw BigIntegerError("woot");
	}
	
	simplifyZero();
}


BigInteger BigInteger::addPos(const BigInteger& b) const{
	string result;
	int firstIndex = str_int.length() - 1;
	int secondIndex = b.GetInteger().length() - 1;

	int firstDigit, secondDigit;
	int sum = 0, carry = 0;

	while (firstIndex >= 0 && secondIndex >= 0){
		
		firstDigit = CHAR_TO_DIGIT(str_int.at(firstIndex));
		secondDigit = CHAR_TO_DIGIT(b.GetInteger().at(secondIndex));

		sum = (firstDigit + secondDigit + carry) % 10;
		carry = (firstDigit + secondDigit + carry) / 10;
		

		result.append(string(1,DIGIT_TO_CHAR(sum)));

		firstIndex--;
		secondIndex--;

	}

	while (firstIndex >= 0){
		if (carry != 0){
			firstDigit = CHAR_TO_DIGIT(str_int.at(firstIndex));
			sum = (firstDigit + carry) % 10;
			carry = (firstDigit + carry) / 10;
			
		}
		else{
			sum = CHAR_TO_DIGIT(str_int.at(firstIndex));
		}
		result.append(string(1, DIGIT_TO_CHAR(sum)));
		firstIndex--;
	}

	while (secondIndex >= 0){
		if (carry != 0){
			secondDigit = CHAR_TO_DIGIT(b.GetInteger().at(secondIndex));
			sum = (secondDigit + carry) % 10;
			carry = (secondDigit + carry) / 10;

		}
		else{
			sum = CHAR_TO_DIGIT(b.GetInteger().at(secondIndex));
		}
		result.append(string(1, DIGIT_TO_CHAR(sum)));
		secondIndex--;
	}

	if (carry != 0){
		result.append(string(1, DIGIT_TO_CHAR(carry)));
	}

	reverse(result.begin(), result.end());
	
	return BigInteger(result);
	
}



BigInteger BigInteger::subPos(const BigInteger& b) const{

	if (cmp(b) == 0){
		return BigInteger("0");
	}

	string result = "";
	int difference;
	int carry = 0;
	int firstIndex, secondIndex;
	int firstDigit, secondDigit;
	string firstNum, secondNum;

	if (cmp(b) == 1){
		firstNum = str_int;
		secondNum = b.GetInteger();
	}
	else if (cmp(b) == -1){
		firstNum = b.GetInteger();
		secondNum = str_int;
	}
	
	firstIndex = firstNum.length() - 1;
	secondIndex = secondNum.length() - 1;

	while (firstIndex >= 0 && secondIndex >= 0){
		
		firstDigit = CHAR_TO_DIGIT(firstNum.at(firstIndex));
		secondDigit = CHAR_TO_DIGIT(secondNum.at(secondIndex));

		difference = firstDigit - secondDigit - carry;
		
		if (difference < 0){
			difference += 10;
			carry = 1;
		}
		else {
			carry = 0;
		}

		result.append(string(1, DIGIT_TO_CHAR(difference)));
		
		firstIndex--;
		secondIndex--;

	}

	while (firstIndex >= 0){
		if (carry > 0){
			firstDigit = CHAR_TO_DIGIT(firstNum.at(firstIndex));
			difference = firstDigit - carry;
			
			if (difference >= 0) carry = 0;
			else {
				carry = 1;
				difference += 10;
			}

			result.append(string(1, DIGIT_TO_CHAR(difference)));
			
		}
		else{
			result.append(string(1, firstNum.at(firstIndex)));
			
		}
		firstIndex--;
	}

	reverse(result.begin(), result.end());

	if (cmp(b) == 1){
		return BigInteger(result);
	}
	else {
		return -BigInteger(result);
	}

}

BigInteger BigInteger::mulPos(const BigInteger& b) const{
	if (str_int == "0" || b.GetInteger() == "0"){
		return BigInteger("0");
	}

	BigInteger result("0");
	string temp_result;


	int carry = 0;
	int product = 0;
	int digit1, digit2;
	int multiplierIndex, multiplicandIndex;

	for (multiplierIndex = str_int.length() - 1; multiplierIndex >= 0; multiplierIndex--){
		temp_result = "";
		carry = 0;
		
		for (multiplicandIndex = b.GetInteger().length() - 1; multiplicandIndex >= 0; multiplicandIndex--){
			digit1 = CHAR_TO_DIGIT(str_int.at(multiplierIndex));
			digit2 = CHAR_TO_DIGIT(b.GetInteger().at(multiplicandIndex));

			product = (digit1 * digit2 + carry) % 10;
			carry = (digit1 * digit2 + carry) / 10;
			
			
			temp_result.append(string(1,DIGIT_TO_CHAR(product)));
		}
		
		if (carry != 0){
			temp_result.append(string(1,DIGIT_TO_CHAR(carry)));
		}
		reverse(temp_result.begin(), temp_result.end());

		temp_result.append(string(str_int.length() - 1 - (multiplierIndex) , '0'));
		
		result = result.addPos(BigInteger(temp_result));
	}
	result.simplifyZero();
	return result;

}

BigInteger BigInteger::divPos(const BigInteger& b)const{

	if (b.GetInteger() == "0"){
		throw BigIntegerError("Divisor cannot be zero!");
	}
	
	if (cmp(b) == 0){
		return BigInteger("1");
	}
	else if (cmp(b) == -1){
		return BigInteger("0");
	}
	else{
		int count = 0;
		BigInteger temp;
	    string remainder;
		int dividendIndex = 0;
		string result;
		while (dividendIndex < str_int.length() ){
			
			count = 0;
			remainder.append(string(1, str_int.at(dividendIndex)));
			
			if (BigInteger(remainder).cmp(b) < 0){
				
				result.append(string(1, DIGIT_TO_CHAR(count)));
				dividendIndex++;
				continue;
			}
			else{
				temp = BigInteger(remainder);
				while (temp.cmp(b) >= 0){
					count++;
					temp = temp.subPos(b);
				}
				remainder = temp.GetInteger();
				/*remainder.append(string(1, str_int.at(dividendIndex)));*/
				
			}
			
			result.append(string(1, DIGIT_TO_CHAR(count)));
			dividendIndex++;
			

		}
	
	

		return BigInteger(result);
	}
}


BigInteger BigInteger::modPos(const BigInteger& b) const{

	if (b.GetInteger() == "0"){
		throw BigIntegerError("Divisor cannot be zero!");
	}

	if (cmp(b) == 0){
		return BigInteger("0");
	}
	else if (cmp(b) == -1){
		return BigInteger(str_int);
	}
	else{
		int count = 0;
		BigInteger temp;
		string remainder;
		int dividendIndex = 0;

		while (dividendIndex < str_int.length()){

			count = 0;
			remainder.append(string(1, str_int.at(dividendIndex)));

			if (BigInteger(remainder).cmp(b) < 0){


				dividendIndex++;
				continue;
			}
			else{
				temp = BigInteger(remainder);
				while (temp.cmp(b) >= 0){
					count++;
					temp = temp.subPos(b);
				}
				remainder = temp.GetInteger();


			}

			dividendIndex++;
		}
		return BigInteger(remainder);
	}
}


BigInteger BigInteger::operator-()const{

	string result = str_int;

	if (result.at(0) == '-'){
		result.erase(0, 1);
	}
	else{
		result.insert(0, string(1, '-'));
	}
	return BigInteger(result);
}

BigInteger BigInteger:: operator =(const BigInteger& b){
	
	str_int.assign(b.GetInteger());
	
	return *this;
}

BigInteger BigInteger:: operator =(const string& str){
	
	if (!BigInteger(str).isLegal()){
		throw BigIntegerError("�Ƿ��ַ���");
	}

	str_int.assign(str);
	simplifyZero();

	return *this;

}

ostream& operator <<(ostream& os, BigInteger& b){
	return os << b.GetInteger();
}

istream& operator >>(istream& is, BigInteger& b){
	return is >> b.str_int;
}

BigInteger BigInteger::pow(const BigInteger& b) const{

	if (b.cmp(BigInteger("0")) < 0){
		throw BigIntegerError("The exp cannot be negative!");
	}

	BigInteger result("1");
	BigInteger count(b.GetInteger());

	string bi = "";
	BigInteger remainder;

	while (count.cmp(BigInteger("0")) > 0){

		remainder = count.modPos(BigInteger("2"));
		
		bi.append(string(1,remainder.GetInteger().at(0)));
		
		count = count.divPos(BigInteger("2"));
		
	}

	reverse(bi.begin(),bi.end());

	bool bitTrue;

	for (int i = 0; i < bi.length(); i++){
		
		result = result.mulPos(result);

		bitTrue = (bi.at(i) == '1');

		if (bitTrue)
		result = result.mulPos(str_int);

		

	}


	
	return result;

}

BigInteger BigInteger::powMod(const BigInteger& b, const BigInteger& m) const{

	if (b.cmp(BigInteger("0")) < 0){
		throw BigIntegerError("The exp cannot be negative!");
	}

	BigInteger result("1");
	BigInteger count(b.GetInteger());

	string bi = "";
	BigInteger remainder;

	while (count.cmp(BigInteger("0")) > 0){

		remainder = count.modPos(BigInteger("2"));

		bi.append(string(1, remainder.GetInteger().at(0)));

		count = count.divPos(BigInteger("2"));

	}

	reverse(bi.begin(), bi.end());

	bool bitTrue;

	for (int i = 0; i < bi.length(); i++){

		result = result.mulPos(result);

		result = result.modPos(m);

		bitTrue = (bi.at(i) == '1');

		if (bitTrue){
			result = result.mulPos(str_int);
			result = result.modPos(m);
		}


	}

	return result;

}


BigInteger operator + (const BigInteger& b1, const BigInteger& b2){
	bool isNeg1 = false, isNeg2 = false;
	BigInteger result;

	if (b1.GetInteger().at(0) == '-') isNeg1 = true;
	if (b2.GetInteger().at(0) == '-') isNeg2 = true;

	if (isNeg1 && isNeg2){
		result = -((-b1).addPos(-b2));
	}
	else if (!isNeg1 && !isNeg2){
		result = b1.addPos(b2);
	}
	else if (!isNeg1 && isNeg2){
		result = b1.subPos(-b2);
	}
	else if (isNeg1 && !isNeg2){
		result = b2.subPos(-b1);
	}

	return result;
}

BigInteger operator -(const BigInteger& b1, const BigInteger& b2) {

	bool isNeg1 = false, isNeg2 = false;
	BigInteger result;

	if (b1.GetInteger().at(0) == '-') isNeg1 = true;
	if (b2.GetInteger().at(0) == '-') isNeg2 = true;

	if (isNeg1 && isNeg2){
		result = (-b2).subPos(-b1);
	}
	else if (!isNeg1 && !isNeg2){
		result = b1.subPos(b2);
	}
	else if (!isNeg1 && isNeg2){
		result = b1.addPos(-b2);
	}
	else if (isNeg1 && !isNeg2){
		result = -((b2).addPos(-b1));
	}

	return result;

}

BigInteger operator *(const BigInteger& b1, const BigInteger& b2) {

	bool isNeg1 = false, isNeg2 = false;
	BigInteger result;

	if (b1.GetInteger().at(0) == '-') 
		isNeg1 = true;
	if (b2.GetInteger().at(0) == '-') 
		isNeg2 = true;

	if (isNeg1 && isNeg2){
		result = (-b2).mulPos(-b1);
	}
	else if (!isNeg1 && !isNeg2){
		result = b1.mulPos(b2);
	}
	else if (!isNeg1 && isNeg2){
		result = -(b1.mulPos(-b2));
	}
	else if (isNeg1 && !isNeg2){
		result = -(b2.mulPos(-b1));
	}

	return result;

}


BigInteger operator /(const BigInteger& b1, const BigInteger& b2) {

	bool isNeg1 = false, isNeg2 = false;
	BigInteger result;

	if (b1.GetInteger().at(0) == '-') isNeg1 = true;
	if (b2.GetInteger().at(0) == '-') isNeg2 = true;

	if (isNeg1 && isNeg2){
		result = (-b1).divPos(-b2);
	}
	else if (!isNeg1 && !isNeg2){
		result = b1.divPos(b2);
	}
	else if (!isNeg1 && isNeg2){
		result = -(b1.divPos(-b2));
	}
	else if (isNeg1 && !isNeg2){
		result = -((-b1).divPos(b2));
	}

	return result;

}

BigInteger operator % (const BigInteger& b1, const BigInteger& b2){
	bool isNeg1 = false, isNeg2 = false;
	BigInteger result;

	if (b1.GetInteger().at(0) == '-') isNeg1 = true;
	if (b2.GetInteger().at(0) == '-') isNeg2 = true;

	if (isNeg2){
		throw BigIntegerError("w00t");
	}

	else if (isNeg1){
		result = b2.subPos((-b1).modPos(b2));
	}

	else if (!isNeg1){
		result = b1.modPos(b2);
	}


	return result;
}

BigInteger operator ^ (const BigInteger& b1, const BigInteger& b2){

	BigInteger result;

	try{
		result = b1.pow(b2);
		
		return result;
	}
	catch (BigIntegerError e){
		cerr << "Runtime error : " << e.what() << endl;
	}

}


int CHAR_TO_DIGIT(char x){

	return  (int)x - 0x30;

}

char DIGIT_TO_CHAR(int x){

	return (char)(x + 0x30);

}