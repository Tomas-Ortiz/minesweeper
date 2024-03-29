#include <iostream>  //Liberaria para utilizar entrada y salida de datos (cout y cin)
#include <stdlib.h>    //Libreria para ejecutar comando externo(system)
#include <time.h>  //Libreria para la funci�n aleatoria

void titulo();
void nombre(char usuario[]);
void ingresobomba(int *nbombas);         //Declaraci�n
void limpiarmatriz(int tablero[][10], int aux[][10], int aux2[][10]);
void generarbomba(int tablero[][10], int nbombas);       //Prototipos de los subprogramas utilizados
void jugada(int aux[][10], int *x, int *y, int *njugadas, int *puntaje, int nbombas);//las variables que est�n acompa�adas de asteriscos se pasan por referencia
void establecernum(int tablero[][10]);
void tablero1(int tablero[][10], int aux[][10], int x, int y);
void ganarperder(int tablero[][10], int x, int y, int njugadas, int nbombas, int *ganados, int *perdidos, int destapados);
void informacion();
void menu(int *opcion);
void partidas(char usuario[], int perdidos, int ganados, int puntaje);
void destaparadyac(int aux[][10], int x, int y);
void destapadas(int aux[][10], int x, int y, int *destapados, int aux2[][10]);


using namespace std;       //Para pasar un arreglo bidimensional como par�metro se necesita especificar el tama�o de la segunda dimensi�n

int main(){  //PROGRAMA PRINCIPAL
	
int tablero[10][10],aux[10][10],x,y,nbombas=0,bombas=9,njugadas=0,puntaje=0,ganados=0,perdidos=0,jugar=0,opcion,destapados=0, aux2[10][10];
char usuario[50];               

do{

menu(&opcion);


switch(opcion)
{
	case 1: 
system("cls");
	
	do{
	
titulo();
nombre(usuario);
ingresobomba(&nbombas);  
limpiarmatriz(tablero, aux, aux2);  //En cada inicio del bucle se reinicia el tablero
generarbomba(tablero, nbombas);        //Llamada a los subprogramas	//Estos subprogramas se repiten una vez, ya que no est�n adentro del ciclo
establecernum(tablero);

njugadas=0;   		//Al iniciar el bucle se reinicia el num de jugadas y el puntaje
puntaje=0;
x=-4;
y=-4;    //Se borra registro de la �ltima casilla seleccionada, y se dan las coordenadas (-4, -4) para evitar que coincida con alguna casilla del tablero
destapados=0;  //Se reinicia las casillas destapadas para volver a jugar

while(tablero[x][y]!=bombas || destapados!=(64-nbombas)) //los subprogramas seleccionadas se encuentran en un ciclo while para repetirlos cierta cantidad de veces
{
titulo();  
tablero1(tablero, aux, x, y);
destapadas(aux, x, y, &destapados, aux2); 
ganarperder(tablero, x, y, njugadas, nbombas, &ganados, &perdidos, destapados);	 //las variables que est�n acompa�adas con andpersand se pasan por referencia	 //Se revisa la cantidad de casillas destapadas (aux[i][j]=1)

if(tablero[x][y]==bombas || destapados==(64-nbombas))     //si pierde o gana se muestra partidas, sino sigue jugando      
	{	
	partidas(usuario, perdidos, ganados, puntaje);	
	break;
	}
	else
	{
		jugada(aux, &x, &y, &njugadas, &puntaje, nbombas);  
	}
}

cout<<"�Desea volver a jugar?"<<endl;
cout<<"\n"<<"5. Si."<<endl;
cout<<"6. No."<<endl;
cout<<"\n"<<"Opcion: ";
cin>>jugar;

while(!cin)
{
	cin.clear();
	cin.ignore();
	cin>>jugar;
}

system("cls");

}while(jugar!=6);
	
	case 2:
		system("cls");	

		informacion();
		break;
		
	case 3:
		
	break;
		
		default:
			cout<<"\n"<<"Opcion no valida."<<endl;
}

}while(opcion!=3);

return 0;
}

void titulo()
	{
cout<<"                    *----------------------------------*"<<endl;               
cout<<"                  	  *----------------------*"<<endl;
cout<<"                                 BUSCAMINAS"<<endl;                    
cout<<"                 	  *----------------------*"<<endl;
cout<<"                    *----------------------------------*"<<endl;
cout<<" "<<endl;	
	}

void nombre(char usuario[])
{
	cout<<"\n"<<"\t"<<"Nombre del jugador: ";
	cin>>usuario;
}

void ingresobomba(int *nbombas)				//Se pasa por referencia para mantener el valor durante la ejecuci�n de otros subprogramas
	{

cout<<"\n"<<"\t"<<"Ingrese cantidad de bombas (1 - 64): ";           //Cantidad de bombas que ingresa el usuario con las que desea jugar

do{
cin>>*nbombas;               

if(*nbombas<1 || *nbombas>64)              
{
	cout<<"\n"<<"Ingrese un numero valido. "<<endl;	
}

while(!cin) //Condicion para evitar que el usuario ingrese otro tipo de dato diferente al entero
{
	cout<<endl<<"\n"<<"Ingrese un numero entero: ";  //Si ingresa un tipo de dato diferente entonces entra en el ciclo while
	cin.clear();       
	cin.ignore(); 	//Limpia el contenido basura en el buffer de entrada e ignora los caracteres  y lo vuelve a pedir mientras sea diferente a entero
	cin>>*nbombas;	
}

}while(*nbombas<1 || *nbombas>64);  //Hacer mientras no cumpla con los requisitos

system("cls");    //Limpiar pantalla para la siguiente ejecuci�n

	}
		
void generarbomba(int tablero[][10], int nbombas)
	{	
	int i,j,p;
	
	srand(time(NULL));       //Inicializa el generador de n�meros aleatorios diferentes en cada ejecuci�n
	
for(p=0;p<nbombas;p++)     //Repetir hasta la cantidad de bombas ingresadas      
{
	int bombas=9;
do{
	i = 1+rand()%8;					//generar bombas de forma aleatoria, dandole un valor aleatorio a "x" e "y" entre 1 y 8
	j = 1+rand()%8;
	
}while(tablero[i][j]==bombas);  //Control para que no se repitan las coordenadas para colocar bomba
								//Si en una coordenada generada de forma aleatoria ya existe bomba entonces genera otras 
	tablero[i][j]=bombas;	//Esa posici�n generada equivale a una bomba(9)
}
	}
	
void limpiarmatriz(int tablero[][10], int aux[][10], int aux2[][10])
	{
		int i,j,bombas=9;                //La variable bomba se identifica con el n�mero 9

for(i=1;i<9;i++)
{
	for(j=1;j<9;j++)
	{      					//Limpiar matrices para reiniciar el tablero
		tablero[i][j]=0; 
		              
		aux[i][j]=0;	//Matriz auxiliar para marcar las casillas destapadas
		
		aux2[i][j]=0;		//Matriz auxiliar para marcar las casillas revisadas 
	}
}

	}
	
void jugada(int aux[][10], int *x, int *y, int *njugadas, int *puntaje, int nbombas)
	{

	do
	{		
cout<<"----------------------------------------------"<<endl;
cout<<" Puntos: "<<*puntaje<<endl;
cout<<" Jugadas: "<<*njugadas<<endl;
cout<<" Bombas: "<<nbombas<<endl;                            //Interfaz del usuario
cout<<"------------------"<<endl;
cout<<"Jugada: "<<endl;
cout<<"------------------"<<endl;                     
cout<<"Ingrese fila: ";           
cin>>*x; 

while(!cin)
{
	cout<<"Ingrese un numero entero: "<<endl;
	cin.clear();
	cin.ignore();
	cin>>*x;
}                                    //Usuario ingresa fila(x) y columna(y) para seleccionar la casilla correspondiente al tablero
cout<<"Ingrese columna: ";
cin>>*y;	

while(!cin)
{
	cout<<"Ingrese un numero entero: "<<endl;
	cin.clear();
	cin.ignore();
	cin>>*y;
} 

if((*x>1 && *x<9) && (*y>1 && *y<9) && (aux[*x][*y]!=1))
{
	*njugadas=*njugadas+1;
	*puntaje=*puntaje+10;        //Se incrementa las veces jugadas y el puntaje cada vez que el usuario juega y cumple las condiciones
}
		else
	{		
	cout<<"\n"<<"Ingrese numeros validos."<<endl;
	cout<<" "<<endl;
	}
		
}while((*x<1 || *x>9) || (*y<1 || *y>9));  //Hacer mientras no ingrese n�meros que se salgan de la matriz

aux[*x][*y]=1;       //Matriz l�gica usada para marcar una casilla destapada, dicha casilla se identifica con el valor 1

system("cls"); //Se limpia la pantalla cada vez que el usuario juega
	
	}

void establecernum(int tablero[][10])	
	{
	int i,j,num,bombas=9;
	
for(i=1;i<9;i++)
{
	for(j=1;j<9;j++)
	{
			num = 0;  //El valor de num se reinicia en cada iteraci�n para asignarle el nuevo valor a la casilla siguiente
			
	if (tablero[i][j]!=bombas)        //Si en la casilla no existe bomba entonces se coloca un numero dependiendo de la cantidad de bombas alrededor
			{
        if (tablero[i+1][j]==9) 
			num++;
        if (tablero[i][j+1]==9) 
			num++;
        if (tablero[i-1][j]==9) 
			num++;
        if (tablero[i][j-1]==9) 
			num++;                        //Contar bombas en casillas adyacentes para asignarle el valor a dicha casilla
        if (tablero[i+1][j+1]==9) 
			num++;
        if (tablero[i-1][j-1]==9) 
			num++;
        if (tablero[i-1][j+1]==9) 
			num++;
        if (tablero[i+1][j-1]==9) 
			num++;
        tablero[i][j]=num;
			}      			 //Almacena todos los numeros en la matriz		
		}
	}
}

void tablero1(int tablero[][10], int aux[][10], int x, int y)
	{
	int i,j,bombas=9;
	
cout<<"----------------------------------------------"<<endl;
cout<<" [X] ";
for(j=1;j<9;j++)
{
cout<<"[ "<<j<<" ]";
}
cout<<endl<<"----------------------------------------------"<<endl;        //generar tablero


for(i=1;i<9;i++)
 {   
    	
  cout<<"[ "<<i<<" ]";

	for(j=1;j<9;j++)
	{
				
	if(tablero[x][y]==0)   //Si la posici�n seleccionada contiene el valor cero entonces..
	{
		destaparadyac(aux, x, y);	//Se marcan las casillas adyacentes como destapadas para que abajo las mismas se muestran
	}							//Se coloca fuera del condicional para que itere desde el principio
	
		if(x==i && y==j)           //entra en el condicional si la casilla seleccionada equivale a la posicion del tablero
		{	
		  if(tablero[i][j]==bombas)                  //Si en la casilla hay bomba se muestra un asterisco
			{
				cout<<" "<<" * "<<" ";
			}
			
				if(tablero[i][j]!=bombas)    //Si en la casilla no hay bomba entonces se muestra el numero correspondiente(i,j)
				{
					cout<<"  "<<tablero[i][j]<<"  ";				
				}
		
		}

		 else if(aux[i][j]==1) 	//Si la casilla del tablero fue destapada entonces la misma se muestra de forma permanente en el tablero
				{
					cout<<"  "<<tablero[i][j]<<"  ";  							  						
				}
				
			else
					{
						cout<<" "<<" - "<<" ";         //Si la casilla no fue destapada (!=1) entonces se mantiene tapada(-)
					}
					
	}
		cout<<endl;			   
}
	}

void ganarperder(int tablero[][10], int x, int y, int njugadas, int nbombas, int *ganados, int *perdidos, int destapados)
	{
	int i,j,bombas=9;
	
 if(tablero[x][y]==bombas)                //Si el usuario ingresa una casilla que contiene bomba entonces pierde
{
	*perdidos=*perdidos+1;
	cout<<"    --------------------------------------------"<<endl;
	cout<<"\n"<<"\t"<<"\t"<<"OH, HAS PERDIDO :( !"<<endl;
	cout<<" "<<endl;
	cout<<"    --------------------------------------------"<<endl;
	
cout<<endl<<"SOLUCION: "<<endl;	           //Si pierde entonces se muestra la soluci�n, es decir, la matriz destapada
cout<<"----------------------------------"<<endl;
cout<<" "<<endl;

	for(i=1;i<9;i++)                      
	{
		for(j=1;j<9;j++)
		{
			if(tablero[i][j]==bombas)
			{
				cout<<" "<<" * "<<" ";             //tablero mostrado despues de perder
			}
			else if(tablero[i][j]!=bombas) 
			{
				cout<<"  "<<tablero[i][j]<<"  ";
			}
		}
	cout<<endl;
	}
}

else if(destapados==(64-nbombas))     //Condicion para ganar
		{
			*ganados=*ganados+1;
	cout<<"	    --------------------------------------------"<<endl;
	cout<<"\n"<<"\t"<<"\t"<<"�FELICIDADES, HAS GANADO LA PARTIDA!"<<endl;
	cout<<"  "<<endl;
	cout<<"	    --------------------------------------------"<<endl;
		}
	}
	
void informacion()
{
cout<<"\n"<<"\t"<<"\t"<<"#Codigo desarrollado por Tomas Ortiz."<<endl;
cout<<"\t"<<"\t"<<"#Licenciatura en Informatica y desarrollo de software."<<endl;
cout<<"\t"<<"\t"<<"#Version del juego: 1.0"<<endl;
}

void menu(int *opcion)
{
cout<<"\n"<<"\t"<<"\t"<<"\t"<<"\t"<<"MENU"<<endl;
cout<<"\t"<<"\t"<<"\t"<<"--------------------------"<<endl;
cout<<"\t"<<"\t"<<"\t"<<"1. Iniciar partida"<<"\n"<<endl;
cout<<"\t"<<"\t"<<"\t"<<"2. Informacion"<<"\n"<<endl;
cout<<"\t"<<"\t"<<"\t"<<"3. Salir"<<"\n"<<endl;
cout<<"\n"<<"Opcion: ";
cin>>*opcion;
	
while(!cin)
{
	cin.clear();
	cin.ignore();
	cin>>*opcion;
}

}

void partidas(char usuario[], int perdidos, int ganados, int puntaje)
{
	cout<<"\n"<<"----------------------------------"<<endl;
	cout<<"Jugador: "<<usuario<<endl;
	cout<<"Puntaje obtenido: "<<puntaje<<endl;
	cout<<"Partidas ganadas: "<<ganados<<endl;
	cout<<"Partidas perdidas: "<<perdidos<<endl;
	cout<<"----------------------------------"<<endl;	
}

void destaparadyac(int aux[][10], int x, int y)
{
							
				aux[x-1][y-1]=1;           //8 casillas alrededor de la seleccionada
				
				aux[x-1][y]=1;

				aux[x-1][y+1]=1;			//Las casillas alrededores se marcan como ya destapadas (1) para que en tablero1 las mismas se muestren

    			aux[x][y-1]=1;

				aux[x][y+1]=1;

				aux[x+1][y-1]=1;

				aux[x+1][y]=1;

				aux[x+1][y+1]=1;
				
}

void destapadas(int aux[][10], int x, int y, int *destapados, int aux2[][10])
{
int i,j;

for(i=1;i<9;i++)
{
	for(j=1;j<9;j++)
	{				
		if(aux[i][j]==1 && aux2[i][j]!=2)   	//Se revisa cuantas casillas han sido destapadas, para luego hacer el calculo si gana
		{
		*destapados=*destapados+1;
		aux2[i][j]=2;						//Matriz auxiliar que marca las casillas que ya han sido contadas
		}	
	}
}
		
} 

