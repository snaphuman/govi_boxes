<?php

include_once (dirname(__FILE__).'/connection.class.inc');

class Container {

    public static $connection;

    public static function status ($name) {

        if (!self::exist($name)) return 'not running';

        $cmd = "docker inspect " . $name;
        $output = json_decode(shell_exec("docker inspect " . $name), TRUE);

        $status = $output[0]['State']['Status'];

        return empty($status) ? "not running": $status;
    }

    public static function down ($name, $status) {

        if ($status == "running") {

            $cmd = 'docker stop ' . $name . ' && docker rm ' . $name;

            shell_exec($cmd);

            $output = 'stopped and removed ';

        } else {

            $output = 'nothing to stop';
        }

        print ('[govi-boxes] ' . $name . ': ' . $output . PHP_EOL);
    }

    public static function start ($name) {

        $cmd = 'docker start ' . $name;

        shell_exec($cmd);

        return 'started';
    }

    public static function run ($name, $params) {

        if (self::exist($name)) {

            return self::start($name);
        } else {

            $cmd = 'docker run -d -v /var/run/docker.sock:/var/run/docker.sock --name ' . $name . ' ' . $params;
            return shell_exec($cmd) .' created';
        }
    }

    public static function exist ($name) {

        $cmd = 'docker inspect ' . $name;

        $output = json_decode(shell_exec("docker inspect " . $name), TRUE);

        return !empty($output) ? true : false;
    }

  public static function exec ($name, $command) {

      $cmd = 'docker exec -ti ' . $name . ' ' . $command;

      return shell_exec($cmd);

    }

  public static function getIP ($name) {

      $cmd = 'docker inspect --format "{{ .NetworkSettings.IPAddress }}" ' . $name;

      $ip = shell_exec($cmd);

      return $ip;
  }

    public static function listNodes($image, $tag, $format) {

        print ('[govi-boxes] list of deployed nodes'.PHP_EOL);

        $cmd = 'docker ps -a --filter \'ancestor=' . $image . ':' . $tag . '\' --format \''. $format .'\'';

        $nodes = shell_exec($cmd);

        return $nodes;
    }

    public static function copy($name, $source, $destination) {

        $cmd = 'docker cp ' . $source . ' ' . $name . ':' . $destination;

        shell_exec($cmd);
    }

    public static function checkConnection() {

        self::$connection = Connection::check();
    }
}
