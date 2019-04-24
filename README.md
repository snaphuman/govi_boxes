# Gestor de contenedores govi_boxes

Govi_boxes es un set de comandos de Drush que facilita la gestión del ambiente
de despliegue e instancias de Drupal o Govimentum bajo demanda a través de
contenedores de Docker. Esta herramienta está orientada a desarrolladores de
Drupal puesto que permite la creación y organización de sitios web en los
entornos locales de desarrollo. 

Nota: Esta es una herramienta en fase beta de desarrollo, por lo que no se
recomienda su uso en ambientes de producción.

## Pre-Requisitos

* Git
* PHP
* [Composer](https://getcomposer.org/download)
* [Drush 8.x-dev](https://docs.drush.org/en/8.x/install-alternative) 
* Cliente Mariadb 


## Descarga e instalación

Ingresar al directorio local de Drush

```
cd ~/.drush
```

Clonar el repositorio govi_boxes

```
git clone https://github.com/snaphuman/govi_boxes
```

Borrar la cache de Drush

```
drush cc drush
```

## Configuración 

Antes de inicializar el ambiente de despliegue de Drupal y crear el primer nodo, es necesario aplicar la configuración de conexión con el servicio de base de datos _govi\_db_ y la declaración del primer nodo con los parámetros de conexión con base datos y acceso ssh. 

Ingresar al directorio de govi_boxes

```
cd ~/.drush/govi_boxes
```

Crear una copia del archivo de configuración de ejemplo

```
cp config.example.json config.json
```

Configurar los valores de las credenciales de conexión con bases de datos

```javascript
{
  "services": {
    "govi-db": {
      "rootPassword": "secret"
    }
  },
  "nodes": {
    "drupal8": {
      "db": {
        "user": "my-user",
        "password": "secret",
        "name": "my-db"
      },
      "ssh": {
        "port": "22220",
        "authType": "publicKey",
        "file": "$HOME/.drush/govi_boxes/keys/authorized_keys",
        "password": ""
      }
    }
}

```

Crear llave pública y agregarla al archivo authorized_keys que será usado para acceder al nodo via ssh

```
cd .
ssh-keygen
mkdir ~/.drush/govi_boxes/keys
cat ~/,ssh/id_rsa.pub > ~/.drush/govi_boxes/keys/authorized_keys
```

## Descargar Drupal

Ingresar al directorio en donde se almacenan los proyectos. ej: mis-proyectos y obtener el core de Drupal (o Govimentum) ya sea a través de Git o Drush


```
cd mis-proyectos
drush dl drupal --drupal-project-rename=drupal8 
```

## Inicializar el ambiente de despliegue

Para inicializar el ambiente de despliegue con govi_boxes, se debe asegurar que
las operaciones con docker se ejecuten sin el comand sudo (las siguientes
operaciones deben ejecutarse una sola vez)

```
sudo groupadd docker
sudo gmasswd -a $USER docker
newgrp docker
```

Inicializar docker

```
sudo systemctl start docker
```

Inicializar el ambiente de despliegue con Govi_boxes

```
drush govi-boxes-env up
```
ó a través del alias

```
drush gbxe up
```

Esta operación solicitará escribir en el archivo resolv.conf para configurar los
requerimientos de la red local con el servicio dns

```
[govi-boxes] resolv.conf file will be modified to reach proxy network requirements and password will be required to allow this operation.
¿can I proceed? (no/yes): yes
```

Verificar que los servicios dnsmaq, proxy reverso y mysql estén arriba

Con Govi_boxes:

```
drush gbxe status
[govi-boxes] connected
[govi-boxes] govi-dns: running
[govi-boxes] govi-proxy: running
[govi-boxes] govi-db: running
```

Con docker:

```
docker ps
```

Nota: Si es la primera vez que se inicializa el ambiente de despliegue, docker
descargará las imágenes de los servicios dnsmasq, mariadb y nginx-proxy. Esta
operación puede tardar varios minutos.


## Desplegar nodo de Drupal8

Agregar un nuevo nodo

```
drush gbxn add --sitename="drupal8" --path="$HOME/mis-proyectos/drupal8" --branch="test" --fresh-install=true
```

Nota: Si es la primera vez que se inicializa el nodo de Drupal8, docker
descargará la imágen govi_doker que configura el entorno con el servicio web para aplicaciones PHP. Esta
operación puede tardar varios minutos.

