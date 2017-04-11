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

            $cmd = 'docker run -d --name ' . $name . ' ' . $params;
            return shell_exec($cmd) .' created';
        }
    }

    public static function exist ($name) {

        $cmd = 'docker inspect ' . $name;

        $output = json_decode(shell_exec("docker inspect " . $name), TRUE);

        return !empty($output) ? true : false;
    }

    public static function checkConnection() {

        self::$connection = Connection::check();
    }
}
