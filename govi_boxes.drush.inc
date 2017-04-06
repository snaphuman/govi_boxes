<?php

require_once(dirname(__FILE__) . '/includes/govi_boxes.class.inc');
require_once(dirname(__FILE__) . '/includes/connection.class.inc');
require_once(dirname(__FILE__) . '/includes/dnsmasq.class.inc');
require_once(dirname(__FILE__) . '/includes/proxy.class.inc');
require_once(dirname(__FILE__) . '/includes/mariadb.class.inc');

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

  return $items;
}

function govi_boxes_drush_help($section) {

  switch ($section) {

    case 'drush:govi-boxes-env':
      return "Este comando gestiona el ambiente de ejecución de Govimentum que incluye servidor dnsmasq, proxy reverso dinámico y motor de base de datos";

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
    new DB
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
