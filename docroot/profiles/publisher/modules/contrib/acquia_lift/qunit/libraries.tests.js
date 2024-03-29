/**
 * @file libraries.js
 */

QUnit.module("Acquia Lift DOM selector tests");

QUnit.test('DOM Selection', function(assert) {
  var $mousehere = jQuery('#mousehere');
  var $nowatch = jQuery('#nowatch');
  var $another = jQuery('#another');
  var $watch = jQuery('#watch');
  var indicatorClass = 'acquia-lift-active-element';
  var current = null;
  var currentSelector = '';

  expect(10);

  function testCallback(element, selector) {
    assert.equal(element, current, 'Callback triggered from selecting ' + selector);
    assert.equal(selector, currentSelector, 'Triggered callback with current selector ' + selector);
  }

  $watch.DOMSelector({
    onElementSelect: testCallback
  });
  assert.ok(!$watch.DOMSelector("isWatching"), 'DOM Selector initialized without watching.');

  $watch.DOMSelector("startWatching");
  assert.ok($watch.DOMSelector("isWatching"), 'DOM Selector watching.');

  $mousehere.trigger('mousemove');
  assert.ok($mousehere.hasClass(indicatorClass), 'Element is highlighted');
  current = $mousehere[0];
  currentSelector = '#mousehere';

  $another.trigger('mousemove');
  assert.ok(!$mousehere.hasClass(indicatorClass), 'Highlight is removed when moving to new element');
  assert.ok($another.hasClass(indicatorClass), 'New element is highlighted');
  current = $another[0];
  currentSelector = '#another';

  $nowatch.trigger('mousemove');
  assert.ok(!$nowatch.hasClass(indicatorClass), 'No watching outside watch area');
  assert.ok($another.hasClass(indicatorClass), 'Last element is still highlighted');
  $another.trigger('click');

  assert.ok(!$another.hasClass(indicatorClass), 'Highlight removed after selection');
});

QUnit.module("Acquia Lift message box tests");

QUnit.asyncTest('Message Box autoclose', function(assert) {
  var message = "It's the <b>Muppet Show</b>",
    resp = {
      data: {
        message: message,
        seconds: 1
      }
    },
    $messagebox = null;

  QUnit.start();
  expect(4);

  Drupal.ajax.prototype.commands.acquia_lift_message_box(Drupal.ajax, resp, 200);
  $messagebox = jQuery('#acquia-lift-message-box');
  assert.equal($messagebox.length, 1, 'Message box added to page.');
  assert.ok(!$messagebox.hasClass('element-hidden'), 'Message box is not hidden.');
  assert.equal($messagebox.find('.message').html(), message, 'Message was set to provided text.');

  QUnit.stop();
  setTimeout(function() {
    assert.ok($messagebox.hasClass('element-hidden'), 'Message box was removed after 1 second.');
    QUnit.start();
    $messagebox.remove();
  }, 2000);
});

QUnit.asyncTest('Message Box no interaction', function(assert) {
  var message = "It's the <b>Muppet Show</b>",
    resp = {
      data: {
        message: message
      }
    },
    $messagebox = null;

  QUnit.start();
  expect(4);

  Drupal.ajax.prototype.commands.acquia_lift_message_box(Drupal.ajax, resp, 200);
  $messagebox = jQuery('#acquia-lift-message-box');
  assert.equal($messagebox.length, 1, 'Message box added to page.');
  assert.ok(!$messagebox.hasClass('element-hidden'), 'Message box is not hidden.');
  assert.equal($messagebox.find('.message').html(), message, 'Message was set to provided text.');

  QUnit.stop();
  setTimeout(function() {
    assert.equal(jQuery('#acquia-lift-message-box').length, 1, 'Message box was not removed after 2 seconds.');
    QUnit.start();
    $messagebox.remove();
  }, 2000);
});


QUnit.asyncTest('Message Box click close', function(assert) {
  var message = "It's the <b>Muppet Show</b>",
    resp = {
      data: {
        message: message
      }
    },
    $messagebox = null;

  QUnit.start();
  expect(4);

  Drupal.ajax.prototype.commands.acquia_lift_message_box(Drupal.ajax, resp, 200);
  $messagebox = jQuery('#acquia-lift-message-box');
  assert.equal($messagebox.length, 1, 'Message box added to page.');
  assert.ok(!$messagebox.hasClass('element-hidden'), 'Message box is not hidden.');
  assert.equal($messagebox.find('.message').html(), message, 'Message was set to provided text.');

  QUnit.stop();
  $messagebox.find('.close').trigger('click');
  setTimeout(function() {
    assert.ok($messagebox.hasClass('element-hidden'), 'Message box is hidden when close button is clicked.');
    QUnit.start();
    $messagebox.remove();
  }, 2000);
});

QUnit.asyncTest('Message Box click document', function(assert) {
  var message = "It's the <b>Muppet Show</b>",
    resp = {
      data: {
        message: message
      }
    },
    $messagebox = null;

  expect(4);
  QUnit.start();

  Drupal.ajax.prototype.commands.acquia_lift_message_box(Drupal.ajax, resp, 200);
  $messagebox = jQuery('#acquia-lift-message-box');
  assert.equal($messagebox.length, 1, 'Message box added to page.');
  assert.ok(!$messagebox.hasClass('element-hidden'), 'Message box is not hidden.');
  assert.equal($messagebox.find('.message').html(), message, 'Message was set to provided text.');

  QUnit.stop();
  jQuery('#nowatch').trigger('click');
  setTimeout(function() {
    assert.ok($messagebox.hasClass('element-hidden'), 'Message was hidden when clicking elsewhere in document.');
    QUnit.start();
    $messagebox.remove();
  }, 2000);
});

QUnit.asyncTest('Message Box click message', function(assert) {
  var message = "It's the <b>Muppet Show</b>",
    resp = {
      data: {
        message: message
      }
    },
    $messagebox = null;

  expect(4);
  QUnit.start();

  Drupal.ajax.prototype.commands.acquia_lift_message_box(Drupal.ajax, resp, 200);
  $messagebox = jQuery('#acquia-lift-message-box');
  assert.equal($messagebox.length, 1, 'Message box added to page.');
  assert.ok(!$messagebox.hasClass('element-hidden'), 'Message box is not hidden.');
  assert.equal($messagebox.find('.message').html(), message, 'Message was set to provided text.');


  QUnit.stop();
  $messagebox.find('.message').trigger('click');
  setTimeout(function() {
    assert.ok(!$messagebox.hasClass('element-hidden'), 'Message was not hidden when clicking on text.');
    QUnit.start();
    $messagebox.remove();
  }, 2000);
});
