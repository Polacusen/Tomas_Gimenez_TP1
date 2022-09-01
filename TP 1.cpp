#include<iostream>
#include<fstream>

int const dim_fil {8};
int const dim_col {5};

using namespace std;
template <class TIPOD>
int Mayor(TIPOD cant[dim_fil]);
template <class TIPOD>
void Mostrar(TIPOD mat[][dim_col]);
void Ordenar_Doble(float v[], int dim,string vec[]);

int main (){
    //Estructuras de DATOS
    string nom [dim_fil]{};                 //Guarda nombre de los clientes
    string tip_prod [dim_col]{};            //Guarda los tipo de producto
    float peso [dim_fil][dim_col]{};        //Guarda el peso total por cliente y tipo de producto
    float distancia [dim_fil][dim_col]{};   //Guarda la distancia total por cliente y tipo de producto
    int cant[dim_fil]{};                   //vector que suma cuantos tipo de prod pasan los 13000 kg 
    int cod_cli=0,cod_tip_prod=0;          //Variable para leer archivo
    float peso_tot=0,dist_tot=0;           //Variable para leer archivo
    string aux_tip_prod [dim_col]{};        //Vector auxiliar para no "romper" el vector de nombre de clientes
    int cantidad[dim_col]{};                //Guarda la cantidad de viajes por tipo de producto
    float aux[dim_col]{};                     //Vector auxiliar para guardar las distancias del cliente q mas pasa los 13000kg

    ifstream nombres;               //declaro el archivo
    nombres.open("Nombres.txt");    //abro el archivo
    if(!nombres){                   //compruebo q se abre bien el archivo
        cout<<"Error al abrir el archivo"<<endl;
    }
    for(int i=0;i<dim_fil;i++){     //Cargo el vector con los clientes
        nombres >> nom[i];
    }
    for(int i=0;i<dim_col;i++){     //Cargo el vector con los tipo de producto
        nombres >> tip_prod[i];
    }
    nombres.close();
    for (int i = 0; i < dim_col; i++){  //Cargo el vector auxiliar con los tipo de producto
       aux_tip_prod[i]=tip_prod[i];
    }
    
    ifstream datos;                 //declaro el archivo
    datos.open("Datos.txt");        //abro el archivo
    if(!datos){                     //compruebo q se abre bien el archivo
        cout<<"Error al abrir el archivo"<<endl;
    }

    while(datos>>cod_cli>>cod_tip_prod>>peso_tot>>dist_tot){        //Cargo las matrices de peso,distancia y el vector cantidad
        peso[cod_cli][cod_tip_prod] = peso[cod_cli][cod_tip_prod] + peso_tot;
        distancia[cod_cli][cod_tip_prod] = distancia[cod_cli][cod_tip_prod] + dist_tot;
        cantidad[cod_tip_prod]++;
    }
    datos.close();

    /*cout<<"MATRIZ PESOS"<<endl;    //Muestro matriz peso
    Mostrar(peso);
    cout<<"MATRIZ DISTANCIAS"<<endl;    //Muestro matriz distancia
    Mostrar(distancia);
    cout<<"MATRIZ CANTIDAD"<<endl;      //Muestro matriz cantidad
    Mostrar(cantidad);*/
    
    //Punto 1
    cout<<"Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados: "<<endl;
    for(int i=0;i<dim_fil;i++){     //Encuentro por cliente los tipos de producto q superan los 13000 kg
        cout<<nom[i]<<":";
        for(int j=0;j<dim_col;j++){
            if(peso[i][j] > 13000){
                cout<<" "<<tip_prod[j]<<" ";
                cant[i]++;          //vector que suma cuantos tipo de prod pasan los 13000 kg 
            }
        }
        cout<<endl;
    }
    //Punto 2
    int pos_may=0;
    pos_may=Mayor(cant);        //Encuentra cual es el tipo de producto que mas pasa los 13000 kg
            
    for (int i = 0; i < dim_col; i++){      //Guardo todas las distancias del cliente que tiene mas productos que pasan los 13000kg
        aux[i]=distancia[pos_may][i];
    }
    int pos_may1=0;
    pos_may1= Mayor(aux);
    Ordenar_Doble(aux,dim_col,aux_tip_prod);   //Ordeno los vectores de tipo de productos y de distacias de forma ascendente  

    cout<<"\nLista de Km recorridos por tipo de producto ascendete: "<<endl;
    for (int i = 0; i < dim_col; i++){          //Muestro los tipo de producto y distancias de forma ascendente del cliente q mas pasa los 13000kg
        cout<<aux_tip_prod[i]<<":  "<<aux[i]<<endl;     
    }
    //Punto 3
    cout<<"\nCantidad de entregas para el tipo de producto "<<tip_prod[pos_may1]<<": "<<cantidad[pos_may1]; //Muestro la cantidad de entregas del tipo de prod con mayor km recorridos
    return 0;
}
template <class TIPOD>
void Mostrar(TIPOD mat[][dim_col]){
    for(int i=0;i<dim_fil;i++){
        for(int j=0;j<dim_col;j++){
            cout<<mat[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout<<endl;
}
template <class TIPOD>
int Mayor(TIPOD cant[dim_fil]){
    int pos_may=0;
    for (int i = 0; i < dim_fil; i++){
        if(cant[i]>cant[pos_may]){
            pos_may=i;
        }
    }
    return pos_may;
}
void Ordenar_Doble(float v[], int dim,string vec[])
{
	int i, pos, imin;
    float temp;
    string auxi;
	for (pos = 0; pos < dim - 1 ; pos++) {
		imin = pos;
		for (i = pos+1 ; i < dim ; i++){
            if (v[i] < v[imin])
				imin = i;
        }
		temp = v[pos];
        auxi=vec[pos];
		v[pos] = v[imin];
        vec[pos]=vec[imin];
		v[imin] = temp;
        vec[imin]=auxi;
	}
}