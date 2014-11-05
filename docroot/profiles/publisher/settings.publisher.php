<?php

/**
 * @file
 * Global Publisher settings file, used in all Sites & Environments.
 */

/**
 * Override domain detection in Acquia Purge: hardcode the incoming domain.
 *
 * @see acquia_purge/DOMAINS.txt
 */
if (isset($_SERVER['HTTP_HOST']) && (!empty($_SERVER['HTTP_HOST']))) {
  $conf['acquia_purge_domains'] = array($_SERVER['HTTP_HOST']);
}

/**
 * Set up fast 404 settings.
 */
$conf['404_fast_paths_exclude'] = '/\/(?:styles)\//';
$conf['404_fast_paths'] = '/\.(?:txt|png|gif|jpe?g|css|js|ico|swf|flv|cgi|bat|pl|dll|exe|asp)$/i';
$conf['404_fast_html'] = '<html xmlns="http://www.w3.org/1999/xhtml"><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL "@path" was not found on this server.</p></body></html>';

/**
 * Deauthorize Update manager.
 */
$conf['allow_authorize_operations'] = FALSE;

/**
 * Memcache settings.
 */
if (class_exists('Memcache')) {
  $conf['cache_backends'][] = 'profiles/publisher/modules/contrib/memcache/memcache.inc';
  $conf['cache_default_class'] = 'MemCacheDrupal';
  $conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
}

/**
 * Fix issue where Drush doesn't get 'AH_SITE_ENVIRONMENT' environment variable.
 */
if (file_exists('/var/www/sitescripts/siteinfo.php')) {
  // Extract environment info using Acquia's own tool for it.
  require_once '/var/www/sitescripts/siteinfo.php';
  list($ah_site_name, $ah_site_group, $ah_site_env) = ah_site_info();

  if (!isset($_ENV['AH_SITE_NAME'])) {
    $_ENV['AH_SITE_NAME'] = $ah_site_name;
  }
  if (!isset($_ENV['AH_SITE_GROUP'])) {
    $_ENV['AH_SITE_GROUP'] = $ah_site_group;
  }
  if (!isset($_ENV['AH_SITE_ENVIRONMENT'])) {
    $_ENV['AH_SITE_ENVIRONMENT'] = $ah_site_env;
  }
}

/**
 * SSO settings.
 */
$conf['pub_sso_password_reset'] = 'https://sso.external.nbcuni.com/nbcucentral/jsp/pwchange.jsp';
