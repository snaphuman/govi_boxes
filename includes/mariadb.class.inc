<?php

include_once (dirname(__FILE__).'/govi_boxes.class.inc');
include_once (dirname(__FILE__).'/env.interface.inc');
include_once (dirname(__FILE__).'/container.class.inc');
include_once (dirname(__FILE__).'/config.class.inc');

class DB implements iEnv {

    public $conf = null;
    public $containerName = 'govi-db';
    public $containerStatus = '';
    private $imageName = 'mariadb';
    private $imageTag = 'latest';

    public function __construct() {

        $this->status();
        $this->conf = Config::readFile();
    }

    public function getStatus () {

        print('[govi-boxes] ' . $this->containerName . ': ' . $this->containerStatus . PHP_EOL);
    }

    public function load () {

        $params = '-e MYSQL_ROOT_PASSWORD=' . $this->conf->services->{govi-db}->rootPassword . ' ';
        $params .= '-v /var/lib/mysql:/var/lib/mysql ';
        $params .= $this->imageName . ':';
        $params .= $this->imageTag . ' ';
        //$params .= '--bind-address=0.0.0.0';
        //$params .= '--skip-networking=TRUE';

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

    public function configure ($user, $password, $db) {

        $serverIP = Container::getIP($this->containerName);

        $rootPasswd = $this->conf->services->{'govi-db'}->rootPassword . ' ';

        $query = "GRANT ALL PRIVILEGES ON " . $db . ".* TO '" . $user . "'@'%' IDENTIFIED BY '" . $password . "'; FLUSH PRIVILEGES;";

        $command = "mysql -uroot -p" . $rootPasswd . " -e \"" . $query . "\"";

        Container::exec($this->containerName, $command);
    }
}
