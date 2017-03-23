<?php

include_once (dirname(__FILE__).'/dnsmasq.class.inc');

class GoviBoxes {

    private $socket = 'unix:///var/run/docker.sock';
    private $conn = FALSE;

    public function __construct() {

        self::connection();
    }

    public function setEnvUp() {

        $dnsmasq = new Dnsmasq;

        return $dnsmasq->load();

    }

    public function setEnvDown() {

        $dnsmasq = new Dnsmasq;

        return $dnsmasq->down();
    }

    public function getEnvStatus() {

        $dnsmasq = new Dnsmasq;

        return $dnsmasq->status();
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