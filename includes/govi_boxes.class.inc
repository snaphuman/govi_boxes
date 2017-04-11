<?php

include_once (dirname(__FILE__).'/resolv.class.inc');
include_once (dirname(__FILE__).'/dnsmasq.class.inc');
include_once (dirname(__FILE__).'/proxy.class.inc');
include_once (dirname(__FILE__) . '/node.class.inc');

class GoviBoxes {

    private $dnsmasq;
    private $proxy;
    private $db;
    private $node;

    public function __construct(
        Dnsmasq $dnsmasq,
        Proxy $proxy,
        DB $db,
        Node $node
    ) {

        $this->dnsmasq = $dnsmasq;
        $this->proxy = $proxy;
        $this->db = $db;
        $this->node = $node;
    }

    public function setEnvUp() {

        Resolv::configure();

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

    public function addNode($opts) {

        if(!$this->checkDependencies() ||
           !$this->checkRequiredOptions($opts)) return;

        $this->node->add($opts);
    }

    public function checkRequiredOptions($opts) {

        $missing = implode(', ', array_keys($opts, null, true));

        if (in_array(null, $opts)) {
            print ("\033[01;31m[govi-boxes]\033[0m node: please provide required options: " . $missing . PHP_EOL);

            return false;
        }

        return true;

    }

    public function checkDependencies() {

        $deps = array(
            $this->dnsmasq,
            $this->proxy,
            $this->db
        );

        $notFound = '';

        foreach ($deps as $dep) {
            if ($dep->containerStatus !== 'running') {

                $notFound .= $dep->containerName . ' ';
            }
        }

        if (!empty(trim($notFound))) {
            print("\033[01;31m[govi-boxes]\033[0m node: cannot start node, service(s): " . $notFound . "not found" . PHP_EOL);

            return false;
        }

        return true;
    }
}
