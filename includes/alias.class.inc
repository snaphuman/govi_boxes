<?php

class Alias {

  private $conf = null;
  //const $tpl = dirname( dirname(__FILE__) ) . '/drupal/aliases_drushrc.tpl.php';
  //private $path = getenv('HOME') . '.drush/site-aliases';
  private $file = '';

  public function __construct($conf) {
    $this->conf = $this->getConf($conf);
    var_dump($this->file);
  }

  public function create($sitename) {
    $this->file = $sitename.'.aliases.drushrc.php';
    var_dump($this->file);

  }

  private function getConf($conf) {
    return $conf;
  }
}
