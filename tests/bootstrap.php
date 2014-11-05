<?php

/**
 * @file
 * PHPUnit bootstrap.
 *
 * @see phpunit.xml
 */

// Load some basic files incase people are using random drupal functions.
// Any non-database function are safe.
// TODO: Add more as needed.
require_once './docroot/includes/bootstrap.inc';
require_once './docroot/includes/common.inc';
require_once './docroot/includes/date.inc';
require_once './docroot/includes/entity.inc';
require_once './docroot/includes/unicode.inc';

/**
 *
 * Load contrib Classes.
 *
 * These classes are needed to run generate proper code coverage.
 */
require_once './docroot/profiles/publisher/modules/contrib/entity/includes/entity.inc';
require_once './docroot/profiles/publisher/modules/contrib/entity/includes/entity.controller.inc';
require_once './docroot/profiles/publisher/modules/contrib/entity/includes/entity.property.inc';
require_once './docroot/profiles/publisher/modules/contrib/entity/includes/entity.ui.inc';
require_once './docroot/profiles/publisher/modules/contrib/entity/includes/entity.wrapper.inc';
