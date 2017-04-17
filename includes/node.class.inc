<?php
include_once (dirname(__FILE__).'/container.class.inc');

class Node {

    public $containerStatus = '';
    private $imageName = 'govi-boxes';
    // Uncomment to fetch remote image
    // private $imageName = 'snaphuman/govi-boxes';
    private $domainName = 'govi.box';
    private $imageTag = '1.1';
    private $docroot = '/home/govi/drupal';
    private $dbContainer = 'govi-db';

    public function add($opts) {

        $params = '-e VIRTUAL_HOST=' . $opts['sitename'] . '.' . $this->domainName . ' ';
        $params .= '-e APP_ENV=' . $opts['branch'] . ' ';
        $params .= '-v ' . $opts['path'] . ':' . $this->docroot . ':rw ';
        $params .= '--link ' . $this->dbContainer . ':mysql ';
        $params .= $this->imageName . ':';
        $params .= $this->imageTag . ' ';

        $output = Container::run($opts['sitename'], $params);

        print ('[govi-boxes] node ' . $opts['sitename'] . ' created. Navigate in your browser to: ' . $opts['sitename'] . '.' . $this->domainName . PHP_EOL);
    }

    public function show($opts) {

        $format = '{{.Names}}';

        if (!empty($opts['with-status'])) {
            $format .= ': {{.Status}}';
        }

        $output = Container::listNodes($this->imageName, $this->imageTag, $format);

        print ($output . PHP_EOL);
    }
}
