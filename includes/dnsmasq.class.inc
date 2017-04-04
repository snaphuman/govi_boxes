<?php

include_once (dirname(__FILE__).'/govi_boxes.class.inc');
include_once (dirname(__FILE__).'/env.interface.inc');
include_once (dirname(__FILE__).'/container.class.inc');

class Dnsmasq implements iEnv {

    private $containerName = 'govi-dns';
    private $imageName = 'andyshinn/dnsmasq';
    private $imageTag = 'latest';
    private $domainNAme = 'govi.box';
    private $host = '127.0.0.1';
    private $containerStatus = '';

    public function __construct() {

        $this->status();
    }

    public function getStatus () {

        print('[govi-boxes] ' . $this->containerName . ': ' . $this->containerStatus . PHP_EOL);
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

        Container::down($this->containerName, $this->containerStatus);

    }

    public function status () {
        $this->containerStatus = Container::status($this->containerName);
    }

}
