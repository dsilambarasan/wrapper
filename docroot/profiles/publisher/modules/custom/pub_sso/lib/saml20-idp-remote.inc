<?php
/**
 * @file
 * Set up some basic configurations for the remote.  These can be updated in the
 * site-specific idp-remote files.
 */

include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
// Determine the relevant environment.
include dirname(__FILE__) . '/env.inc';

// Set up some defaults for authsource config values.
$environment_config = array(
  'logout_referrer' => $_SERVER['SERVER_NAME'],
  'metadata.key' => 'nbcufssstg',
  'metadata.name' => $environment_info['metadata_name'],
  'metadata.signonservice' => $environment_info['metadata_signonservice'],
  'metadata.logoutservice' => $environment_info['metadata_logoutservice'],
  'certificate' => 'sso.crt',
  'protocol' => 'http',
);
if (isset($_SERVER['HTTPS']) && strcasecmp($_SERVER['HTTPS'], 'off') != 0) {
  $environment_config['protocol'] = 'https';
}

if ($environment_info['environment'] === 'prod') {
  $environment_config['metadata.key'] = 'nbcufssprod';
  $environment_config['certificate'] = 'sso.crt';
}
