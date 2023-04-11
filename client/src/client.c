#include "client.h"
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip = "127.0.0.1";
	char* puerto = "4444";
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	config = iniciar_config();

	if (config == NULL) {
	    return 1;
	}

	char* path = config_get_string_value(config, "PATH");

	logger = log_create( path , "TP0", true, LOG_LEVEL_INFO );

	log_info(logger, "Soy un Log");


	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */


	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	conexion = crear_conexion(ip, puerto);

	char* clave = config_get_string_value(config, "CLAVE");

	enviar_mensaje(clave,conexion);







	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);


}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("../tp0.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");


	while(strcmp(leido,""))
	{
		log_info(logger, leido);
		leido = readline("> ");
	}

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	free(leido);

	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	char* leido = readline("> ");
	t_paquete* paquete = crear_paquete();


	while(strcmp(leido,""))
	{
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
		leido = readline("> ");
	}

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	free(leido);

	// Leemos y esta vez agregamos las lineas al paquete
	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config)
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
