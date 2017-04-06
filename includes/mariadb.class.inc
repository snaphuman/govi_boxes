<?php

include_once (dirname(__FILE__).'/govi_boxes.class.inc');
include_once (dirname(__FILE__).'/env.interface.inc');
include_once (dirname(__FILE__).'/container.class.inc');

class DB implements iEnv {

    private $containerName = 'govi-db';
    private $imageName = 'mariadb';
    private $imageTag = 'latest';
    private $containerStatus = '';

    public function __construct() {

        $this->status();
    }

    public function getStatus () {

        print('[govi-boxes] ' . $this->containerName . ': ' . $this->containerStatus . PHP_EOL);
    }

    public function load () {

        $params .= '-e MYSQL_ROOT_PASSWORD=secreto ';
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