/**
* @file 
* @brief Proyecto 2_segundo corte
* @author Valentina Añasco Concha <valentinaanasco@unicauca.edu.co>
* @author Santiago Solarte Castillo <santiagosolarte@unicauca.edu.co>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* @brief Lee una cadena de caracteres del teclado, incluyendo espacios
* @param max_tamano Cantidad maxima de caracteres a leer
* @return linea Linea leida y NULL si no se pudo leer correctamente
*/
char * leer_linea(int max_tamano);

/**
* @brief Lee una linea y saca de ella un numero entero
* @return Numero leido y 1 si no se pudo leer correctamente
*/
int leer_entero();

/**
* @brief Lee una linea y saca de ella un numero real
* @return Valor real leido y 1 si no se pudo leer correctamente
*/
float leer_real();

/**
* @brief Quita el caracter de fin de linea de una cadena
* @param linea Variable que almacena la cadena de caracteres
*/
void quitar_fin_de_linea(char * linea);

/**
* @brief Lee el nombre de los estudiantes y lo guarda en un vector
* @param Arreglo de nomres y el numero de ellos
*/
void arregloDeEstudiantes(char ** nombres, int tamano);

/**
* @brief Lee las notas de los estudiantes y guardarlas en una matriz
* @param Arreglo de nombres, matriz de notas, filas y columnas
*/
void matrizDeNotas(char ** nombres, float ** notas, int estudiantes, int columnas);

/**
* @brief Calcula el promedio de las 3 primeras notas de la matriz y lo almacena en la cuarta columna
* @param Matriz de notas, filas y columnas
*/
void calcularPromedio(float ** notas, int estudiantes, int columnas);

/**
* @brief Lee las matriculas de los estudiantes 
* @param Arreglo de nombres, el de matriculas y las filas
*/
void arregloDeMatriculas(char ** nombres, int * matriculas, int estudiantes);

/**
* @brief Mostar tabla con datos 
* @param Arreglo de nombres y estudiantes
*/
void mostrarNombres(char ** nombres, int estudiantes);

/**
* @brief Mostrar el promedio total del curso 
* @param Matriz de notas y estudiantes 
* @return Promedio total
*/
float promedioTotal(float ** notas, int estudiantes);

/**
* @brief Mostar la matricula con mayor valor 
* @param Arreglo de nombres, arreglo de matriculas y estudiantes
*/
void mayorMatricula(char ** nombres, int * matriculas, int estudiantes);

/**
* @brief Mostar la mayor nota definitva 
* @param Arreglo de nombres, matriz de notas y estudiantes
*/
void notaMayor(char ** nombres, float ** notas, int estudiantes);


int main(int argc, char * argv[]) {
	
	printf("TRABAJO SEGUNDO CORTE.");
	printf("\n \n");
  
	//Cantidad de estudiantes
	int estudiantes;
	do{
		printf("Por favor ingrese la cantidad de estudiantes: ");
		estudiantes = leer_entero();
		if(estudiantes <= 0){
			printf("\nEl valor ingresado no es válido, ingrese un nuevo valor. \n");
		}
	}while(estudiantes <= 0);
	
	printf("\n");
	printf("NOMBRES DE LOS ESTUDIANTES.");
	printf("\n \n");
	//Arreglo para almacenar los nombres y los apellidos
	char ** nombres = (char **)malloc(estudiantes * sizeof(char *));
	arregloDeEstudiantes(nombres, estudiantes);
	
	printf("\n");
	printf("NOTAS.");
	printf("\n");
	//Matriz para almacenar las notas parciales y la definitiva
	//Inicialisamos las 4 columnas que va a tener nuestra matriz	
	int columnas = 4;
	float ** notas = (float **)malloc(estudiantes * sizeof(float *));
	if(notas == NULL){
		printf("Error al asignar memoria para la nota.\n");
		exit(1);
	}
	for(int i = 0; i < estudiantes; i++){
		notas[i] = (float *)malloc(columnas * sizeof(float));
	}
	matrizDeNotas(nombres, notas, estudiantes, columnas);
	calcularPromedio(notas, estudiantes, columnas);
	
	printf("\n");
	printf("MATRICULAS.");
	printf("\n \n");
	//Arreglo para almacenar los valores de la matricula
	int * matriculas = (int *)malloc(estudiantes * sizeof(int));
	if(matriculas == NULL){
		printf("Error al asignar memoria para las matriculas.\n");
		exit(1);
	}
	arregloDeMatriculas(nombres, matriculas, estudiantes);
	
	//Implementar el algoritmo
	printf("\n");
	printf("TABLA DE DATOS.");
	printf("\n \n");
	//Imprimimos una tabla con los datos
	printf("----------------------------------------------------------------\n");
	printf("%-21s %-5s %-5s %-5s %-8s %-10s\n", "|Estudiante", "|Nota1", "|Nota2", "|Nota3", "|Promedio", "|Matricula|");
	printf("----------------------------------------------------------------\n");
	for(int i = 0; i < estudiantes; i++){
		printf("|%-20s |%-5.1f |%-5.1f |%-5.1f |%-8.1f |%-9d|\n", nombres[i], notas[i][0], notas[i][1], notas[i][2], notas[i][3], matriculas[i]);
		printf("----------------------------------------------------------------\n");
	}
	
	printf("\n");
	printf("SINTESIS.");
	printf("\n \n");
	//Imprimimos el promedio total de curso}
	printf("El promedio total del curso es: %.1f\n", promedioTotal(notas, estudiantes));
	
	//Imprimimos el mayor valor de la matricula
	mayorMatricula(nombres, matriculas, estudiantes);
	
	//Imprimimos la mayor definitiva 
	notaMayor(nombres, notas, estudiantes);
	
	//Imprimmos las notas de los estudiantes mayores al promedio
	for(int i = 0; i < estudiantes; i++){
		if(notas[i][3] > promedioTotal(notas, estudiantes)){
			printf("El/La estudiante %s posee una nota definitiva mayor al promedio, la cual es: %.1f\n", nombres[i], notas[i][3]);
		}
	}
	
	//Liberamos memoria de arreglos y de la matriz
	free(nombres);
	free(notas);
	free(matriculas);
	
  return 0;
}

void notaMayor(char ** nombres, float ** notas, int estudiantes){
	
	float nota = 0.0;
	char * nombre;
	//Recorremos la matriz en busca de la nota mayor 
	for(int i = 0; i < estudiantes; i++){
		if(notas[i][3] > nota){
			nota = notas[i][3];
			nombre = nombres[i];
		}
	}
	printf("El/La estudiante %s obtuvo la mayor defintiva con una nota de: %.1f\n", nombre, nota);
}
void mayorMatricula(char ** nombres, int * matriculas, int estudiantes){
	
	int matriculaMayor = 0;
	char * nombreEstudiante;
	//Recorremos el arreglo en busca del mayor valor de la matricula 
	for(int i = 0; i < estudiantes; i++){
		if(matriculas[i] > matriculaMayor){
			nombreEstudiante = nombres[i];
			matriculaMayor = matriculas[i];
		}
	}
	printf("El/La estudiante %s posee la matricula con mayor valor, la cual es: %d\n", nombreEstudiante, matriculaMayor);
}

float promedioTotal(float ** notas, int estudiantes){
	
	float promedioTotal = 0.0, suma = 0.0;
	for(int i = 0; i < estudiantes; i++){
		suma += notas[i][3];
	}
	promedioTotal = suma / estudiantes;
	return promedioTotal;
}

void arregloDeMatriculas(char ** nombres, int * matriculas, int estudiantes){
	
	//Llenamos el arreglo de las matriculas
	for(int i = 0; i < estudiantes; i++){
		do{
			printf("Ingrese el valor de la matricula para el estudiante %s: ", nombres[i]);
			matriculas[i] = leer_entero();
			if(matriculas[i] < 0){
				printf("El valor ingresdo no es válido, ingreselo nuevamente.\n");
			}
		} while(matriculas[i] < 0);
	}
}

void calcularPromedio(float ** notas, int estudiantes, int columnas){
	
	float promedio, suma;
	for(int i = 0; i < estudiantes; i++){
		notas[i][3] = 0.0;
		suma = 0.0;
		for(int j = 0; j < columnas; j++){
			suma += notas[i][j];
		}
		
		promedio = suma / 3.0;
		notas[i][3] = promedio; //Almacenamos el promedio en la cuarta columna
	}
}

void matrizDeNotas(char ** nombres, float ** notas, int estudiantes, int columnas){
	
	//Llenamos la matriz con las notas de los estudiantes
	for(int i = 0; i < estudiantes; i++){
		printf("\nNotas de %s: \n", nombres[i]);
		for(int j = 0; j < columnas - 1; j++){
			do{
				printf("Ingrese la nota parcial %d: ", j + 1);
				notas[i][j] = leer_real();
				if(notas[i][j] < 0 || notas[i][j] > 5.0){
					printf("El valor ingresdo no es válido, ingreselo nuevamente.\n");
				}
				
			} while(notas[i][j] < 0 || notas[i][j] > 5.0);
		}
	}
}

void arregloDeEstudiantes(char ** nombres, int estudiantes){
	
	//Llenamos el arreglo con los nombres de los estudiantes
	for(int i = 0; i < estudiantes; i++){
		printf("Ingrese el nombre del estudiante %d: ", i + 1);
		nombres[i] = leer_linea(256);
	}
}

char * leer_linea(int max_tamano){
  char * linea;
  
  //Reservar memoria para la linea
  linea = (char *)malloc(max_tamano);
  
  //Validamos que la linea se leyo correctamente
  if(linea == NULL){
	  fprintf(stderr, "Error al leer la linea.\n");
	  return NULL;
  }
  
  //Rellenar la linea con el caracter nulo \0
  memset(linea, 0, max_tamano);
  
  //Limpiar el resto de la salida
  fflush(stdin);
  
  //Leer la linea por teclado
  fgets(linea, max_tamano, stdin);
  
  //Quitar el caracter de ENTER "\n" al final de la linea
  quitar_fin_de_linea(linea);
  
  return linea;
}
  
int leer_entero(){
  int numero;
  char * linea;
  //Leer una linea
  linea = leer_linea(80);
  
  //Validamos que la linea se leyo correctamente
  if(linea == NULL){
	  fprintf(stderr, "Error al leer la linea.\n");
	  return 1;
  }
  
  //Obtener un numero entero de la linea
  if (sscanf(linea, "%d", &numero) == 1) {
    return numero;
  }
  return 0;
}
    
    
float leer_real(){
  float numero;
  char * linea;
  //Leer una linea
  linea = leer_linea(80);
  
  //Validamos que la linea se leyo correctamente
  if(linea == NULL){
	  fprintf(stderr, "Error al leer la linea.\n");
	  return 1;
  }
  
  //Obtener un numero real de la linea
  if (sscanf(linea, "%f", &numero) == 1) {
    return numero;
  }
  return 0;
}
   
void quitar_fin_de_linea(char * linea){
  int len;
  
  //Calcular la longitud de la linea
  len = strlen(linea);
  
  //Validamos que la linea se leyo correctamente
  if(linea == NULL){
	  fprintf(stderr, "Error al leer la linea.\n");
	  return;
  }
  
  //fgets lee y guarda el ENTER al final de la linea, es decir
  //en la ultima posicion de la cadena antes de nulo
  while (len > 0 && (linea[len - 1] == '\n' || linea[len - 1] == '\r')) {
    linea[--len] = 0;
  }
}
