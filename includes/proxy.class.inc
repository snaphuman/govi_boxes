<?php

include_once (dirname(__FILE__).'/govi_boxes.class.inc');
include_once (dirname(__FILE__).'/env.interface.inc');
include_once (dirname(__FILE__).'/container.class.inc');

class Proxy implements iEnv {

    private $containerName = 'govi-proxy';
    private $imageName = 'jwilder/nginx-proxy';
    private $imageTag = 'alpine';
    private $containerStatus = '';

    public function __construct() {

        $this->status();
    }

    // TODO: make this reusable
    public function getStatus () {

        print('[govi-boxes] ' . $this->containerName . ': ' . $this->containerStatus . PHP_EOL);
    }

    public function load () {

        $params = '-p 80:80 ';
        $params .= '-v /var/run/docker.sock:/tmp/docker.sock:ro ';
        $params .= $this->imageName . ':';
        $params .= $this->imageTag . ' ';

        if ($this->containerStatus == "running") {

            $output = $this->containerStatus;
        } else {

            $output = Container::run($this->containerName, $params);
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