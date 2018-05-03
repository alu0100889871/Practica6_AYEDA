#include "DNI.hpp"

DNI::DNI(long int dni): dni_(dni) {}

DNI::DNI(void){}
DNI::~DNI() {}

long int DNI::get_dni(void){
	return dni_;
}

void DNI:: set_dni(long int dni){
	dni_ = dni;
}

 int operator%( DNI& a, int tamanio){
	 return a.get_dni()% tamanio;
 }
 bool operator==( const DNI& a,  const int& b) {
	 long int a_= a.dni_;
	 return a_==b;
 }
 bool operator!=( DNI& a,  int& b){
	 return a.get_dni()!=b;
 }
 bool operator<( DNI& a,  int& b){
	 return a.get_dni()<b;
 }


int DNI::operator%( DNI& a){
	return dni_%a.dni_;
}
DNI& DNI::operator=(DNI Dni){
	dni_=Dni.dni_;
	return *this;
}

bool DNI::operator==( DNI& a){
	return dni_ == a.dni_;
}
bool DNI::operator!=( DNI& a){
	return dni_ != a.dni_;
}
bool DNI::operator<( DNI& a){
	return dni_ < a.dni_;
}
bool DNI::operator>( DNI& a){

	return dni_>a.dni_;
}

ostream& operator<<(ostream& os, DNI& Dni){
	os<<Dni.get_dni();
}
