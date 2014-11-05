This is Publisher 7. Prepare to be awed.



# Installation

## Core Development

To install publisher locally please follow these steps:

1. Determine your sitename - most likely ```pub7```.
1. Clone this repository in your local sites folder.
1. Create a mysql database locally
1. Create a local vhost (either local.pub7 or pub7.local in order for your drush aliases to work) pointing to ..../sites/Publisher7/docroot
1. Copy ```docroot/sites/default/settings.site.php``` to ```docroot/sites/sitename```.
1. Copy ```docroot/sites/default/settings.local-example.php``` to ```docroot/sites/sitename/settings.local.php```
   and edit with your database credentials and other local settings.
1. For the initial installation, run ```drush psi --sites-subdir=sitename```.

## Implementation Development

For developing a Publisher7 implementation, there are two different repositories that come into play: this repo (`NBCUOTS/Publisher7`) for Publisher Core and a separate implementation repo (`NBCUOTS/Publisher7_<sitename>`) for the contents of your sites directory (`docroot/sites/<sitename>`). Replace `<sitename>` accordingly (e.g. `nbcunbc`).

To install the Publisher7 implementation locally please follow these steps:

1. Clone this repository, or your own fork of this repo, somewhere within your local webserver's `DocumentRoot`.
1. Checkout the appropriate tag or branch of Publisher7, based on your team's workflow (check with your dev lead).
1. Clone the implementation repo (`NBCUOTS/Publisher7_<sitename>` or your own fork) to `docroot/sites/<sitename>`.
1. Create a mysql database locally named `publisher7_<sitename>`.
1. Create a local vhost, either `local.<sitename>` (e.g. `local.nbcunbc`) or `local.<sitedomain>.com` (e.g. `local.nbc.com`), pointing to `/path/to/Publisher7/docroot`.
1. Create a `settings.<sitename>.php` file in the root of your Publisher7 clone based on this example:

```php
<?php

// Define the current environment.
$_ENV['AH_SITE_ENVIRONMENT'] = 'local';

$databases['default'] = array(
  'default' => array(
    'database' => 'publisher7_<sitename>', // <--- Local database name (required, replace <sitename>)
    'username' => '', // <--- Local database username (required)
    'password' => '', // <--- Local database password (not required)
    'host' => 'localhost',
    'port' => '',
    'driver' => 'mysql',
    'prefix' => '',
  ),
);
```

## New Environment

Requirements: ruby >=2.0.0, [bundler](http://bundler.io/), [composer](https://getcomposer.org/)?

1. Clone this repository, or your own fork of this repo, somewhere within your local webserver's `DocumentRoot`.
1. Checkout the `master` branch.
1. Update `acquia-credentials.yml` with your Acquia cloud account username/password.
1. Create a mysql database locally named `publisher7`.
1. Update the `settings.local.php` files in `docroot/sites/install` AND `docroot/sites/update` with the proper database details.
1. Run the following commands:

```sh
bundle install
bundle exec rake build_local
```

To create a new branch for a story, start it from canonical/master. This is the guaranteed safest way to do that:

```sh
git fetch canonical
git checkout -b <branch-name-goes-here> canonical/master
```

After switching branches and other changes, ensure you're on the correct version of buildkit by running:

 ```sh
bundle install
```

Rebuild the local environment:

```sh
bundle exec rake build_local [profile-name]
```

**Note:** If you're using a shell like zsh make sure to escape your quotes.


### Publisher Testing

####Running Unittest
Install dependencies: ```composer install```
Run phpunit: ```./vendor/bin/phpunit```

#### Writing a Publisher Test
Publisher ships with 1 base class: PublisherWebTestCase (the default Publisher
profile).

*Note: When writing your test it is strongly recommended that you extend from
PublisherWebTestCase.  The reason for this is that we want to be sure the tests
are executed within a publisher installation profile.*

#### Running a Test:

Since we have a custom base class to simplify the testing, you must first enable
pub_test.
```sh
 drush en simpletest pub_test --yes
```

A couple of notes:
1) You must enable both simpletest and pub_test if you plan on running any
test from any module, simpletest will fail if you do not enable pub_test.
You do not need to enable simpletest inside your testing environment.
2) The Publisher Testing module is deliberately hidden from the web UI.  Given
that, you'll need to enable pub_test with drush.

```sh
# You can run a single test such as:
drush test-run PublisherProfileTestCase

# Or you can run all the tests in the Publisher group:
drush test-run Publisher

# If you just want to test the new method you just added you can also do:
drush test-run PublisherProfileTestCase --methods="testPublisherSmokeUserLogin"
```

#### Tips
 - If running via the UI, odds are that PHP will timeout. Either run it via
 drush or increase your PHP ```max_execution_time``` settings.
 - If you add a new test and you do not see it available make sure you also
 added it to the ```files[]``` array on the pub_test.info file.
 - When running a test you will be messing with the Drupal Registry System a lot.
 It's a good idea to install [Registry Rebuild](https://drupal.org/project/registry_rebuild)

####External resources

