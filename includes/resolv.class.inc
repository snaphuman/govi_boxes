<?php

class Resolv {

  static $resolvConfFile = '/etc/resolv.conf'; // Should be a constant
  static $comment = '#Agregado por govi boxes';
  static $nameserver = '127.0.0.1';

  public static function fileContent() {

    $content .= 'nameserver ' . self::$nameserver . ' ' . self::$comment;

    return $content;
  }

  public static function checkFile() {

    $file = self::$resolvConfFile;
    $size = filesize($file);
    $newLine = self::fileContent();

    if (file_exists($file)) {

      $resource = fopen(self::$resolvConfFile, "r");
      $resolvContent = fread($resource, $size);
      fclose($resource);

      $output = empty(self::checkContent($resolvContent)) ? self::fileWrite($file, $newLine, $resolvContent) : 'nothing to change';
    }

    return 'resolv.conf: ' . $output . PHP_EOL;
  }

  public static function checkContent($content) {

      $pattern = self::fileContent();

      preg_match('/' . $pattern . '/', $content, $match);

      return empty($match) ? false : true;
  }

    public static function fileWrite($file, $line, $content) {

      echo ('[govi-boxes] resolv.conf file will be modified to reach proxy network requirements and password will be required do allow this operation.' . PHP_EOL . ' ¿can I proceed? (no/yes): ');

      $newContent = $line . PHP_EOL . $content;

      $handle = fopen('php://stdin', 'r');
      $response = fgets($handle);

      switch (trim($response)) {

          case 'yes':

              $cmd = 'echo "' . addslashes($newContent) . '" | sudo tee ' . $file . ' > /dev/null';
              shell_exec($cmd);

              $output = "written";

              break;
          case 'no':

              $output = "nothing changed";

              break;

          default:
              $output = "nothing changed. Should run drush gbxe up to configure resolver";

              break;
      }

      fclose ($handle);

      return $output;
  }

  public static function configure() {

    $output = self::checkFile();

    print ('[govi-boxes] ' . $output);
  }
}
