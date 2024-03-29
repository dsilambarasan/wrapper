<?php


/**
 * Implements hook_file_formatter_info().
 */
function pub_mpx_file_formatter_info() {

  $formatters = array();

  $formatters['pub_mpx_video'] = array(
    'label' => t('Pub MPX Video'),
    'file types' => _pub_mpx_get_mpx_account_video_file_types(TRUE),
    'default settings' => array(
      'pub_mpx_video_width' => '',
      'pub_mpx_video_height' => '',
    ),
    'view callback' => 'pub_mpx_file_formatter_video_view',
    'settings callback' => 'pub_mpx_file_formatter_video_settings',
  );
  $formatters['pub_mpx_image'] = array(
    'label' => t('Pub MPX Image'),
    'file types' => _pub_mpx_get_mpx_account_video_file_types(TRUE),
    'default settings' => array(
      'pub_mpx_image_image_style' => '',
    ),
    'view callback' => 'pub_mpx_file_formatter_image_view',
    'settings callback' => 'pub_mpx_file_formatter_image_settings',
  );

  return $formatters;
}

/**
 * Settings callback for the pub_mpx_video file formatter.
 */
function pub_mpx_file_formatter_video_settings($form, &$form_state, $settings) {

  $element = array();
  preg_match('|^mpx_video_([0-9]+)$|', $form['#file_type'], $account_id_matches);
  if (count($account_id_matches) >= 2) {
    $account_id = $account_id_matches[1];
    $account = _media_theplatform_mpx_get_account_data($account_id);

    $acccount_default_player = media_theplatform_mpx_get_mpx_player_by_player_id($account->default_player);
    $element['pub_mpx_video_player_id'][ $account->id ] = array(
      '#title' => t('Pub MPX Video Player for Account @account',
        array('@account' => basename($account->account_id))),
      '#type' => 'select',
      '#options' => array_merge(array('' => t('--- Default ---')), media_theplatform_mpx_get_players_select(NULL, 'pid')),
      '#default_value' => isset($settings['pub_mpx_video_player_id'][ $account->id ]) ?
          $settings['pub_mpx_video_player_id'][ $account->id ] :
          (!empty($acccount_default_player) && !empty($acccount_default_player['player_id']) ?
            $acccount_default_player['player_id'] : ''),
    );
  }
  return $element;
}

/**
 * View callback for the pub_mpx_video file formatter.
 */
function pub_mpx_file_formatter_video_view($file, $display, $langcode) {

  $scheme = file_uri_scheme($file->uri);

  if ($scheme != 'mpx' || empty($file->mpx_video_data)) {
    return array();
  }

  // Determine video player.
  $video_player_pid = NULL;
  // Use the player assigned directly to the video if it exists.
  if (!empty($file->mpx_video_data['player_id'])) {
    $player = media_theplatform_mpx_get_mpx_player_by_player_id($file->mpx_video_data['player_id']);
    if (!empty($player['pid'])) {
      $video_player_pid = $player['pid'];
    }
  }
  // ...if not, then the player chosen in the formatter settings.
  if (!$video_player_pid) {
    $account = _media_theplatform_mpx_get_account_data($file->mpx_video_data['parent_account']);
    if (!empty($display['settings']['pub_mpx_video_player_id'][ $account->id ])) {
      $video_player_pid = $display['settings']['pub_mpx_video_player_id'][ $account->id ];
    }
    // ...finally use the default player for the video's account.
    else {
      $player = media_theplatform_mpx_get_mpx_player_by_player_id($account->default_player);
      $video_player_pid = $player['pid'];
    }
  }

  // If this file is inactive, display the themed inactive video.
  if (isset($file->mpx_video_data['status']) && !$file->mpx_video_data['status']) {
    $element = array(
      '#theme' => 'pub_mpx_inactive_video',
      '#file' => $file,
    );
  }
  // Otherwise theme the video player.
  else {
    $element = array(
      '#theme' => 'pub_mpx_video',
      '#file' => $file,
      '#player_id' => $video_player_pid,
    );
  }

  return $element;
}

/**
 * Settings callback for the pub_mpx_image file formatter.
 */
function pub_mpx_file_formatter_image_settings($form, &$form_state, $settings) {

  $element = array();
  $element['pub_mpx_image_image_style'] = array(
    '#title' => t('Pub MPX Image Style'),
    '#type' => 'select',
    '#options' => image_style_options(FALSE),
    '#default_value' => $settings['pub_mpx_image_image_style'],
    '#empty_option' => t('None (original image)'),
  );

  return $element;
}

/**
 * View callback for the pub_mpx_video file formatter.
 */
function pub_mpx_file_formatter_image_view($file, $display, $langcode) {

  $scheme = file_uri_scheme($file->uri);

  if ($scheme != 'mpx') {
    return array();
  }

  $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
  $image_style = $display['settings']['pub_mpx_image_image_style'];
  $valid_image_styles = image_style_options(FALSE);

  // If this file is inactive, display the themed inactive video.
  if (isset($file->mpx_video_data['status']) && !$file->mpx_video_data['status']) {
    $element = array(
      '#theme' => 'pub_mpx_inactive_video',
      '#file' => $file,
    );
  }
  else if (empty($image_style) || !isset($valid_image_styles[$image_style])) {
    $element = array(
      '#theme' => 'image',
      '#path' => $wrapper->getOriginalThumbnailPath(),
      '#alt' => isset($file->override['attributes']['alt']) ? $file->override['attributes']['alt'] : $file->filename,
    );
  }
  else {
    $element = array(
      '#theme' => 'image_style',
      '#style_name' => $image_style,
      '#path' => $wrapper->getLocalThumbnailPath(),
      '#alt' => isset($file->override['attributes']['alt']) ? $file->override['attributes']['alt'] : $file->filename,
    );
  }

  return $element;
}

/**
 * Implements hook_file_displays_alter().
 */
function pub_mpx_file_displays_alter(&$displays, $file, $view_mode) {

  // Ensure that the pub_mpx_video and pub_mpx_image file displays have settings
  // for mpx_video_* file types.  If the setting is a remnant of an old Pub7
  // release without multiple mpx accounts, convert the setting to one that is
  // compatible with multiple accounts.
  if (strpos($file->type, 'mpx_video') === 0) {
    if (isset($displays['pub_mpx_video'])) {
      if(!empty($file->mpx_video_data)) {
        if (is_string($displays['pub_mpx_video']['settings']['pub_mpx_video_player_id'])) {
          $displays['pub_mpx_video']['settings']['pub_mpx_video_player_id'][$file->mpx_video_data['parent_account']] = $displays['pub_mpx_video']['settings']['pub_mpx_video_player_id'];
        }
        if (!isset($displays['pub_mpx_video']['settings']['pub_mpx_video_player_id'][$file->mpx_video_data['parent_account']])) {
          $displays['pub_mpx_video']['settings']['pub_mpx_video_player_id'][$file->mpx_video_data['parent_account']] = '';
        }
      }
    }
    if (isset($displays['pub_mpx_image']) && !isset($displays['pub_mpx_image']['settings']['pub_mpx_image_image_style'])) {
      $displays['pub_mpx_image']['settings']['pub_mpx_image_image_style'] = '';
    }
  }
}
