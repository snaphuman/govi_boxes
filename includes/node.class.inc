<?php
include_once (dirname(__FILE__).'/container.class.inc');
include_once (dirname(__FILE__).'/config.class.inc');
include_once (dirname(__FILE__).'/mariadb.class.inc');
include_once (dirname(__FILE__).'/ssh.class.inc');

class Node {

    private $conf = null;
    public $containerStatus = '';
    private $imageName = 'govi-boxes';
    // Uncomment to fetch remote image
    // private $imageName = 'snaphuman/govi-boxes';
    private $domainName = 'govi.box';
    private $imageTag = '1.2';
    private $docroot = '/usr/share/nginx/html/www/drupal';
    private $dbContainer = 'govi-db';

    public function __construct() {

      $this->conf = Config::readFile()->nodes;
    }

    public function add($opts) {

        $nodeConf = $this->conf->{$opts['sitename']};
        $sshConf = $nodeConf->ssh;
        $dbParams = $nodeConf->db;
        $mySQLServerIP = Container::getIP($this->dbContainer);

        /*
        if (empty($nodeConf)) {

            print ('[govi-boxes] cannot create node ' . $opts['sitename'] . ', please set database connection parameters  in config.json file' . PHP_EOL);
            return;
        }
        */

        $params = '-e GOVIBOX_SITENAME=' . $opts['sitename'] . ' ';
        $params .= '-e GOVIBOX_SSH_PORT=' . $sshConf->port . ' ';
        $params .= '-e GOVIBOX_DB_NAME=' . $nodeConf->db->name . ' ';
        $params .= '-e GOVIBOX_DB_USER=' . $nodeConf->db->user . ' ';
        $params .= '-e GOVIBOX_DB_PASSWORD=' . $nodeConf->db->password . ' ';
        $params .= '-e GOVIBOX_DB_HOST="' . $mySQLServerIP . '" ';
        $params .= '-e GOVIBOX_BASE_URL=' . $opts['sitename'] . '.' . $this->domainName . ' ';

        $params .= '-e VIRTUAL_HOST=' . $opts['sitename'] . '.' . $this->domainName . ' ';
        $params .= '-e APP_ENV=' . $opts['branch'] . ' ';
        $params .= '-v ' . $opts['path'] . ':' . $this->docroot . ':rw ';
        $params .= '--link ' . $this->dbContainer . ':mysql ';
        $params .= $this->imageName . ':';
        $params .= $this->imageTag . ' ';

        $output = Container::run($opts['sitename'], $params);

        $nodeIP = Container::getIP($opts['sitename']);

        // TODO: implement method to prepare needed database ops
        // i.e: create new database.

        $db = new DB();
        if (empty($opts['fresh-install'])) {

            $db->configure($dbParams->user,
              $dbParams->password,
              $dbParams->name);

              self::settings($opts['sitename']);
              // self::aliases($opts['sitename']);
        } else {

          $db->configure($dbParams->user,
            $dbParams->password,
            $dbParams->name,
            TRUE);
        }


        print ('[govi-boxes] node ' . $opts['sitename'] . ' created with IP ' . $nodeIP . '. Navigate in your browser to: ' . $opts['sitename'] . '.' . $this->domainName . PHP_EOL);
        $ssh = new SSH();
        $ssh->start($opts['sitename'], $sshConf);
    }

    public function show($opts) {

        $format = '{{.Names}}';

        if (!empty($opts['with-status'])) {
            $format .= ': {{.Status}}';
        }

        $output = Container::listNodes($this->imageName, $this->imageTag, $format);

        print ($output . PHP_EOL);
    }

    public function settings($containerName) {

        $settings = dirname(dirname(__FILE__)).'/drupal/settings.php';
        $sitePath = $this->docroot.'/sites/default/settings.php';

        Container::copy($containerName, $settings, $sitePath);
    }

  public function aliases($containerName) {

    $aliases = dirname(dirname(__FILE__)).'/drupal/aliases.drushrc.php';
    $aliasesPath = '/home/govi/.drush/site-aliases/aliases.drushrc.php';

    Container::copy($containerName, $aliases, $aliasesPath);
  }
}
