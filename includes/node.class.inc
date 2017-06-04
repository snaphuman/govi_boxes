<?php
include_once (dirname(__FILE__).'/container.class.inc');
include_once (dirname(__FILE__).'/config.class.inc');
include_once (dirname(__FILE__).'/mariadb.class.inc');

class Node {

    private $conf = null;
    public $containerStatus = '';
    private $imageName = 'govi-boxes';
    // Uncomment to fetch remote image
    // private $imageName = 'snaphuman/govi-boxes';
    private $domainName = 'govi.box';
    private $imageTag = '1.1';
    private $docroot = '/home/govi/drupal';
    private $dbContainer = 'govi-db';

    public function __construct() {

      $this->conf = Config::readFile()->nodes;
    }

    public function add($opts) {

        $nodeConf = $this->conf->{$opts['sitename']};
        $dbParams = $nodeConf->db;

        /*
        if (empty($nodeConf)) {

            print ('[govi-boxes] cannot create node ' . $opts['sitename'] . ', please set database connection parameters  in config.json file' . PHP_EOL);
            return;
        }
        */

        $params = '-e GOVIBOX_DB_NAME=' . $opts['sitename'] . ' ';
        $params .= '-e GOVIBOX_DB_USER=' . $nodeConf->user . ' ';
        $params .= '-e GOVIBOX_DB_PASSWORD=' . $nodeConf->password . ' ';

        $params .= '-e VIRTUAL_HOST=' . $opts['sitename'] . '.' . $this->domainName . ' ';
        $params .= '-e APP_ENV=' . $opts['branch'] . ' ';
        $params .= '-v ' . $opts['path'] . ':' . $this->docroot . ':rw ';
        $params .= '--link ' . $this->dbContainer . ':mysql ';
        $params .= $this->imageName . ':';
        $params .= $this->imageTag . ' ';

        $output = Container::run($opts['sitename'], $params);

        $nodeIP = Container::getIP($opts['sitename']);

        // TODO: create method to prepare needed database operations
        $db = new DB();

        $db->configure($dbParams->user,
          $dbParams->password,
          $dbParams->database);

        print ('[govi-boxes] node ' . $opts['sitename'] . ' created with IP ' . $nodeIP . '. Navigate in your browser to: ' . $opts['sitename'] . '.' . $this->domainName . PHP_EOL);
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
