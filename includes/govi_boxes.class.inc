<?php

include_once (dirname(__FILE__).'/connection.class.inc');
include_once (dirname(__FILE__).'/dnsmasq.class.inc');
include_once (dirname(__FILE__).'/proxy.class.inc');

class GoviBoxes {

    private $connection;
    private $dnsmasq;
    private $proxy;

    public function __construct(Dnsmasq $dnsmasq, Proxy $proxy) {

        $this->dnsmasq = $dnsmasq;
        $this->proxy = $proxy;

        $this->connection = Connection::instance();
        if (!$this->connection->check()) return;
    }

    public function setEnvUp() {

        $this->dnsmasq->load();
        $this->proxy->load();
    }

    public function setEnvDown() {

        $this->dnsmasq->down();
        $this->proxy->down();
    }

    public function getEnvStatus() {

            $this->dnsmasq->getStatus();
            $this->proxy->getStatus();
    }
}
