<?php

/**
 * @file
 * Hooks provided by the Pub Mpx module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Set mpx player per video on initial import based on user defined rulesets.
 *
 * @return array
 */
function hook_pub_mpx_player_id_rulesets_info() {
  $rulesets = array(
    array(
      'fields' => array(
        'entitlement' => 'free',
        'fullEpisode' => FALSE,
      ),
      // Set the player for the video with the key 'guid'. This is the
      // 'Reference ID' in the history section of the player at
      // http://mpx.theplatform.com.

      // thePlatform - VOD Global Player
      'guid' => 'GClP1BxPBHo87Bi5oymyrI4xnBqwaL9Zz',
    ),
    array(
      'fields' => array(
        'entitlement' => 'auth',
        'fullEpisode' => TRUE,
      ),
      // [DEV] - MVPD Live Player (tP Support)
      'guid' => 'gd_DUKrut8dURN8bzZaA7y0BDtbJG_6sz',
    ),
    array(
      'fields' => array(
        // Use media$name to specify a category. Currently case-sensitive.
        'media$name' => 'Live',
      ),
      // thePlatform - Linear Global Player
      'guid' => 'Ypj4ZTiYGkwy5iCRdLQMgzX1CyhnqYHjz',
    ),
  );

  return $rulesets;
}

/**
 * Implements hook_pub_mpx_player_id_rulesets_info_alter().
 *
 * @params array $rulesets
 *   A multidimensial array.
 *
 * @return array
 */
function hook_pub_mpx_player_id_rulesets_info_alter(&$rulesets) {
  if (is_array($rulesets) && !empty($rulesets)) {
    foreach ($rulesets as $ruleset) {
      $ruleset['guid'] = 'kljsflksdjflkjlkjsdf0893409384';
    }
  }
}

/**
 * @} End of "addtogroup hooks".
 */
