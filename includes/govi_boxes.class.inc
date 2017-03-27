<?php

include_once (dirname(__FILE__).'/dnsmasq.class.inc');
include_once (dirname(__FILE__).'/proxy.class.inc');

class GoviBoxes {

    private $socket = 'unix:///var/run/docker.sock';
    private $conn = FALSE;
    private $dnsmasq;
    private $proxy;

    public function __construct(Dnsmasq $dnsmasq, Proxy $proxy) {

        $this->dnsmasq = $dnsmasq;
        $this->proxy = $proxy;
        self::connection();
    }

    public function setEnvUp() {

        $out = $this->dnsmasq->load();
        $out .= $this->proxy->load();

        return $out;

    }

    public function setEnvDown() {

        $this->dnsmasq->down();
        $this->proxy->down();
    }

    public function getEnvStatus() {

        $this->dnsmasq->getStatus();
        $this->proxy->getStatus();
    }

    public function connection () {

        $client = stream_socket_client($this->socket, $errno, $errorMessage);

        if ($client == FALSE) {

            //throw new UnexpectedValueException('Failed to connect: '.$errno);
            $this->conn = FALSE;
        } else {

            // we are just checking the connection to the socket,
            // so there is not need to keep it open
            $this->conn = TRUE;
            fclose($client);
        }


    }
}
