<?php

class Config {

    public static function readFile() {

        $user = posix_getpwuid(posix_geteuid());
        $file = $user['dir'] . '/.drush/govi_boxes/config.json';
        if (file_exists($file)) {

          print ("[govi-boxes] using config file from " . $file . PHP_EOL);
          $config = file_get_contents($file);
        } else {

          print ("\033[01;31m[govi-boxes]\033[0m config file not found". PHP_EOL);

          return;
        }

        return json_decode($config);
    }
}
