#include "test_de_personalidad.h"
#include "inicializar_elementos.h"

/** 
 * Determina si el canal de televisión ingresado es válido (Ánime, Pop o Limpieza).
 * @param letra_ingresada Canal de televisión ingresado por el usuario. Debe ser un caracter ASCII válido.
 * @return Verdadero si el canal de televisión ingresado es válido.
*/
bool es_canal_tv_valido(char letra_ingresada)
{
	return (letra_ingresada == ANIME || letra_ingresada == POP || letra_ingresada == LIMPIEZA);
}

/** 
 * Determina si el tipo de alimento ingresado es válido (Focas, Bambú o Pescado).
 * @param letra_ingresada Tipo de alimento ingresado por el usuario. Debe ser un caracter ASCII válido.
 * @return Verdadero si el tipo de alimento ingresado es válido.
*/
bool es_alimento_valido(char alimento_ingresado)
{
	return (alimento_ingresado == BAMBU || alimento_ingresado == PESCADO || alimento_ingresado == FOCAS);
}

/** 
 * Determina si un número ingresado por el usuario cabe dentro de un intervalo numérico determinado.
 * @param cota_inferior Número real que representa el mínimo valor permitido en el intervalo (incluyente).
 * @param cota_superior Número real que representa el máximo valor permitido en el intervalo (incluyente).
 * @param valor_a_evaluar Número ingresado por el usuario.
 * @return Verdadero número ingresado cabe dentro del intervalo numérico especificado.
*/
bool esta_incluido_en_intervalo(int cota_inferior, int cota_superior, int valor_a_evaluar)
{
	return (cota_inferior <= valor_a_evaluar) && (valor_a_evaluar <= cota_superior);
}

/** 
 * Determina si el nivel de grito ingresado por el usuario es válido.
 * @param nivel_grito Nivel de grito ingresado por el usuario.
 * @return Verdadero si el nivel de grito ingresado por el usuario es válido.
*/
bool es_nivel_grito_valido(int nivel_grito)
{
	return esta_incluido_en_intervalo(MIN_NIVEL_GRITO, MAX_NIVEL_GRITO, nivel_grito);
}

/** 
 * Determina si el piso de la torre ingresado por el usuario es válido.
 * @param nivel_grito Piso de la torre ingresado por el usuario.
 * @return Verdadero si el piso de la torre ingresado por el usuario es válido.
*/
bool es_piso_torre_valido(int piso_torre)
{
	return esta_incluido_en_intervalo(MIN_PISOS_TORRE, MAX_PISOS_TORRE, piso_torre);
}

/** 
 * Determina si la letra ingresada por el usuario es minúscula.
 * @param letra_evaluada Letra ingresada por el usuario. Debe ser un caracter ASCII válido.
 * @return Verdadero si el caracter evaluado es minúscula.
*/
bool es_letra_minuscula(char letra_evaluada)
{
	return ((letra_evaluada >= MIN_MINUSCULA) && (letra_evaluada <= MAX_MINUSCULA));
}

/** 
 * Calcula el puntaje correcto según el canal de televisión ingresado.
 * @param canal_ingresado Recibe un caracter que corresponda a alguna de las opciones válidas de canales de televisión 'A', 'M' o 'L' (case sensitive).
 * @return Retorna el puntaje correcto según el canal de televisión ingresado.
*/
int calcular_puntaje_segun_canal_tv(char canal_ingresado)
{
	int puntos_segun_canal;
	switch (canal_ingresado)
	{
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

/** 
 * Calcula el puntaje correcto según el tipo de alimento ingresado.
 * @param alimento_ingresado Recibe un caracter que corresponda a alguna de las opciones válidas de tipos de alimentos 'B', 'P' o 'F' (case sensitive).
 * @return Retorna el puntaje correcto según el tipo de alimento ingresado.
*/
int calcular_puntaje_segun_alimento(char alimento_ingresado)
{
	int puntos_segun_alimento;
	switch (alimento_ingresado)
	{
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

/**
 * Calcula el puntaje total del test de personalidad.
 * @param pts_segun_alimento Recibe el punta según el tipo de alimento ingresado (calculado automáticamente por las funciones que calculan el puntaje de cada pregunta). 
 * @param pts_segun_canal_tv Recibe el punta según el canal de televisión ingresado (calculado automáticamente por las funciones que calculan el puntaje de cada pregunta). 
 * @param pts_nivel_grito Recibe el punta según el nivel de grito ingresado (calculado automáticamente por las funciones que calculan el puntaje de cada pregunta). 
 * @param pts_piso_torre Recibe el punta según el piso de la torre ingresado (calculado automáticamente por las funciones que calculan el puntaje de cada pregunta). 
 * @return Puntaje total del test de personalidad.
*/
int calcular_puntaje_total(int pts_segun_alimento, int pts_segun_canal_tv, int pts_nivel_grito, int pts_piso_torre)
{
	return (pts_segun_alimento * pts_segun_canal_tv) + pts_piso_torre + pts_nivel_grito;
}

/** 
 * Realiza la pregunta sobre el tipo de alimento preferido para el usuario y devuelve el puntaje correspondiente en base a su respuesta.
 * @return Puntaje correspondiente en base al tipo de alimento preferido para el usuario.
*/
int resultados_alimento()
{
	char alimento_ingresado;
	do
	{
		printf(" » Solo podes guardar un alimento en tu vianda - Bambú (B), Pescado (P), Focas (F): ");
		scanf(" %c", &alimento_ingresado);
	} while (!es_alimento_valido(alimento_ingresado));
	return calcular_puntaje_segun_alimento(alimento_ingresado);
}

/** 
 * Realiza la pregunta sobre el canal de televisión preferido para el usuario y devuelve el puntaje correspondiente en base a su respuesta.
 * @return Puntaje correspondiente en base al canal de televisión preferido para el usuario.
*/
int resultados_canal_tv()
{
	char canal_ingresado;
	do
	{
		printf(" » Vas a ver televisión un rato, pones el canal de - Anime (A), Musica Pop (M), Limpieza (L): ");
		scanf(" %c", &canal_ingresado);
	} while (!es_canal_tv_valido(canal_ingresado));
	return calcular_puntaje_segun_canal_tv(canal_ingresado);
}

/** 
 * Realiza la pregunta sobre el nivel de grito del usuario y devuelve el puntaje correspondiente en base a su respuesta.
 * @return Puntaje correspondiente en base al nivel de grito del usuario.
*/
int resultados_nivel_grito()
{
	int nivel_grito_ingresado;
	do
	{
		printf(" » ¡Oh, una rata! ¿Que tan fuerte gritas del 1 al 18? Siendo 1 no gritar y 18 desgarrarse la garganta: ");
		scanf(" %i", &nivel_grito_ingresado);
	} while (!es_nivel_grito_valido(nivel_grito_ingresado));
	return nivel_grito_ingresado;
}

/** 
 * Realiza la pregunta sobre el piso de la torre preferido para el usuario y devuelve el puntaje correspondiente en base a su respuesta.
 * @return Puntaje correspondiente en base al piso de la torre preferido para el usuario.
*/
int resultados_piso_torre()
{
	int piso_torre_ingresado;
	do
	{
		printf("-> Te compras una torre con tus dos hermanos de 18 pisos. ¿En que piso te gustaría vivir?: ");
		scanf(" %i", &piso_torre_ingresado);
	} while (!es_nivel_grito_valido(piso_torre_ingresado));
	return piso_torre_ingresado;
}

/** 
 * Determina la personalidad del pesronaje del usuario en base a las preguntas respondidas.
 * @pre Deben haberse calculado los resultados individuales de cada pregunta del test de personalidad.
 * @param pts_totales Puntaje final del test de personalidad, calculado utilizando la fórmula especificada.
 * @return Letra que representa la personalidad que se le ha asignado al personaje del usuario.
*/
char asignar_personalidad(int pts_totales)
{
	char personalidad_asignada;
	if (pts_totales >= MIN_PUNTAJE && pts_totales <= MAX_POLAR)
	{
		personalidad_asignada = POLAR;
	}
	else if (pts_totales <= MAX_PANDA)
	{
		personalidad_asignada = PARDO;
	}
	else
	{
		personalidad_asignada = PANDA;
	}
	printf("Personalidad Asginada: %c\n", personalidad_asignada);
	return personalidad_asignada;
}

void test_de_personalidad(char *personalidad_detectada)
{
	system("clear");
	renderizar_introduccion();
	renderizar_bordes_estadisticas();
	printf(" TEST DE PERSONALIDAD ESCANDALOZA\n");
	renderizar_bordes_estadisticas();

	int pts_segun_canal_tv = resultados_canal_tv();
	int pts_segun_alimento = resultados_alimento();
	int pts_piso_torre = resultados_piso_torre();
	int pts_nivel_grito = resultados_nivel_grito();

	int pts_totales = calcular_puntaje_total(pts_segun_alimento, pts_segun_canal_tv, pts_nivel_grito, pts_piso_torre);

	*personalidad_detectada = asignar_personalidad(pts_totales);
	*personalidad_detectada = 'P';
}
