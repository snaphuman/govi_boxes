<?php

class Connection {

    private $socket = 'unix:///var/run/docker.sock';
    private $conn = FALSE;

    public static function instance() {

        static $instance = FALSE;
        if (empty($instance)) {
            $instance = new static();
        }
        return $instance;
    }

    private function __construct() {

    }

    public function check() {

        $client = stream_socket_client($this->socket, $errno, $errorMessage);

        if ($client == FALSE) {

            //throw new UnexpectedValueException('Failed to connect: '.$errno);
            print ("\033[01;31m[govi-boxes]\033[0m not connected" . PHP_EOL);

            $this->conn = FALSE;
            
        } else {

            // we are just checking the connection to the
            // socket, so there is not need to keep it open
            // PROMISE: this could be useful if we want
            // to handle socket resources directly instead
            // docker commands
            fclose($client);
            print ("\033[01;32m[govi-boxes]\033[0m connected" . PHP_EOL);
            $this->conn = TRUE;
        }

        return $this->conn;
    }
}