<?php

include_once (dirname(__FILE__).'/dnsmasq.class.inc');

class GoviBoxes {

    private $socket = 'unix:///var/run/docker.sock';
    private $conn = FALSE;
    private $dnsmasq;

    public function __construct() {

        $this->dnsmasq = new Dnsmasq;
        self::connection();
    }

    public function setEnvUp() {

        return $this->dnsmasq->load();

    }

    public function setEnvDown() {

        return $this->dnsmasq->down();
    }

    public function getEnvStatus() {

        return $this->dnsmasq->status();
    }

    public function connection () {

        if (!stream_socket_client($this->socket)) {
            $this->conn = TRUE;
            die('No pude conectarme al socket');
        } else {
            $this->conn = TRUE;
        }
    }
}