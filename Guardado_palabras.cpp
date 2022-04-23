#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;

void leer();
void crear();
void actualizar();
void eliminar();
void traducir();

const char *nom_arch="archivo.dat";
const char *tem="temporal.dat";

struct Traductor{
	int n;
	char palabra[20];
	char palabra_trad[20];
	char descripcion[300];	
};

main(){
	int n=0;
	char con;
	string codigo;
	do{
			system("cls");
			cout<<"Escriba el numero de la opcio que desea realizar:\n1.Ver listado de palabra\n2.Agregar palabras al listado\n3.Actualizar listado de palabras\n4.Eliminar\n";
			cin>>n;
		switch(n){
			case 1:
				leer(); break;
			case 2:
				crear(); break;
			case 3:
				actualizar(); break;
			case 4:
				eliminar(); break;
			case 5:
				//cout<<"Ingresar codigo a traducir: ";
				//getline(cin,codigo);
				//cin.ignore();
				traducir();
				break;
			default:
				cout<<"El numero seleccionado no es una opcion, vuelva a intentarlo";			
		}
		
			cout<<"Desea Realizar otra accion? (s/n): ";
			cin>>con;
	}while(con=='s'||con=='S');
}

void leer(){
	system("cls");
	FILE* archivo=fopen(nom_arch,"rb");
	if(!archivo){
		archivo=fopen(nom_arch,"w+b");
	}
	Traductor traductor;
	int id_palabra=1;
	cout<<"id    |    palabra    |    palabra traducida    |    descripcion\n";
	fread(&traductor,sizeof(Traductor),1,archivo);
	do{
		cout<<id_palabra<<"     |    "<<traductor.palabra<<"   |    "<<traductor.palabra_trad<<"                |    "<<traductor.descripcion<<endl;

		fread(&traductor,sizeof(Traductor),1,archivo);
		id_palabra++;
	}while(feof(archivo)==0);
	fclose(archivo);
}

void crear(){
	FILE* archivo=fopen(nom_arch,"ab");
	char con;
	Traductor traductor;
	string descripcion;
	do{
		fflush(stdin);
		cout<<"Ingrese una plabra: ";
		cin>>traductor.palabra;
		cout<<"Ingrese su traduccion: ";
		cin>>traductor.palabra_trad;
		cin.ignore();
		cout<<"Ingrese su descripcion: ";
		getline(cin,descripcion);
		strcpy(traductor.descripcion,descripcion.c_str());
		fwrite(&traductor,sizeof(Traductor),1,archivo);
		cout<<"Desea agragar mas palabras? (s/n): ";
		cin>>con;
	}while(con=='s'||con=='S');
	fclose(archivo);
}

void actualizar(){
	FILE* archivo=fopen(nom_arch,"r+b");
	int id;
	char con;
	Traductor traductor;
	string descripcion;
	do{
		system("cls");
		leer();
		cout<<"\nIngrese el id de la palabra a modificar: ";
		cin>>id;
		fseek(archivo,id *sizeof(Traductor),SEEK_SET);
			cout<<"Ingrese una plabra: ";
			cin>>traductor.palabra;
			cout<<"Ingrese su traduccion: ";
			cin>>traductor.palabra_trad;
			cin.ignore();
			cout<<"Ingrese su descripcion: ";
			getline(cin,descripcion);
			strcpy(traductor.descripcion,descripcion.c_str());
			fwrite(&traductor,sizeof(Traductor),1,archivo);
		cout<<"Desea modificar mas palabras? (s/n): ";
		cin>>con;
	}while(con=='s'||con=='S');
	
	fclose(archivo);
}

void eliminar(){
 	
	FILE *archivo, *archivo_tem; 	
	Traductor traductor; 
	archivo_tem=fopen(tem,"w+b");
	archivo=fopen(nom_arch,"rb"); 

	leer();

	int id=1,i=1;
	cout<<"ingrese el id a eliminar:"; 
	cin>>id; 	                      				                
	                                                                                
	while(fread(&traductor,sizeof(Traductor),1,archivo)){ 	
	if (i != id){
	fwrite(&traductor,sizeof(Traductor),1,archivo_tem);
	} 
	i++;
	}
	fclose(archivo_tem); 
	fclose(archivo);                 
	archivo_tem=fopen(tem,"rb"); 
	archivo=fopen(nom_arch,"wb");
	while(fread(&traductor,sizeof(Traductor),1, archivo_tem)){ 
	fwrite(&traductor,sizeof(Traductor),1, archivo); 
	}
	                
	fclose(archivo_tem);
	fclose(archivo); 
	leer();	
}	

void traducir(){
	
	FILE* archivo=fopen(nom_arch,"rb");
	if(!archivo){
		archivo=fopen(nom_arch,"w+b");
	}
	Traductor traductor;
	int id=0;
	
	string texto,texto_salida;
	//texto_salida=text;
	
	cout<<"Ingrese texto a traducir:\n";
	getline(cin,texto_salida);
	cin.ignore();
	
	fread(&traductor,sizeof(Traductor),1,archivo);
	do{
		id;
		/*char ingles=lectura.palabra;
		char espanol=lectura.palabra_trad;*/
		/*int in_t=sizeof(lectura.palabra);
		int es_t=sizeof(lectura.palabra_trad);
		string in(in_t,lectura.palabra);
		string es(es_t,lectura.palabra_trad);*/
		//string::size_type pos=0;
		string in(string(traductor.palabra));
		string espanol(string(traductor.palabra_trad));
		/*string in=to_string(traductor.palabra);
		string espanol=to_string(traductor.palabra_trad);*/
		
		
	/*	int pos=in.length();
		
		size_t buscar =texto_salida.find(in);
		if(buscar!=string::npos){
			texto_salida.replace(buscar,pos,espanol);
		}*/
		
		
		/*while((pos=texto.find(in,pos))<string::npos){
			texto.replace(pos,in.length(),es);
			pos+=es.size();
		}*/
	//	texto_salida.replace(texto,in,es);
		string::size_type pos=texto_salida.find(in);
		if(pos<string::npos){
			texto_salida.replace(pos, in.length(),espanol);
		}
		
		
		fread(&traductor,sizeof(Traductor),1,archivo);
		id++;
	}while(feof(archivo)==0);
	fclose(archivo);
	cout<<texto_salida;
	//return texto_salida;
}

