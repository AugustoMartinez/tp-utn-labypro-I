#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//Autores:
//ñegue Gustavo
//Ubilla Martina
//Marttinez Augusto

typedef struct {
     char nombre[20];
     char apellido[20];
     int dni;
     char mail[40];
     char domicilio[50];
     char movil[20];
     int idCliente;
     bool bajaCliente; //true si esta de baja, false si no lo esta
} stClientes;

typedef struct{
    int dia;
    int mes;
    int anio;
}stFecha;

typedef struct{
    int idPedido;
    float costoPedido;
    bool pedidoAnulado; //true si esta de anulado, false si no lo esta
    int dni;
    int idCliente;
    stFecha fechaPedido;
    char descripcionPedido[400];
}stPedidos;

void cargarCliente();
stClientes cargarDatos(stClientes cliente);
int asignarId(int dato);
int verificaUnico(int dni);

void mostrarArchivoCliente();
void mostrarCliente(stClientes cliente);

int buscarPosicion(int dni);
stClientes modificarDatosCliente(stClientes cliente);
void modificarCliente(int dni);
void bajaCliente(int dni);
void altaCliente(int dni);
int encontrarIdCliente(int dni);


int archivoArreglo(stClientes arregloCli[], int dim);
void mostrarArregloCli (stClientes arregloCli[],int validos);

void ordenacionInsercion(stClientes arregloCli[ ], int validos);

void insertar(stClientes arregloCli[ ], int u,stClientes dato[]);
int compara(stClientes arregloCli[],stClientes dato[],int i,int h);
void ordenacionSeleccion(stClientes arregloCli[ ], int validos);
int posicionMenor(stClientes arregloCli[], int validos, int pos);
void intercambio(stClientes A[], int i, int j);

void menuCliente();
void menuPedido();
void menuListarPedido();
void menuListarCLientes();

stPedidos cargarPedido(int idPedidoPos,int dni,int idCliente);
void cargarArchivoDePedidos(int dni);

void mostrarListadoDePedidos();
void mostrarPedido(stPedidos pedido);

int cantidadDeArchivos();

void buscarPedidosPorCliente(int dni);
void modificarPedido(int idPedido);
stPedidos modificarPedidoSelec(stPedidos pedido);

void bajaPedido(int idPedido);
void altaPedido(int idPedido);


int cantidadPedidosCliente(int dni);
void topTenClientes(stClientes P[], int validos);
stClientes peorCliente();
void mostrarPeorCliente();
void insertarPorCantPedidos(stClientes P[], int x, stClientes Cl);
void ordenarClientesPorPedidos(stClientes P[], int validos);

int pedidosPosMenor(stPedidos arregloPed[], int u, int validos);
void ordenacionPedidosSelec(stPedidos arregloPed[],int validos);
void mostrarArrayPedidos(stPedidos arregloPed[],int validos);

const char nombreArchivoCli[30]="archivoClientes";

int main(){
    int elegir_cliente_pedido;

    do{
        printf("----Menu Principal-----\n");
        printf("\nQue desea ver?\n");
        printf("\n1.Clientes\n");
        printf("\n2.Pedidos\n");
        printf("\nO ingrese 0 si desea salir...\n\n");
        scanf("%d", &elegir_cliente_pedido);

        if(elegir_cliente_pedido == 1){
            menuCliente();
        }else if(elegir_cliente_pedido == 2){
            menuPedido();
        }
        else if(elegir_cliente_pedido == 0){
            printf("Programa finalizado\n");
        }
        else{
            printf("Eleccion invalida\n");
            system("pause");
            system("cls");
        }

    }while(elegir_cliente_pedido != 0);

    return 0;
}

///Menus
//SubMenu listado de clientes
void menuListarCLientes(){
    int eleccion, doc;
    int dim = 100;
    int validos = 0;
    stClientes arregloCli[dim];

    validos = archivoArreglo(arregloCli, dim);

    menu:
    system("pause");
    system("cls");
    printf("-----------Listar cliente-----------\n");
    printf("\n1.Ordenados por apellido y nombre\n");
    printf("\n2.Ordenados por DNI\n");
    printf("\n0. Volver al menu principal\n\n");
    scanf("%d", &eleccion);

    switch(eleccion){
        case 1:{
        system("cls");
        printf("\n------------------Ordenados por Nombre y Apellido------------------\n");
        ordenacionInsercion(arregloCli,validos);
        mostrarArregloCli(arregloCli,validos);
        }
        goto menu;
    case 2:{
        system("cls");
        printf("\n------------------Ordenados por DNI------------------\n");
        ordenacionSeleccion(arregloCli,validos);
        mostrarArregloCli(arregloCli,validos);
        }
        goto menu;

    case 0:{
        printf("\nVolviendo al menu principal...\n");
        system("pause");
        system("cls");
        }
        break;
    default:
        goto menu;
    }
}

//Menu Clientes
void menuCliente(){
    int eleccion, doc;

    menu:
    system("pause");
    system("cls");
    printf("-----------Menu cliente-----------\n");
    printf("\nQue desea hacer?\n");
    printf("\n1.Cargar cliente\n");
    printf("\n2.Mostrar todos los clientes\n");
    printf("\n3.Dar de baja a un cliente\n");
    printf("\n4.Dar de alta a un cliente\n");
    printf("\n5.Modificar cliente\n");
    printf("\n6.Listar clientes\n");
    printf("\n0. Volver al menu principal\n\n");
    scanf("%d", &eleccion);


    switch (eleccion){
    case 1:{
        system("cls");
        cargarCliente();
        }
        goto menu;
    case 2:
        system("cls");
        mostrarArchivoCliente();
        goto menu;
    case 3:{
        system("cls");
        printf("\n------------------Dar de baja Cliente------------------\n");
        do{
            printf("\nEn caso de querer salir ingrese 0..\n");
            printf("\nIngrese el numero de DNI del cliente que quiere dar de baja. Ya debe estar cargado en el sistema: ");
            scanf("%d",&doc);
        }while(verificaUnico(doc) == 0 && doc != 0);

        if(doc != 0){
            bajaCliente(doc);
        }

        }
        goto menu;
    case 4:{
        system("cls");
        printf("\n------------------Dar de alta Cliente------------------\n");
        do{
            printf("\nEn caso de querer salir ingrese 0..\n");
            printf("\nIngrese el numero de DNI del cliente que quiere dar de alta. Ya debe estar cargado en el sistema: ");
            scanf("%d",&doc);
        }while(verificaUnico(doc) == 0 && doc != 0);

        if(doc != 0){
            altaCliente(doc);
        }

        }
        goto menu;
    case 5:{
        system("cls");
        printf("\n------------------Modificar Cliente------------------\n");
        do{
            printf("\nEn caso de querer salir ingrese 0..\n");
            printf("\nIngrese el numero de DNI del cliente que quiere modificar. Ya debe estar cargado en el sistema: ");
            scanf("%d",&doc);
        }while(verificaUnico(doc) == 0 && doc != 0);

        if(doc != 0){
            modificarCliente(doc);
        }

        }
        goto menu;
    case 6:{
        menuListarCLientes();
    }
    case 0:{
        printf("\nVolviendo al menu principal...\n");
        system("pause");
        system("cls");
        }
        break;
    default:
        goto menu;
    }

}

//SubMenu listado de Pedidos
void menuListarPedido(){
    int eleccion, dni;
    int dim = 100;
    int validos = 0;
    int validosPed = 0;

    stClientes arregloCli[dim];
    stPedidos arregloPed[dim];

    validos = archivoArreglo(arregloCli, dim);
    validosPed=archivoArregloPed(arregloPed,dim);

    menu:
    system("pause");
    system("cls");
    printf("-----------Listar Pedidos-----------\n");
    printf("\n1.Mostrar todos los pedidos de un cliente por DNI\n");
    printf("\n2.Listar Pedidos por orden de fecha\n");
    printf("\n3.Top ten clientes\n");
    printf("\n4.Peor Cliente\n");
    printf("\n0. Volver al menu principal\n\n");
    scanf("%d", &eleccion);

    switch(eleccion){
        case 1:{
        system("cls");
        printf("\n------------------Pedidos de un cliente------------------\n");
        do{
            printf("Ingrese el DNI del cliente: ");
            scanf("%d",&dni);
        }while(verificaUnico(dni) == 0);
        buscarPedidosPorCliente(dni);
        }
        goto menu;
    case 2:{
        system("cls");
        printf("\n------------------Lista ordenada de Pedidos por fecha------------------\n");
        ordenacionPedidosSelec(arregloPed,validosPed);
        mostrarArrayPedidos(arregloPed,validosPed);
        }
        goto menu;
    case 3:{

        system("cls");
        printf("\n------------------Top Ten clientes------------------\n");
        ordenarClientesPorPedidos(arregloCli, validos);
        topTenClientes(arregloCli, validos);
        }
        goto menu;
    case 4:{
        system("cls");
        printf("\n------------------Peor Cliente------------------\n");
        mostrarPeorCliente();
        }
        goto menu;
    case 0:{
        printf("\nVolviendo al menu principal...\n");
        system("pause");
        system("cls");
        }
        break;
    default:
        goto menu;
    }
}

//Menu Pedidos
void menuPedido(){
    int eleccion, dni, id;

    menu:
    system("pause");
    system("cls");
    printf("-----------Menu Pedido-----------\n");
    printf("\nQue desea hacer?\n");
    printf("\n1.Cargar Pedidos\n");
    printf("\n2.Mostrar Todos los pedidos\n");
    printf("\n3.Anular un pedido\n");
    printf("\n4.Activar un pedido\n");
    printf("\n5.Modificar Pedido\n");
    printf("\n6.Listado y Estadisticas\n");
    printf("\n0. Volver al menu principal\n\n");
    scanf("%d", &eleccion);


    switch (eleccion){
    case 1:{
        system("cls");
        printf("Ingrese el DNI del cliente: ");
        scanf("%i",&dni);
        cargarArchivoDePedidos(dni);
        }
        goto menu;
    case 2:
        system("cls");
        mostrarListadoDePedidos();
        goto menu;
    case 3:{
        system("cls");
        printf("\n------------------Anular Pedido------------------\n");
        do{
            printf("\nEn caso de querer salir ingrese 0..\n");
            printf("Ingrese el DNI del cliente: ");
            scanf("%d",&dni);
        }while(verificaUnico(dni) == 0 && dni != 0);

        if(dni != 0){
            buscarPedidosPorCliente(dni);
        }

        do{
            printf("\nIngrese el numero de Id del pedido que quiere anular. Ya debe estar cargado en el sistema: ");
            scanf("%d",&id);
        }while(verificarExistenciaPedido(id) == 0 && dni != 0);

        if(dni != 0){
            bajaPedido(id);
        }

        }
        goto menu;
    case 4:{
        system("cls");
        printf("\n------------------Activar Pedido------------------\n");
        do{
            printf("\nEn caso de querer salir ingrese 0..\n");
            printf("Ingrese el DNI del cliente: ");
            scanf("%d",&dni);
        }while(verificaUnico(dni) == 0 && dni != 0);

        if(dni != 0){
            buscarPedidosPorCliente(dni);
        }

        do{
            printf("\nIngrese el numero de Id del pedido que quiere activar. Ya debe estar cargado en el sistema: ");
            scanf("%d",&id);
        }while(verificarExistenciaPedido(id) == 0 && dni != 0);

        if(dni != 0){
            altaPedido(id);
        }

        }
        goto menu;
    case 5:{
        system("cls");
        printf("\n------------------Modificar Pedido------------------\n");
        do{
            printf("\nEn caso de querer salir ingrese 0..\n");
            printf("Ingrese el DNI del cliente: ");
            scanf("%d",&dni);
        }while(verificaUnico(dni) == 0 && dni != 0);

        if(dni != 0){
            buscarPedidosPorCliente(dni);
        }

        do{
            printf("\nIngrese el numero de Id del pedido que quiere modificar. Ya debe estar cargado en el sistema: ");
            scanf("%d",&id);
        }while(verificarExistenciaPedido(id) == 0 && dni != 0);

        if(dni != 0){
            modificarPedido(id);
        }

        }
        goto menu;
    case 6:{
       menuListarPedido();
    }
    goto menu;
    case 0:{
        printf("\nVolviendo al menu principal...\n");
        system("pause");
        system("cls");
        }
        break;
    default:
        goto menu;
    }

}

///----------------CLIENTES

///CARGAR UN CLIENTE:
stClientes cargarDatos(stClientes cliente){
    printf("\nIngrese los datos de un nuevo cliente: \n");

    do{
        printf("\nNombre: ");
        fflush(stdin);
        gets(cliente.nombre);
    }while(isalpha(cliente.nombre)!=0);   //isalpha: indica si se ingresa una letra

    do{
        printf("\nApellido: ");
        fflush(stdin);
        gets(cliente.apellido);
    }while(isalpha(cliente.nombre)!=0);

    do{
        printf("\nIngrese el DNI del cliente:\n");
        scanf("%d",&cliente.dni);
    }while(verificaUnico(cliente.dni) == 1);

    do{
        printf("\nMail: ");
        fflush(stdin);
        gets(cliente.mail);
    }while(strstr(cliente.mail,"@")==NULL);

    printf("\nDomicilio: ");
    fflush(stdin);
    gets(cliente.domicilio);

    printf("\nMovil: ");
    fflush(stdin);
    gets(cliente.movil);

    cliente.bajaCliente = false;

    return cliente;

}

void cargarCliente(){
    FILE * arch = fopen(nombreArchivoCli,"ab");

    stClientes cliente;

    char seguir = 's';

    int ident = asignarId(sizeof(stClientes))+1;;

    if(arch != NULL){
        printf("\n------------------Cargar Clientes------------------\n");

        while(seguir == 's'){
            cliente.idCliente = ident++;

            cliente = cargarDatos(cliente);

            fwrite(&cliente,sizeof(stClientes),1,arch);

            printf("\nDesea ingresar otro cliente?(s para continuar): ");
            fflush(stdin);
            scanf("%c",&seguir);
        }

        fclose(arch);
    }
    else{
        printf("El Archivo no se puede abrir ni crear");
    }
}

int asignarId(int dato){
    FILE * buf = fopen(nombreArchivoCli,"rb");
    int cant = 0;

    if(buf != NULL){
        fseek(buf,0 ,SEEK_END);
        cant = ftell(buf) / dato;

        fclose(buf);
    }

    return cant;
}

///VERIFICA SI YA EXISTE UN CLIENTE:
int verificaUnico(int dni){
    FILE * arch2 = fopen(nombreArchivoCli,"rb");

    stClientes cliente;
    int flag = 0; // 0 si no existe y 1 si existe

    if(arch2!=NULL){
        while(fread(&cliente,sizeof(stClientes),1,arch2)>0){
            if(cliente.dni==dni){
                flag = 1;
            }
        }

    fclose(arch2);
    }

    return flag;
}

///MOSTRAR UN CLIENTE:
void mostrarArchivoCliente(){
    FILE * buf = fopen(nombreArchivoCli,"rb");
    stClientes cliente;

    if(buf == NULL){
        printf("\nNo se pudo abrir el archivo.");
    }
    else{
        printf("\n------------------Mostrar Clientes------------------\n");

        while(fread(&cliente,sizeof(stClientes),1,buf) > 0){
            mostrarCliente(cliente);
        }

        fclose(buf);
    }
}

void mostrarCliente(stClientes cliente){
    printf("\n------------------------\n");

    printf("Id Cliente: %i\n",cliente.idCliente);
    printf("Nombre: %s\n",cliente.nombre);
    printf("Apellido: %s\n",cliente.apellido);
    printf("DNI: %d\n",cliente.dni);
    printf("Mail: %s\n",cliente.mail);
    printf("Domicilio: %s\n",cliente.domicilio);
    printf("Movil: %s\n",cliente.movil);

    if (cliente.bajaCliente==false){
        printf("El cliente esta activo.");
    }
    else{
        printf("El cliente esta de baja.");
    }

    printf("\n------------------------\n");
}

///BUSCAR POSICION DE CLIENTE POR DNI

int buscarPosicion(int dni){
    FILE * buf = fopen(nombreArchivoCli,"rb");
    stClientes cliente;

    int i=0;

    if(buf==NULL){
        printf("\nNo se pudo abrir el archivo.");
    }
    else{
        while(fread(&cliente,sizeof(stClientes),1,buf) > 0 && cliente.dni!=dni){
            i++;
        }

        fclose(buf);
    }

   return i;
}

///DAR DE BAJA UN CLIENTE:
void bajaCliente(int dni){
    FILE * arch = fopen(nombreArchivoCli,"r+b");
    int pos;
    stClientes cliente;

    if (arch==NULL){
        printf("\nNo se pudo abrir el archivo.");
    }
    else{
        pos = buscarPosicion(dni);

        fseek(arch, sizeof(stClientes)* pos, SEEK_SET);
        fread(&cliente, sizeof(stClientes), 1, arch);

        printf("\nEste es el estado actual del cliente.");
        mostrarCliente(cliente);

        fseek(arch,sizeof(stClientes)*(-1),SEEK_CUR);

        cliente.bajaCliente = true;

        fwrite(&cliente,sizeof(stClientes),1,arch);

        fclose(arch);

        printf("\nEl cliente fue dado de baja con exito.\n");
    }
}

///DAR DE ALTA UN CLIENTE YA EXISTENTE:
void altaCliente(int dni){
    FILE * arch = fopen(nombreArchivoCli,"r+b");
    stClientes cliente;
    int pos;

    if(arch==NULL){
        printf("\nNo se pudo abrir el archivo.");
    }
    else{
        pos=buscarPosicion(dni);

        fseek(arch,sizeof(stClientes) * pos,SEEK_SET);
        fread(&cliente,sizeof(stClientes),1,arch);

        printf("\nEste es el estado actual del cliente.");
        mostrarCliente(cliente);

        fseek(arch,sizeof(stClientes)*(-1),SEEK_CUR);

        cliente.bajaCliente = false;

        fwrite(&cliente,sizeof(stClientes),1,arch);

        fclose(arch);

        printf("\nEl cliente fue dado de alta con exito.\n");
    }

}

///MODIFICAR UN CLIENTE:
void modificarCliente(int dni){
    FILE * arch = fopen(nombreArchivoCli,"r+b");
    int pos;
    stClientes cliente;

    if(arch==NULL){
        printf("\nNo se pudo abrir el archivo.");
    }
    else{
        pos=buscarPosicion(dni);

        fseek(arch, sizeof(stClientes) * pos, SEEK_SET);
        fread(&cliente, sizeof(stClientes), 1, arch);

        printf("\nEste es el actual del cliente.");
        mostrarCliente(cliente);

        fseek(arch, sizeof(stClientes)*(-1), SEEK_CUR);

        cliente = modificarDatosCliente(cliente);

        fwrite(&cliente,sizeof(stClientes),1,arch);

        fclose(arch);
    }

}

stClientes modificarDatosCliente(stClientes cliente){
    char nombre,apellido,mail,domicilio,documento,tel;

    ///MODIFICA NOMBRE
    do{
        printf("\nDesea modificar el nombre (s/n)?\n");
        fflush(stdin);
        scanf("%c",&nombre);
    }while(nombre != 's' && nombre != 'n');

    if(nombre == 's'){
        do{
            printf("\nNombre: ");
            fflush(stdin);
            gets(cliente.nombre);
        }while(isalpha(cliente.nombre)!=0);
    }

    ///MODIFICA APELLIDO
    do{
        printf("\nDesea modificar el apellido (s/n)?\n");
        fflush(stdin);
        scanf("%c",&apellido);
    }while(apellido != 's' && apellido != 'n');

    if(apellido == 's'){
        do{
            printf("\nApellido: ");
            fflush(stdin);
            gets(cliente.apellido);
        }while(isalpha(cliente.nombre)!=0);
    }

     ///MODIFICA DNI
    do{
        printf("\nDesea modificar el dni (s/n)?\n");
        fflush(stdin);
        scanf("%c",&documento);
    }while(documento != 's'&& documento != 'n');

    if(documento == 's'){
        do{
            printf("\nDNI:\n");
            scanf("%d",&cliente.dni);
        }while(verificaUnico(cliente.dni) == 1);
    }

    ///MODIFICA MAIL
    do{
        printf("\nDesea modificar el mail (s/n)?\n");
        fflush(stdin);
        scanf("%c",&mail);
    }while(mail != 's' && mail != 'n');

    if(mail=='s'){
        do{
            printf("\nMail: ");
            fflush(stdin);
            gets(cliente.mail);
        }while(strstr(cliente.mail,"@")==NULL);
    }


    ///MODIFICA DOMICILIO
    do{
        printf("\nDesea modificar el domicilio (s/n)?\n");
        fflush(stdin);
        scanf("%c",&domicilio);
    }while(domicilio != 's' && domicilio != 'n');

    if(domicilio == 's'){
        printf("\nDomicilio: ");
        fflush(stdin);
        gets(cliente.domicilio);
    }

    ///MODIFICA MOVIL
    do{
        printf("\nDesea modificar el numero de movil (s/n)?\n");
        fflush(stdin);
        scanf("%c",&tel);
    }while(tel != 's' && tel != 'n');

    if(tel == 's'){
        printf("\nMovil: ");
        fflush(stdin);
        gets(cliente.movil);
    }

    printf("\nDatos modificados del cliente:");
    mostrarCliente(cliente);

    return cliente;
}

///BUSCAR ID CLIENTE POR DNI
int encontrarIdCliente(int dni){
    FILE * buf = fopen(nombreArchivoCli,"rb");
    stClientes cliente;
    int id;
    int pos = 0;

    if(buf == NULL){
        printf("\nNo se pudo abrir el archivo.");
    }
    else{
        pos = buscarPosicion(dni);
        fseek(buf, sizeof(stClientes)* pos, SEEK_SET);
        fread(&cliente, sizeof(stClientes), 1, buf);
        id = cliente.idCliente;
        fclose(buf);
    }
    return id;
}

///PASAR ARCHIVO CLIENTES A ARRAY
int archivoArreglo(stClientes arregloCli[], int dim){
    FILE * arch = fopen(nombreArchivoCli,"rb");
    int i=0;
    stClientes cliente;

    if (arch!=NULL){
        while (fread(&cliente,sizeof(stClientes),1,arch)>0 && i<dim){
            arregloCli[i] = cliente;
            i++;
        }
        fclose(arch);
    }

    return i;
}

///MOSTRAR ARRAY CLIENTES
void mostrarArregloCli(stClientes arregloCli[],int validos){
    int i=0;

    while (i<validos){
        mostrarCliente(arregloCli[i]);
        i++;
    }

}

///ORDENACION POR INSERCION POR APELLIDO Y NOMBRE:
int compara(stClientes arregloCli[],stClientes dato[],int i,int h){
    int flag=0;

    if (strcmpi(arregloCli[i].apellido,dato[h].apellido)>0){
        flag=1;
    }
    else if(strcmpi(arregloCli[i].nombre,dato[h].nombre)==0){
        flag=1;
    }

    return flag;
}

void insertar(stClientes arregloCli[], int u,stClientes dato[]){
    int i= u,h=0; //ultima pos valida izq
    while (i >= 0 && compara(arregloCli,dato,i,h)==1){
        arregloCli[i+1] = arregloCli[i];
        i--;
    }
    arregloCli[i+1] = dato[h];
}

void ordenacionInsercion(stClientes arregloCli[ ], int validos){
    int u=0;
    stClientes dato[10];

    while (u < validos - 1)
    {
        dato[0]=arregloCli[u+1];
        insertar(arregloCli, u, dato);
        u++;
    }
}

///ORDENACION POR SELECCION POR DNI:
int posicionMenor(stClientes arregloCli[], int validos, int pos){
    stClientes menor[10];
    menor[0] = arregloCli[pos];
    int posMenor = pos;
    int index = pos + 1;
    while (index < validos){
        if(menor[0].dni > arregloCli[index].dni){
            menor[0] = arregloCli[index];
            posMenor = index;
        }

        index++;
    }
    return posMenor;
}

void intercambio(stClientes A[], int i, int j){
    stClientes aux[10];
    aux[0] = A[i];
    A[i] = A[j];
    A[j] = aux[0];
}

void ordenacionSeleccion(stClientes arregloCli[ ], int validos){
    int posMenor;
    int i = 0;
    while(i<validos - 1){ //llego hasta la anteúltima posición
        posMenor = posicionMenor(arregloCli, validos, i);
        intercambio(arregloCli,posMenor,i);
        i++;
    }
}


///----------------PEDIDOS

///Cargar datos de pedido
stPedidos cargarPedido(int idPedidoPos,int dni,int idCliente){
    stPedidos pedido;
    int flag;

    pedido.idPedido = idPedidoPos + 1;
    pedido.dni = dni;
    pedido.idCliente=idCliente;
    pedido.pedidoAnulado = false;

    printf("\nIngrese los datos del pedido: ");
    fflush(stdin);

    printf("\nIngrese el costo: ");
    scanf("%f",&pedido.costoPedido);
    fflush(stdin);

    do{
        flag=0;
        printf("\nIngrese el anio que se realizo el pedido: ");
        fflush(stdin);
        scanf("%i", &pedido.fechaPedido.anio);

        if((2000<=pedido.fechaPedido.anio)&&(2025>=pedido.fechaPedido.anio)){
            flag=1;
        }
        else{
            printf("\n**Ingreso un dato erroneo**");
        }
    }while(flag==0);

    do{
        flag=0;
        printf("\nIngrese el mes(en numero) que se realizo el pedido: ");
        fflush(stdin);
        scanf("%i",&pedido.fechaPedido.mes);

        if((0<pedido.fechaPedido.mes)&&(13>pedido.fechaPedido.mes)){
            flag=1;
        }
        else{
            printf("\n**Ingreso un dato erroneo**");
        }
    }while(flag==0);

    do{
        flag=0;
        printf("\nIngrese el dia que se realizo el pedido: ");
        fflush(stdin);
        scanf("%i",&pedido.fechaPedido.dia);

        if((0<pedido.fechaPedido.dia)&&(32>pedido.fechaPedido.dia)){
            flag=1;
        }
        else{
            printf("\n**Ingreso un dato erroneo**");
        }
    }while(flag==0);

    printf("\nIngrese la descripcion del pedido: ");
    fflush(stdin);
    gets(pedido.descripcionPedido);

    return pedido;
}

///Cargar pedidos
void cargarArchivoDePedidos(int dni){
    FILE * buffPedido = fopen("ArchivoPedidos.bin","ab");

    stPedidos aux;
    char salir = 's';
    char pregunta;

    int idPedidoPos;
    int cantPedidos = cantidadDeArchivos();
    int idCliente = encontrarIdCliente(dni);

    if(buffPedido!=NULL){
        while(salir =='s'){
            idPedidoPos = cantPedidos++;
            printf("\n------------------------------ Cargar Pedidos ------------------------------\n");

            aux = cargarPedido(idPedidoPos,dni,idCliente);

            printf("\nEsta seguro de que desea agregar este pedido?s/n\n");
            scanf("%c",&pregunta);

            if(pregunta=='s'){
                fwrite(&aux,sizeof(stPedidos),1,buffPedido);
                printf("\n**Pedido cargado con exito**");
            }
            else{
                printf("\n**No se cargo el pedido**");
            }

        printf("\nDesea agregar otro Pedido? s/n:");
        fflush(stdin);
        scanf("%c",&salir);

        }
    fclose(buffPedido);
    }
    else{
        printf("no se pudo abrir el archivo");
    }
}

///mostrar
void mostrarListadoDePedidos(){
    FILE * buffPedido = fopen("ArchivoPedidos.bin","rb");
    stPedidos aux;

    if(buffPedido!=NULL){

        printf("\n---------------------------Mostrar Pedidos---------------------------\n");

        while (fread(&aux,sizeof(stPedidos),1,buffPedido) > 0){
            mostrarPedido(aux);
        }

        fclose(buffPedido);
    }
    else{
        printf("no se pudo abrir el archivo");
    }
}

void mostrarPedido(stPedidos pedido){
    printf("\n------------------------\n");

    printf("\nId: %i",pedido.idPedido);
    printf("\nDNI: %i",pedido.dni);
    printf("\nFecha: %i/%i/%i",pedido.fechaPedido.dia,pedido.fechaPedido.mes,pedido.fechaPedido.anio);
    printf("\nCosto: $%.2f",pedido.costoPedido);

    if(pedido.pedidoAnulado == true){
        printf("\nEstado actual: Anulado");
    }
    else{
        printf("\nEstado actual: Activo");
    }
    printf("\nDescripcion del pedido: \n%s",pedido.descripcionPedido);
    printf("\n------------------------\n");
}

///contar archivos
int cantidadDeArchivos(){
    FILE * buff = fopen("ArchivoPedidos.bin","rb");
    int cantidad = 0;

    if(buff != NULL){
        fseek(buff, 0, 2);
        cantidad = ftell(buff)/sizeof(stPedidos);

        fclose(buff);
    }

    return cantidad;
}

void buscarPedidosPorCliente (int dni){
    FILE * buffPedido = fopen("ArchivoPedidos.bin","rb");
    stPedidos aux;
    int flag=0;

    if(buffPedido!=NULL){
        while(fread(&aux,sizeof(stPedidos),1,buffPedido) > 0){
            if(dni==aux.dni){
                mostrarPedido(aux);
                flag = 1;
            }
        }
        if(flag==0){
            printf("\nEste cliente no tiene pedidos");
        }
        fclose(buffPedido);
    }
    else{
        printf("no se pudo abrir el archivo");
    }
}

///Verificar si existe pedido
int verificarExistenciaPedido(int id){
    FILE * buffer = fopen("ArchivoPedidos.bin","rb");

    stPedidos p;
    int flag = 0; // 0 si no existe y 1 si existe

    if(buffer!=NULL){
        while(fread(&p,sizeof(stPedidos),1,buffer) > 0){
            if(p.idPedido == id){
                flag = 1;
            }
        }

    fclose(buffer);
    }

    return flag;
}

///modificar
void modificarPedido (int idPedido){
    FILE * buffPedido = fopen("ArchivoPedidos.bin","r+b");

    stPedidos aux;
    char pregunta;

    if(buffPedido!=NULL){

        fseek(buffPedido,sizeof(stPedidos)*(idPedido-1),SEEK_SET);
        fread(&aux,sizeof(stPedidos),1,buffPedido);

        system("cls");
        printf("\nEste es el pedido a modificar");

        mostrarPedido(aux);

        fseek(buffPedido,sizeof(stPedidos)*(-1),SEEK_CUR);

        aux = modificarPedidoSelec(aux);

        printf("\nEsta seguro de que desea modificar este pedido?s/n\n");
        scanf("%c",&pregunta);

        if(pregunta =='s'){
            fwrite(&aux,sizeof(stPedidos),1,buffPedido);

            printf("\n**Pedido modificado con exito**\n");
            system("pause");
            system("cls");

            printf("\nEstado actual del pedido");

            mostrarPedido(aux);

        }
        else{
            printf("\n**No se modifico el pedido**\n");
        }
    fclose(buffPedido);
    }
    else{
        printf("no se pudo abrir el archivo");
    }
}

///modificar seleccionado
stPedidos modificarPedidoSelec (stPedidos pedido){

    printf("\nIngrese los datos del pedido a modificar:\n");
    fflush(stdin);

    printf("\nIngrese el costo:\n");
    scanf("%f",&pedido.costoPedido);
    fflush(stdin);

    int flag;

    do{
        flag=0;
        printf("\nIngrese el anio que se realizo el pedido:\n");
        scanf("%i", &pedido.fechaPedido.anio);
        fflush(stdin);

        if ((2000<=pedido.fechaPedido.anio)&&(2025>=pedido.fechaPedido.anio)){
            flag=1;
        }
        else{
            printf("\n**Ingreso un dato erroneo**\n");
        }
    }while(flag==0);

    do{
        flag=0;
        printf("\nIngrese el mes que se realizo el pedido:\n");
        scanf("%i",&pedido.fechaPedido.mes);
        fflush(stdin);

        if ((0<pedido.fechaPedido.mes)&&(13>pedido.fechaPedido.mes)){
            flag=1;
        }
        else{
            printf("\n**Ingreso un dato erroneo**\n");
        }
    }while(flag==0);

    do{
        flag=0;
        printf("\nIngrese el dia que se realizo el pedido:\n");
        scanf("%i",&pedido.fechaPedido.dia);
        fflush(stdin);

        if ((0<pedido.fechaPedido.dia)&&(32>pedido.fechaPedido.dia)){
            flag=1;
        }
        else{
            printf("\n**Ingreso un dato erroneo**\n");
        }
        }while(flag==0);

    printf("\nIngrese la descripcion del pedido:\n");
    gets(pedido.descripcionPedido);

    system("cls");
    return pedido;
}

///baja pedido
void bajaPedido (int idPedido){
    FILE * buffPedido = fopen("ArchivoPedidos.bin","r+b");

    stPedidos aux;
    char pregunta;

    if(buffPedido!=NULL){

        fseek(buffPedido,sizeof(stPedidos)*(idPedido-1),SEEK_SET);
        fread(&aux,sizeof(stPedidos),1,buffPedido);

        system("cls");
        printf("\nEstado actual del pedido");

        mostrarPedido(aux);

        fseek(buffPedido,sizeof(stPedidos)*(-1),SEEK_CUR);

        aux.pedidoAnulado = true;

        printf("\nEsta seguro de que desea dar de baja este pedido?s/n\n");
        fflush(stdin);
        scanf("%c",&pregunta);

        if(pregunta == 's'){
            fwrite(&aux,sizeof(stPedidos),1,buffPedido);

            printf("\n**Pedido dado de baja con exito**\n");
            system("pause");
            system("cls");

            printf("\nEstado actual del pedido");

            mostrarPedido(aux);
        }
        else{
            printf("\n**No se cargo la baja**\n");
        }

    fclose(buffPedido);
    }
    else{
        printf("no se pudo abrir el archivo");
    }
}

///alta pedido
void altaPedido (int idPedido){
    FILE * buffPedido=fopen("ArchivoPedidos.bin","r+b");

    stPedidos aux;
    char pregunta;

    if(buffPedido!=NULL){
        fseek(buffPedido,sizeof(stPedidos)*(idPedido-1),SEEK_SET);
        fread(&aux,sizeof(stPedidos),1,buffPedido);

        system("cls");
        printf("\nEstado actual del pedido");

        mostrarPedido(aux);

        fseek(buffPedido,sizeof(stPedidos)*(-1),SEEK_CUR);

        aux.pedidoAnulado = false;

        printf("\nEsta seguro de que desea dar de alta este pedido?s/n\n");
        fflush(stdin);
        scanf("%c",&pregunta);

        if(pregunta == 's'){
            fwrite(&aux,sizeof(stPedidos),1,buffPedido);

            printf("\n**Pedido dado de alta con exito**\n");
            system("pause");
            system("cls");

            printf("\nEstado actual del pedido");

            mostrarPedido(aux);
        }
        else{
            printf("\n**No se cargo el alta**\n");
        }
        fclose(buffPedido);
    }
    else{
        printf("no se pudo abrir el archivo");
    }
}

///Cantidad de pedidos que tiene un Cliente por DNI
int cantidadPedidosCliente(int dni){
    FILE * buffPedido = fopen("ArchivoPedidos.bin","rb");
    stPedidos aux;
    int cantPedidos = 0;

    if(buffPedido!=NULL){
        while(fread(&aux,sizeof(stPedidos),1,buffPedido) > 0){
            if(dni==aux.dni){
                cantPedidos++;
            }
        }
        fclose(buffPedido);
    }
    else{
        printf("no se pudo abrir el archivo");
    }

    return cantPedidos;
}

///ORDENAMIENTO POR INSERCCION DE CLIENTES POR CANT. PEDIDOS
void insertarPorCantPedidos(stClientes P[], int x, stClientes Cl){
    int cantPedidos = cantidadPedidosCliente(Cl.dni);

    while(x >= 0 && cantPedidos > cantidadPedidosCliente(P[x].dni)){
        P[x+1] = P[x];
        x--;
    }
    P[x+1] = Cl;
}

void ordenarClientesPorPedidos(stClientes P[], int validos){
    int i = 0;
    while(i < validos - 1){
        insertarPorCantPedidos(P, i, P[i+1]);
        i++;
    }
}

///MUESTRA LOS 10 MEJORES CLIENTES
void topTenClientes(stClientes P[], int validos){
    int i = 0;
    int cantPedidos;

    while(i < validos && i < 10){
        cantPedidos = cantidadPedidosCliente(P[i].dni);
        printf("\n----Top %d------\n", i+1);
        mostrarCliente(P[i]);
        printf("\nCantidad Pedidos: %d\n", cantPedidos);
        printf("\n----Top %d------\n", i+1);
        i++;
    }

}

///PEOR CLIENTE POR PEDIDOS
stClientes peorCliente(){
    FILE * buffer = fopen(nombreArchivoCli,"rb");

    stClientes cliente, peorCliente;
    int cantPedidos = 0, cantPedidosMenor;

    if(buffer!=NULL){
        while(fread(&cliente,sizeof(stClientes),1,buffer) > 0){
            cantPedidos = cantidadPedidosCliente(cliente.dni);
            if(cantPedidos < cantPedidosMenor && cantPedidos >= 0){
                cantPedidosMenor = cantPedidos;
                peorCliente = cliente;
            }

        }
        fclose(buffer);
    }
    else{
        printf("no se pudo abrir el archivo");
    }

    return peorCliente;
}

///MUESTRA AL PEOR CLIENTE
void mostrarPeorCliente(){
    stClientes Cl;
    int cantPedido = 0;
    Cl = peorCliente();

    cantPedido = cantidadPedidosCliente(Cl.dni);
    mostrarCliente(Cl);
    printf("\nCantidad de pedidos: %d\n", cantPedido);
}

///PASAR ARCHIVO PEDIDOS A ARRAY
int archivoArregloPed(stPedidos arregloPed[], int dim){
    FILE * buff = fopen("ArchivoPedidos.bin","rb");
    int i=0;
    stPedidos pedido;

    if (buff!=NULL){
        while (fread(&pedido,sizeof(stPedidos),1,buff)>0 && i<dim){
            arregloPed[i] = pedido;
            i++;
        }
        fclose(buff);
    }

    return i;
}

///ORDENAMIENTO POR SELECCION POR FECHA DE LOS PEDIDOS
int pedidosPosMenor(stPedidos arregloPed[], int u, int validos){
    int menorAnio= arregloPed[u].fechaPedido.anio;//u arranca en 0 y va creciendo
    int menorMes= arregloPed[u].fechaPedido.mes;
    int menorDia= arregloPed[u].fechaPedido.dia;
    int posMenor=u;
    int i=u+1;

    while (i <validos){
        if(menorAnio>arregloPed[i].fechaPedido.anio){
            menorAnio=arregloPed[i].fechaPedido.anio;
            posMenor=i;
        }
        else if((menorAnio==arregloPed[i].fechaPedido.anio)&&(menorMes>arregloPed[i].fechaPedido.mes)){
            menorMes=arregloPed[i].fechaPedido.mes;
            posMenor=i;
        }
        else if((menorAnio==arregloPed[i].fechaPedido.anio)&&(menorMes==arregloPed[i].fechaPedido.mes)&&(menorDia>arregloPed[i].fechaPedido.dia)){
            menorDia=arregloPed[i].fechaPedido.dia;
            posMenor=i;
        }
        i++;
    }
    return posMenor;
}

void ordenacionPedidosSelec(stPedidos arregloPed[],int validos){
    int posMenor;
    int i=0;
    stPedidos aux;

    while (i < validos - 1){
        posMenor=pedidosPosMenor(arregloPed,i,validos);
        aux=arregloPed[posMenor];
        arregloPed[posMenor]=arregloPed[i];
        arregloPed[i]=aux;
        i++;
    }
}

///MOSTRAR ARREGLO PEDIDOS
void mostrarArrayPedidos (stPedidos arreglo[],int validos){
    int i=0;

    while(i<validos){
        mostrarPedido(arreglo[i]);
        i++;
    }
}
