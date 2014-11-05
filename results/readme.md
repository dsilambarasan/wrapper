#Result

This directory is just used to export test results to.

A good example of this is when running drush test-run with the --xml option. You can export the xml to this directory for parsing by external tools.

Examples:

```sh
./vendor/bin/phpcs --report-file=results/checkstyle.xml --report=checkstyle --standard=./vendor/drupal/coder/coder_sniffer/Drupal --ignore="**/*.features.*,**/*.field_group.inc,**/*.strongarm.inc,**/*.views_default.inc,**/*.default_permission_sets.inc,**/*.tpl.php,*.js" docroot/profiles/publisher/modules/custom

```
