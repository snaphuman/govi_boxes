<?php

include_once (dirname(__FILE__).'/connection.class.inc');
include_once (dirname(__FILE__).'/env.interface.inc');

class Dnsmasq implements iEnv {

    private $containerName = 'govi-dns';
    private $imageName = 'andyshinn/dnsmasq';
    private $imageTag = 'latest';
    private $domainNAme = 'govi.box';
    private $host = '127.0.0.1';
    private $containerStatus = '';

    public function __construct() {

        $this->connection = Connection::instance();

        if (!$this->connection->check()) return;

        $this->status();
    }

    public function getStatus () {

        print('[govi-boxes] ' . $this->containerName . ': ' . $this->containerStatus . PHP_EOL);
    }

    public function status () {

        $cmd = "docker inspect " . $this->containerName;
        $output = json_decode(shell_exec("docker inspect " . $this->containerName), TRUE);

        $status = $output[0]['State']['Status'];

        $this->containerStatus = empty($status) ? "not running" : $status;

    }

    public function load () {

        if ($this->containerStatus == "running") {

            $output = $this->containerStatus;
        } else {

            $cmd = 'docker run -d --name ' . $this->containerName . ' -p 53:53/tcp -p 53:53/udp --cap-add=NET_ADMIN ' . $this->imageName . ':' . $this->imageTag . ' -A /' . $this->domainName . '/' . $this->host;

            $output = shell_exec($cmd);
        }

        print ('[govi-boxes] ' . $this->containerName . ': ' . $output . PHP_EOL);
    }

    public function down () {

        if ($this->containerStatus == "running") {

            $cmd = 'docker stop ' . $this->containerName . ' && docker rm ' . $this->containerName;
            $output = 'stopped and removed ' . shell_exec($cmd);

        } else {

            $output = 'nothing to stop';
        }

        print ('[govi-boxes]' . $this->containerName . ': ' . $output . PHP_EOL);
    }
}
