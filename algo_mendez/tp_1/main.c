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

// Maximos
#define MIN_INTERVALOS 1
#define MAX_PISOS_TORRE 18
#define MAX_NIVEL_GRITO 18

// Intervalos Resultados
#define MIN_POLAR 5
#define MAX_POLAR 24
#define MAX_PANDA 43
#define MAX_PARDO 63

bool es_canal_tv_valido(char letra_ingresada) {
	return (letra_ingresada == ANIME || letra_ingresada == POP || letra_ingresada == LIMPIEZA);
}

bool es_alimento_valido(char alimento_ingresado) {
	return (alimento_ingresado == BAMBU || alimento_ingresado == PESCADO || alimento_ingresado == FOCAS);
}

bool esta_incluido_en_intervalo(bool es_intervalo_cerrado, int cota_inferior, int cota_superior, int valor_a_evaluar) {
	if (es_intervalo_cerrado)
		return (cota_inferior <= valor_a_evaluar) && (valor_a_evaluar <= cota_superior);
	else
		return (cota_inferior < valor_a_evaluar) && (valor_a_evaluar < cota_superior);
}

bool es_nivel_grito_valido(int nivel_grito) {
	bool es_intervalo_cerrado = true;
	return esta_incluido_en_intervalo(es_intervalo_cerrado, MIN_INTERVALOS, MAX_NIVEL_GRITO, nivel_grito);
}

bool es_piso_torre_valido(int piso_torre) {
	bool es_intervalo_cerrado = true;
	return esta_incluido_en_intervalo(es_intervalo_cerrado, MIN_INTERVALOS, MAX_PISOS_TORRE, piso_torre);
}

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

int resultados_alimento() {
	char alimento_ingresado;
	do {
		printf("Solo podes guardar un alimento en tu vianda - Bambú (B), Pescado (P), Focas (F):");
		scanf(" %c", &alimento_ingresado);
	} while(!es_alimento_valido(alimento_ingresado));
	return calcular_puntaje_segun_alimento(alimento_ingresado);
}

int resultados_canal_tv() {
	char canal_ingresado;
	do {
		printf("Vas a ver televisión un rato, pones el canal de - Anime (A), Musica Pop (M), Limpieza (L): ");
		scanf(" %c", &canal_ingresado);
	} while(!es_canal_tv_valido(canal_ingresado));
	return calcular_puntaje_segun_canal_tv(canal_ingresado);
}

int resultados_nivel_grito() {
	int nivel_grito_ingresado;
	do {
		printf("¡Oh, una rata! ¿Que tan fuerte gritas del 1 al 18? Siendo 1 no gritar y 18 desgarrarse la garganta: ");
		scanf(" %i", &nivel_grito_ingresado);
	} while(!es_nivel_grito_valido(nivel_grito_ingresado));
	return nivel_grito_ingresado;
}

int resultados_piso_torre() {
	int piso_torre_ingresado;
	do {
		printf("Te compras una torre con tus dos hermanos de 18 pisos. ¿En que piso te gustaría vivir?: ");
		scanf(" %i", &piso_torre_ingresado);
	} while(!es_nivel_grito_valido(piso_torre_ingresado));
	return piso_torre_ingresado;
}

int calcular_puntaje_total(int pts_segun_alimento, int pts_segun_canal_tv, int pts_nivel_grito, int pts_piso_torre) {
	return (pts_segun_alimento * pts_segun_canal_tv) + pts_piso_torre + pts_nivel_grito;
}

void asignar_personalidad(int pts_totales) {
	char *descripcion_resultados;
	char *personalidad_asignada;
	if (pts_totales >= MIN_POLAR && pts_totales <= MAX_POLAR)
	{
		descripcion_resultados = ("Podes ser el más jove, pero eso no te quita tu madurez.");
		personalidad_asignada = "Polar";
	}
	else if (pts_totales <= MAX_PANDA)
	{
		descripcion_resultados = ("Parece que sos el mas tierno y delicado del trío.");
		personalidad_asignada = "Panda";
	}
	else if (pts_totales <= MAX_PARDO)
	{
		descripcion_resultados = ("¿Cómo te va siendo el líder del trío?");
		personalidad_asignada = "Pardo";
	}
	printf("Obtuviste %i puntos. Después de un arduo análisis, el súper test de personalidad determinó que tu personalidad escandalosa coincide con la de: — %s —", pts_totales, personalidad_asignada);
}

int main() {
	int pts_segun_alimento = resultados_alimento();
	int pts_segun_canal_tv = resultados_canal_tv();
	int pts_nivel_grito = resultados_nivel_grito();
	int pts_piso_torre = resultados_piso_torre();

	int pts_totales = calcular_puntaje_total(pts_segun_alimento, pts_segun_canal_tv, pts_nivel_grito, pts_piso_torre);
	asignar_personalidad(pts_totales);

	return 0;
}
