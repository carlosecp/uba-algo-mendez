#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Razas de Osos
// Posibles Resultados del Test
#define POLAR 'I'
#define PANDA 'P'
#define PARDO 'G'

// Canales de Television
#define ANIME 'A'
#define POP 'M'
#define LIMPIEZA 'L'

// Tipos de Alimento
#define BAMBU 'B'
#define PESCADO 'P'
#define FOCAS 'F'

// Multiplicadores de Puntaje
#define PTS_LIMPIEZA 1
#define PTS_ANIME 2
#define PTS_POP 3
#define PTS_FOCAS 3
#define PTS_BAMBU 6
#define PTS_PESCADO 9

// Maximos y Minimos de Intervalos
#define MAX_PISOS_TORRE 18
#define MIN_PISOS_TORRE 1
#define MAX_NIVEL_GRITO 18
#define MIN_NIVEL_GRITO 1

// Intervalos Resultados
#define MIN_PUNTAJE 5
#define MAX_POLAR 24
#define MAX_PANDA 43
#define MAX_PARDO 63

// Miniscula y mayuscula
#define MIN_MINUSCULA 'a'
#define MAX_MINUSCULA 'z'

/*
*	Pre: El argumento pasado a la funcion debe ser un caracter ASCII válido.
*	Post: La función determina si este caracter coincide o no coincide con alguna de las opciones de canales de televisión validos.
*/
bool es_canal_tv_valido(char letra_ingresada) {
	return (letra_ingresada == ANIME || letra_ingresada == POP || letra_ingresada == LIMPIEZA);
}

/*
*	Pre: El argumento pasado a la funcion debe ser un caracter ASCII válido.
*	Post: La función determina es este caracter coincide o no coincide con alguna de las opciones de tipos de alimentos válidos.
*/
bool es_alimento_valido(char alimento_ingresado) {
	return (alimento_ingresado == BAMBU || alimento_ingresado == PESCADO || alimento_ingresado == FOCAS);
}

/*
*	Pre: Esta función recibe como argumento 3 números reales enteros, dos de los cuales servirán para establecer la cota inferior e inferior del intérvalo evaluado. El número que corresponde a la cota inferior debe ser menor al que corresponde a la cota superior.
*	Post: La función determina si un valor evaluado se encuentra incluído dentro del intervalo establecido (intervalo cerrado).
*/
bool esta_incluido_en_intervalo(int cota_inferior, int cota_superior, int valor_a_evaluar) {
	return (cota_inferior <= valor_a_evaluar) && (valor_a_evaluar <= cota_superior);
}

/*
*	Pre: Esta función recibe un número real entero cualquiera, que representa el nivel de grito dado.
*	Post: Dictamina si el nivel de grito es considerado válido, es decir, si se encuentra entre los valores 1 y 18.
*/
bool es_nivel_grito_valido(int nivel_grito) {
	return esta_incluido_en_intervalo(MIN_NIVEL_GRITO, MAX_NIVEL_GRITO, nivel_grito);
}

/*
*	Pre: Esta función recibe un número real entero cualquiera, que representa el piso de una torre.
*	Post: Dictamina si el número de piso es considerado válido, es decir, si se encuentra entre los valores 1 y 18.
*/
bool es_piso_torre_valido(int piso_torre) {
	return esta_incluido_en_intervalo(MIN_PISOS_TORRE, MAX_PISOS_TORRE, piso_torre);
}

/*
*	Pre: Esta función recibe un caracter del alfabeto (códigos ascii entre los intevalos 64-90 o 97-122).
*	Post: Dictamina si el caracter recibido representa una letra minúscula (perteneciente al intérvalo 97-122).
*/
bool es_letra_minuscula(char letra_evaluada) {
	return ((letra_evaluada >= MIN_MINUSCULA) && (letra_evaluada <= MAX_MINUSCULA));
}

/*
*	Pre: Recibe un caracter que corresponda a alguna de las opciones válidas de canales de televisión 'A', 'M' o 'L' (case sensitive).
*	Post: Retorna el puntaje correcto según el canal de televisión ingresado.
*/
int calcular_puntaje_segun_canal_tv(char canal_ingresado) {
	int puntos_segun_canal;
	switch(canal_ingresado) {
		case ANIME:
			puntos_segun_canal = PTS_ANIME;
			break;
		case POP:
			puntos_segun_canal = PTS_POP;
			break;
		case LIMPIEZA:
			puntos_segun_canal = PTS_LIMPIEZA;
			break;
	}
	return puntos_segun_canal;
}

/*
*	Pre: Recibe un caracter que corresponda a alguna de las opciones válidas de tipos de alimentos 'B', 'P' o 'F' (case sensitive).
*	Post: Retorna el puntaje correcto según el tipo de alimento ingresado.
*/
int calcular_puntaje_segun_alimento(char alimento_ingresado) {
	int puntos_segun_alimento;
	switch(alimento_ingresado) {
		case BAMBU:
			puntos_segun_alimento = PTS_BAMBU;
			break;
		case PESCADO:
			puntos_segun_alimento = PTS_PESCADO;
			break;
		case FOCAS:
			puntos_segun_alimento = PTS_FOCAS;
			break;
	}
	return puntos_segun_alimento;
}

/*
*	Pre: Recibe los puntajes asignados según todas las opciones seleccionadas durante el test. Todos ellos son enteros generados de manera automáticas por las funciones encargadas de asignar estos puntajes.
*	Post: Calcula el puntaje final del test de personalidad basándose en la fórmula establecida según los resultados de cada pregunta.
*/
int calcular_puntaje_total(int pts_segun_alimento, int pts_segun_canal_tv, int pts_nivel_grito, int pts_piso_torre) {
	return (pts_segun_alimento * pts_segun_canal_tv) + pts_piso_torre + pts_nivel_grito;
}

/*
*	Pre: -
*	Post: La función recibe una respuesta del usuario cuando se le pregunta sobre qué tipo de alimento prefiere en su vianda. Cuando el usuario ingresa una opción válida, esta función devuelve el puntaje correspondiente al alimento ingresado.
*/
int resultados_alimento() {
	char alimento_ingresado;
	do {
		printf("-> Solo podes guardar un alimento en tu vianda - Bambú (B), Pescado (P), Focas (F): ");
		scanf(" %c", &alimento_ingresado);
	} while(!es_alimento_valido(alimento_ingresado));
	return calcular_puntaje_segun_alimento(alimento_ingresado);
}

/*
*	Pre: -
*	Post: La función recibe una respuesta del usuario cuando se le pregunta sobre qué tipo canal de televisión prefiere. Cuando el usuario ingresa una opción válida, esta función devuelve el puntaje correspondiente al canal ingresado.
*/
int resultados_canal_tv() {
	char canal_ingresado;
	do {
		printf("-> Vas a ver televisión un rato, pones el canal de - Anime (A), Musica Pop (M), Limpieza (L): ");
		scanf(" %c", &canal_ingresado);
	} while(!es_canal_tv_valido(canal_ingresado));
	return calcular_puntaje_segun_canal_tv(canal_ingresado);
}

/*
*	Pre: -
*	Post: La función recibe una respuesta del usuario cuando se le pregunta nivel de grito se ha registrado. Cuando el usuario ingresa un valor válido, esta función devuelve ese nivel de grito.
*/
int resultados_nivel_grito() {
	int nivel_grito_ingresado;
	do {
		printf("-> ¡Oh, una rata! ¿Que tan fuerte gritas del 1 al 18? Siendo 1 no gritar y 18 desgarrarse la garganta: ");
		scanf(" %i", &nivel_grito_ingresado);
	} while(!es_nivel_grito_valido(nivel_grito_ingresado));
	return nivel_grito_ingresado;
}

/*
*	Pre: -
*	Post: La función recibe una respuesta del usuario cuando se le pregunta piso de la torre donde le gustaría vivir. Cuando el usuario ingresa un valor válido, esta función devuelve el piso ingresado.
*/
int resultados_piso_torre() {
	int piso_torre_ingresado;
	do {
		printf("-> Te compras una torre con tus dos hermanos de 18 pisos. ¿En que piso te gustaría vivir?: ");
		scanf(" %i", &piso_torre_ingresado);
	} while(!es_nivel_grito_valido(piso_torre_ingresado));
	return piso_torre_ingresado;
}

/*
*	Pre: Recibe un número real entero que representa el resultado calculado del total de punto obtenidos durante el test.
*	Post: Dictamina qué tipo de personalidad representa mejor al usuario en base al puntaje obtenido y los puntajes que representan a cada personalidad.
*/
void asignar_personalidad(int pts_totales) {
	char *personalidad_asignada;
	if (pts_totales >= MIN_PUNTAJE && pts_totales <= MAX_POLAR)
	{
		personalidad_asignada = "Polar (I)";
	}
	else if (pts_totales <= MAX_PANDA)
	{
		personalidad_asignada = "Panda (P)";
	}
	else
	{
		personalidad_asignada = "Pardo (G)";
	}
	printf("- %s -", personalidad_asignada);
}

int main() {
	printf("*==================================================*\n");
	printf("\tTest de Personalidad Escandaloza\n");
	printf("*==================================================*\n\n");

	int pts_segun_canal_tv = resultados_canal_tv();
	int pts_segun_alimento = resultados_alimento();
	int pts_piso_torre = resultados_piso_torre();
	int pts_nivel_grito = resultados_nivel_grito();

	int pts_totales = calcular_puntaje_total(pts_segun_alimento, pts_segun_canal_tv, pts_nivel_grito, pts_piso_torre);
	asignar_personalidad(pts_totales);

	return 0;
}
