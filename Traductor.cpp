#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;

const char* lec_arch="archivo.dat";

struct Lectura{
	char palabra[20];
	char palabra_trad[20];
};

int main(){
	FILE* archivo=fopen(lec_arch,"rb");
	if(!archivo){
		archivo=fopen(lec_arch,"w+b");
	}
	Lectura lectura;
	int id=1;
	
	string texto,texto_salida;
	
	
	cout<<"Ingrese texto a traducir:\n";
	getline(cin,texto);
	cin.ignore();
	
	fread(&lectura,sizeof(Lectura),1,archivo);
	do{
		id;
		/*char ingles=lectura.palabra;
		char espanol=lectura.palabra_trad;*/
		/*int in_t=sizeof(lectura.palabra);
		int es_t=sizeof(lectura.palabra_trad);
		string in(in_t,lectura.palabra);
		string es(es_t,lectura.palabra_trad);*/
		//string::size_type pos=0;
		string in(string(lectura.palabra));
		string espanol(string(lectura.palabra_trad));
		/*string in=to_string(lectura.palabra);
		string espanol=to_string(lectura.palabra_trad);*/
		
		/*int pos=in.length();
		
		size_t buscar =texto.find(in);
		if(buscar!=string::npos){
			texto.replace(buscar,pos,espanol);
		}*/
		string::size_type pos=texto_salida.find(in);
		if(pos<string::npos){
			texto.replace(pos, in.length(),espanol);
		}
		
		/*while((pos=texto.find(in,pos))<string::npos){
			texto.replace(pos,in.length(),es);
			pos+=es.size();
		}*/
	//	texto_salida.replace(texto,in,es);
		fread(&lectura,sizeof(Lectura),1,archivo);
		id++;
	}while(feof(archivo)==0);
	fclose(archivo);
	cout<<texto;
	
}