<?php

$aliases["{{site_name}}"] = array(
  "root" => "/usr/share/nginx/html/www/drupal",
  "uri" => "{{site_name}}.govi.box",
  "remote-host" => "0.0.0.0",
  "remote-user" => "root",
  "ssh-options" => "-p {{ssh_port}}"
);
