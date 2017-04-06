# Gestor de contenedores govi_boxes

Esta herramienta es un set de comandos de Drush para la gestión de contenedores de Docker que implementan servicios y ambientes de despliegue de la Distribución Distrital CMS: Govimentum que incluye servicios como:

* dnsmasq
* nginx-proxy
* mariadb

Igualmente permite gestionar la creación de nuevos nodos (Contenedores de govimentum) para los ambientes de despliegue que requiera el proyeto. ej: pruebas, calidad, desarrollo, producción, etc.
Cada nodo es una instancia de la imágen de Docker govi_docker que incluye los siguientes servicios:

* nginx
* php-fpm 5.6x
* php 5.6x
* drush
* composer




