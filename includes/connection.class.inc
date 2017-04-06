<?php

class Connection {

    public static function check() {
        $socket = 'unix:///var/run/docker.sock';

        $client = stream_socket_client($socket, $errno, $errorMessage);

        if ($client) {

            print ("\033[01;32m[govi-boxes]\033[0m connected" . PHP_EOL);

            // we are just checking the connection to the
            // socket, so there is not need to keep it open
            // PROMISE: this could be useful if we want
            // to handle socket resources directly instead
            // docker commands
            fclose($client);
            $conn = TRUE;
        } else {

            print ("\033[01;31m[govi-boxes]\033[0m not connected" . PHP_EOL);

            //throw new UnexpectedValueException('Failed to connect: '.$errno);

            $conn = FALSE;
        }

        return $conn;
    }
}