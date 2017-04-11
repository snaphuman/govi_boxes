<?php

require_once(dirname(__FILE__) . '/includes/govi_boxes.class.inc');
require_once(dirname(__FILE__) . '/includes/connection.class.inc');
require_once(dirname(__FILE__) . '/includes/dnsmasq.class.inc');
require_once(dirname(__FILE__) . '/includes/proxy.class.inc');
require_once(dirname(__FILE__) . '/includes/mariadb.class.inc');
require_once(dirname(__FILE__) . '/includes/node.class.inc');

/**
 * Implements hook_drush_command
 */

function govi_boxes_drush_command() {

  $items = array();

  $items['govi-boxes-env'] = array(
    'description' => 'El comando govi-boxes-env permite gestionar el ambiente de ejecución para la Distribución Distrital CMS: Govimentum',
    'aliases' => ['gbxe'],
    'arguments' => array(
      'status' => 'Muestra el estado de los contenedores del ambiente de ejecución de Govimentum',
      'up' => 'Inicializa los contenedores del ambiente de ejecución de Govimentum',
      'down' => 'Detiene los contenedores del ambiente de ejecución de Govimentum'
    ),
    'examples' => array(
      'drush gbxe status' => 'Muestra el estado de los contenedores del ambiente de Govimentum',
      'drush gbxe up' => 'Inicializa el ambiente de ejecución Govimentum',
      'drush gbxe down' => 'Detiene el ambiente de ejecución de Govimentum'
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_NONE
  );

  $items['govi-boxes-node'] = array(
      'description' => 'El comando govi-boxes-node permite gestionar los contenedores de aplicaciones con la Distribución CMS: Govimentum o sitios en Drupal',
      'aliases' => ['gbxn'],
      'arguments' => array(
          'ops' => 'Operaciones del nodo (add,remove,start,stop)',
      ),
      'options' => array(
          'sitename' => array(
              'description' => 'nombre del prefijo de URL de acceso al contenedor que compone el nombre de dominio de acceso al sitio con el esquema [site-name].govi.box',
          ),
          'path' => array(
              'description' => 'Ruta relativa donde se almacena la aplicación en la máquina host'
          ),
          'branch' => array(
              'description' => 'Nombre de la rama del repositorio Git que contiene el estado de la aplicación para ser desplegado en el contenedor.'
          ),
          'show' => array(
              'description' => 'Muestra el estado de los nodos (contenedores) de Govimentum existentes'
          ),
      ),
      'examples' => array(
          'drush gbxn add --prefix-url=mi-sitio --path=/home/user/projects/mi-sitio --branch=desarrollo' => 'Agrega un nuevo nodo de la aplicación',
          'drush gbxn remove --sitename mi-sitio' => 'Elimina el contenedor del nodo mi-sitio',
          'drush gbxn start --sitename mi-sitio' => 'Inicia el contenedor del nodo mi-sitio existente',
          'drush gbxn stop --sitename mi-sitio' => 'Detiene el contenedor del nodo mi-sitio',
          'drush gbxn stop-all' => 'Detiene todos los nodos activos',
          'drush gbxn show' => 'Muestra el estado de los nodos'
      ),
      'bootstrap' => DRUSH_BOOTSTRAP_NONE
  );

  return $items;
}

function govi_boxes_drush_help($section) {

  switch ($section) {

    case 'drush:govi-boxes-env':
      return "Este comando gestiona el ambiente de ejecución de Govimentum que incluye servidor dnsmasq, proxy reverso dinámico y motor de base de datos";

    case 'drush:govi-boxes-node':
      return "Este comando gestiona los nodos (contenedores de Docker) de la aplicación que conforman los ambientes de despliegue de Govimentum o Drupal" ;

    case 'drush:govi-boxes:title':
      return "Gestión de contenedores para Govimentum";

    case 'drush:govi-boxes:summary':
      return 'Automatiza la gestión del ambiente de ejecución y contenedores de Govimentum';
  }
}

function drush_govi_boxes_env($arg = 'status') {

  $docker = Connection::check();

  if (!$docker) return;

  $boxes = new GoviBoxes(
    new Dnsmasq,
    new Proxy,
    new DB,
    new Node
  );

  switch ($arg) {

    case 'status':

      return $boxes->getEnvStatus();
    case 'up':

      return $boxes->setEnvUp();
    case 'down':

      return $boxes->setEnvDown();
  }
}

function drush_govi_boxes_node($arg = 'show') {

    $docker = Connection::check();

    if (!$docker) return;

    $addOptions = array();
    $addOptions['siteName'] = drush_get_option('sitename');
    $addOptions['path'] = drush_get_option('path');
    $addOptions['branch'] = drush_get_option('branch');

    $show = drush_get_option('show');

    $boxes = new GoviBoxes(
        new Dnsmasq,
        new Proxy,
        new DB,
        new Node
    );

    switch ($arg) {

        case 'add':

            return $boxes->addNode($addOptions);
    }


}
