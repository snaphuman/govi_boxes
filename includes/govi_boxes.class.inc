<?php

include_once (dirname(__FILE__).'/dnsmasq.class.inc');
include_once (dirname(__FILE__).'/proxy.class.inc');

class GoviBoxes extends Connection {

    private $dnsmasq;
    private $proxy;

    public function __construct(Dnsmasq $dnsmasq, Proxy $proxy) {

        $this->dnsmasq = $dnsmasq;
        $this->proxy = $proxy;
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
