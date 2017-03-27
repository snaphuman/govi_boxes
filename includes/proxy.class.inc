<?php

include_once (dirname(__FILE__).'/env.interface.inc');

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

        return $this->containerName . ': ' . $this->containerStatus;
    }

    // TODO: make this reusable
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

            $cmd = 'docker run -d --name ' . $this->containerName . ' -p 80:80 -v /var/run/docker.sock:/tmp/docker.sock:ro ' . $this->imageName . ':' . $this->imageTag;

            $output = shell_exec($cmd);
        }

        return $this->containerName . ': ' . $output . '\n';
    }

    // TODO: make this reusable
    public function down () {

        if ($this->containerStatus == "running") {

            $cmd = 'docker stop ' . $this->containerName . ' && docker rm ' . $this->containerName;
            $output = 'stopped and removed ' . shell_exec($cmd);

        } else {

            $output = 'nothing to stop';
        }

        return $this->containerName . ': ' . $output;
    }

}