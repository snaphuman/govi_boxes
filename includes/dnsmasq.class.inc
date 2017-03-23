<?php

include_once (dirname(__FILE__).'/env.interface.inc');

class Dnsmasq implements iEnv {

    public function status () {

        return "Mostrando estado del ambiente";
    }

    public function load () {

        return "Subiendo ambiente";
    }

    public function down () {

        return "Bajando ambiente";
    }

}