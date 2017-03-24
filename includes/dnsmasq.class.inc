<?php

include_once (dirname(__FILE__).'/env.interface.inc');

class Dnsmasq implements iEnv {

    private $containerName = 'govi-dns';
    private $imageName = 'andyshinn/dnsmasq';
    private $imageTag = 'latest';
    private $domainNAme = 'govi.box';
    private $host = '127.0.0.1';
    private $containerStatus = '';

    public function status () {

        $output = json_decode(shell_exec("docker inspect " . $this->containerName), TRUE);

        return $this->containerName . ': ' . $output[0]['State']['Status'];
    }

    public function load () {

        if ($this->containerStatus = "running") {

            $output = 'Ya se encuentra corriendo';
        } else {

            $cmd = 'docker run -d --name ' . $this->containerName . ' -p 53:53/tcp -p 53:53/udp --cap-add=NET_ADMIN ' . $this->imageName . ':' . $this->imageTag . ' -A /' . $this->domainName . '/' . $this->host;
            $res = shell_exec($cmd);

            $output = 'Servicio iniciado -> ' . $res;
        }

        return $this->containerName . ': ' . $output;
    }

    public function down () {

        if ($this->containerStatus = 'running') {

            $cmd = 'docker stop ' . $this->containerName . ' && docker rm ' . $this->containerName;
            $res = shell_exec($cmd);

            $output = 'Servicio detenido -> ' . $res;
        } else {

            $output = 'No hay nada que detener -> ';
        }

        return $this->containerName . 'detenido: ' . $output;
    }
}