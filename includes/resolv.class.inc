<?php

class Resolv {

  static $resolvConfFile = '/etc/resolv.conf';
  static $comment = '#Agregado por govi boxes';
  static $nameserver = '127.0.0.1';

  public static function fileContent() {

    $content .= 'nameserver ' . self::$nameserver . ' ' . self::$comment;

    return $content;
  }

  public static function checkFile() {

    $file = self::$resolvConfFile;
    $size = filesize($file);

    if (file_exists($file)) {

      $resource = fopen(self::$resolvConfFile, r);
      $content = fread($resource, $size);

      $setNameServer = empty(self::checkContent($content)) ? self::fileWrite() : 'nothing to change';

      var_dump($setNameServer);
    }
  }

  public static function checkContent($content) {

    $pattern = self::fileContent();
    var_dump($pattern);

    preg_match('/' . $pattern . '/', $content, $match);

    return empty($match) ? false : true;
  }

  public static function fileWrite() {

    return "nameserver writed";
  }

  public static function configure() {

    self::checkFile();
  }
}
