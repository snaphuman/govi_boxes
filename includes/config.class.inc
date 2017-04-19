<?php

class Config {


    public static function readFile() {

        $user = posix_getpwuid(posix_geteuid());
        $file = $user['dir'] . '/.drush/govi_boxes/config.json';

        $config = file_get_contents($file);

        var_dump($config);
        var_dump(json_decode($config));

        return json_decode($config);
    }
}
