<?php

class Config {

    public static $checked = false;

    public static function readFile() {

        var_dump(self::$checked);

        if (self::$checked) return;

        $user = posix_getpwuid(posix_geteuid());
        $file = $user['dir'] . '/.drush/govi_boxes/config.json';
        if (!self::$checked) {
            if (file_exists($file)) {

                $config = file_get_contents($file);
            } else {

                print ("[govi-boxes] config file not found". PHP_EOL);
                $config = null;
            }

            self::$checked = true;

            return json_decode($config);
        }


    }
}
