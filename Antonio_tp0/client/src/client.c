#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* clave;

	char* message = "Hola! Soy un log";

	t_log* logger;
	t_config* config;
	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	log_info(logger, message);

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */


	config = iniciar_config();

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	clave = config_get_string_value(config, "CLAVE");

	log_info(logger, "La clave: %s, IP: %s, Puerto: %s\n", clave,ip,puerto);



	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);
	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(clave, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);
}

//funciones:

t_log* iniciar_logger(void)
{
	return log_create("tp0.log","TP0",1,LOG_LEVEL_INFO);
}

t_config* iniciar_config(void)
{
	t_config* nuevoConfig;

	return nuevoConfig;
}


void leer_consola(t_log* logger)
{
	char* leido;
	const char* vacio;
	vacio = "";

	do{
		leido = readline("> ");
	    log_info(logger, leido);
	}
	while (strcmp(leido,vacio) != 0);
}


void paquete(int conexion)
{
	t_paquete* paquete;
	int longitud;

	paquete = crear_paquete();
	char* valor = "antonio";
	longitud = strlen(valor);

	agregar_a_paquete(paquete, valor, longitud+1);
	enviar_paquete(paquete,conexion);
	eliminar_paquete(paquete);
}


void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}

char *config_get_string_value(t_config *self, char *key) {
	return dictionary_get(self->properties, key);
}
