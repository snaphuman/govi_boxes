<?php
include_once (dirname(__FILE__).'/container.class.inc');

class Node {

    public $containerStatus = '';
    private $imageName = 'snaphuman/govi-boxes';
    private $imageTag = '1.0';
    private $docroot = '/usr/share/nginx/html/';
    private $dbContainer = 'govi-db';

    public function add($opts) {

        $params = '-e VIRTUAL_HOST=' . $opts['sitename'] . ' ';
        $params .= '-e APP_ENV=' . $opts['branch'] . ' ';
        $params .= '-v ' . $opts['path'] . ':' . $this->docroot . ':rw ';
        $params .= '--link ' . $this->dbContainer . ':mysql ';
        $params .= $this->imageName . ':';
        $params .= $this->imageTag . ' ';

        $output = Container::run($opts['sitename'], $params);
    }
}
