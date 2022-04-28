#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
//#include <cstring>
using namespace std;

void leer();
void crear();
void actualizar();
void eliminar();
void in_cod();
void traducir(string t);

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
			cout<<"Escriba el numero de la opcio que desea realizar:\n1. Ver listado de palabra\n2. Agregar palabras al listado\n3. Actualizar una palabra del listado\n4. Eliminar una palabra del listado\n5. Traductor de codigo fuente\n";
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
				in_cod(); break;
			default:
				cout<<"El numero seleccionado no es una opcion, vuelva a intentarlo";			
		}
		
			cout<<"\nDesea Realizar otra accion? (s/n): ";
			cin>>con;
	}while(con=='s'||con=='S');
	system("pause");
}

void leer(){
	system("cls");
	FILE* archivo=fopen(nom_arch,"rb");
	if(!archivo){
		archivo=fopen(nom_arch,"w+b");
	}
	Traductor traductor;
	int id_palabra=0;
	fread(&traductor,sizeof(Traductor),1,archivo);
	do{
		
		cout<<"id: "<<id_palabra<<endl;
		cout<<"\tIngles: "<<traductor.palabra<<endl;
		cout<<"\tEspanhol: "<<traductor.palabra_trad<<endl;
		cout<<"\t------Funcion------"<<endl;
		cout<<traductor.descripcion<<endl;
		cout<<"_____________________________________________________________________________________"<<endl;
		cout<<"_____________________________________________________________________________________"<<endl;
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
		cout<<"Ingrese la palabra en ingles: ";
		cin>>traductor.palabra;
		cout<<"Ingrese la palabra en espanhol: ";
		cin>>traductor.palabra_trad;
		cin.ignore();
		cout<<"Defina su funcion: ";
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
			cout<<"Ingrese la palabra en ingles: ";
			cin>>traductor.palabra;
			cout<<"Ingrese la palabra en espanhol: ";
			cin>>traductor.palabra_trad;
			cin.ignore();
			cout<<"Defina su funcion: ";
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

void in_cod(){
	string texto[100];
	cout<<"Ingrese texto a traducir, escriba '#@' para traducir:\n\n";
	for(int i=0;i<100;i++){
		getline(cin,texto[i]);
		if(texto[i]=="#@"){
			i=99;
		}
	}
	cout<<"____________________________________________________________"<<endl;
	cout<<"____________________________________________________________"<<endl;
	for(int i=0;i<99;i++){
		
		if(texto[i]=="#@"){
			i=99;
		}else{
		traducir(texto[i]);	
		}
		
	}
}

void traducir(string texto){
	
	FILE* archivo=fopen(nom_arch,"rb");
	if(!archivo){
		archivo=fopen(nom_arch,"w+b");
	}
	Traductor traductor;
	int id=0;
	
	fread(&traductor,sizeof(Traductor),1,archivo);
	do{
		id;
		string in(string(traductor.palabra));
		string espanol(string(traductor.palabra_trad));
		string::size_type pos=texto.find(in,0);
		
		if(pos<string::npos){
			texto.replace(pos,in.length(),espanol);	
		}
		fread(&traductor,sizeof(Traductor),1,archivo);
		id++;
	}while(feof(archivo)==0);
	
	fclose(archivo);
	cout<<texto<<"\n";
}

