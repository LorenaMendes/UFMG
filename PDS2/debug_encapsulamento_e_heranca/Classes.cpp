#include "Classes.hpp"

// ############################################# CLASSE BASE

void ClasseBase::set_public(int val){
	this->var_public = val;
}

int ClasseBase::get_public(){
	return this->var_public;
}

void ClasseBase::set_protected(int val){
	this->var_protected = val;
}

int ClasseBase::get_protected(){
	return this->var_protected;
}

void ClasseBase::set_private(int val){
	this->var_private = val;
}

int ClasseBase::get_private(){
	return this->var_private;
}

// ############################################# CLASSE A2

void A2::set_public2(int val){
	this->var_public2 = val;
}

int A2::get_public2(){
	return this->var_public2;
}

void A2::set_protected2(int val){
	this->var_protected2 = val;
}

int A2::get_protected2(){
	return this->var_protected2;
}

void A2::set_private2(int val){
	this->var_private2 = val;
}

int A2::get_private2(){
	return this->var_private2;
}

void A2::set_protected_base_a2(int var){
	this->var_protected = var;
}

int A2::get_protected_base_a2(){
	return this->var_protected;
}

void A2::set_public_base_a2(int var){
	this->var_public = var;
}

int A2::get_public_base_a2(){
	return this->var_public;
}

// ############################################# CLASSE A3

void A3::set_public3(int val){
	this->var_public3 = val;
}

int A3::get_public3(){
	return this->var_public3;
}

void A3::set_protected3(int val){
	this->var_protected3 = val;
}

int A3::get_protected3(){
	return this->var_protected3;
}

void A3::set_private3(int val){
	this->var_private3 = val;
}

int A3::get_private3(){
	return this->var_private3;
}

int A3::get_protected_a3_a2(){
	return this->var_protected2;
}

void A3::set_protected_a3_a2(int var){
	this->var_protected2 = var;
}

int A3::get_public_a3_a2(){
	return this->var_public2;
}

void A3::set_public_a3_a2(int var){
	this->var_public2 = var;
}

// ############################################# CLASSE PÚBLICA

void ClassePublica::set_public_public_base(int val){
	this->var_public = val;
}

int ClassePublica::get_public_public_base(){
	return this->var_public;
}

void ClassePublica::set_protected_public_base(int val){
	this->var_protected = val;
}

int ClassePublica::get_protected_public_base(){
	return this->var_protected;
}

// ############################################# CLASSE PRIVADA

void ClassePrivada::set_public_private_base(int val){
	this->var_public = val;
}

int ClassePrivada::get_public_private_base(){
	return this->var_public;
}

void ClassePrivada::set_protected_private_base(int val){
	this->var_protected = val;
}

int ClassePrivada::get_protected_private_base(){
	return this->var_protected;
}

// ############################################# CLASSE OVERLOAD

void OverloadPrivada::set_public(int val){
	this->var_public = val;
}

int OverloadPrivada::get_public(){
	return this->var_public;
}

void OverloadPrivada::set_protected(int val){
	this->var_protected = val;
}

int OverloadPrivada::get_protected(){
	return this->var_protected;
}

void OverloadPrivada::set_private(int val){
	this->var_private = val;
}

int OverloadPrivada::get_private(){
	return this->var_private;
}