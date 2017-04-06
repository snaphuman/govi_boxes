<?php

include_once (dirname(__FILE__).'/dnsmasq.class.inc');
include_once (dirname(__FILE__).'/proxy.class.inc');

class GoviBoxes {

    private $dnsmasq;
    private $proxy;
    private $db;

    public function __construct(
        Dnsmasq $dnsmasq,
        Proxy $proxy,
        DB $db
    ) {

        $this->dnsmasq = $dnsmasq;
        $this->proxy = $proxy;
        $this->db = $db;
    }

    public function setEnvUp() {

        $this->dnsmasq->load();
        $this->proxy->load();
        $this->db->load();
    }

    public function setEnvDown() {

        $this->dnsmasq->down();
        $this->proxy->down();
        $this->db->down();
    }

    public function getEnvStatus() {

        $this->dnsmasq->getStatus();
        $this->proxy->getStatus();
        $this->db->getStatus();
    }
}
