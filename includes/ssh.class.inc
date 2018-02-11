<?php

include_once (dirname(__FILE__).'/container.class.inc');

class SSH {

  private $imageName = 'jeroenpeeters/docker-ssh';
  private $imageTag = 'latest';

  public function start ($name, $conf) {

    $params = '-p '. $conf->port .':22 ';

    switch($conf->authType) {

      case "publicKey" :
        $params .= '-v '. $conf->file .':/authorized_keys ';
        $params .= '-e AUTHORIZED_KEYS=/authorized_keys ';
        break;
      case "simpleAuth":

        $params .= '-e AUTH_PASSWORD='. $conf->password .' ';
    }
    $params .= '-e PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/root/vendor/bin ';
    $params .= '-e AUTH_MECHANISM='. $conf->authType . ' ';
    $params .= '-e AUTH_USER=root ';
    $params .= '-e CONTAINER=' .$name. ' ';
    $params .= $this->imageName .':';
    $params .= $this->imageTag  .' ';

    $output = Container::run($name.'-ssh', $params);

    print ('[govi-boxes] govi-ssh for ' . $opts['sitename'] . ' created. Now you can access to your this node via ssh -p '.$conf->port. ' root@localhost' . PHP_EOL);
  }

}
