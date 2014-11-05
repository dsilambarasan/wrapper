# NOTE: Make likes tabs, so the tabs are on purpose.
.PHONY: check-style check-style-ci
.PHONY: check-cpd check-cpd-ci
.PHONY: check-js check-js-ci
.PHONY: check-all-ci

# Both these command exit non-0 when any violations occur
# We want to ignore that so we can get all the results in jenkins
.IGNORE: check-style-ci check-cpd-ci check-pmd-ci check-phpunit-ci

# A fancy php -l for developers/Jenkins.
check-php:
	./vendor/bin/parallel-lint \
	-e module,php,inc,install,profile \
	docroot/profiles/publisher/modules/custom \
	docroot/profiles/publisher/publisher.install \
	docroot/profiles/publisher/publisher.profile \
	docroot/profiles/publisher/settings.publisher.php \
	docroot/profiles/publisher/publisher.install \

# phpcs for developers.
check-style:
	./vendor/bin/phpcs \
	--extensions=module,php,inc,install \
	--standard=./vendor/drupal/coder/coder_sniffer/Drupal \
	--ignore="**/*.features.*,**/*.field_group.inc,**/*.strongarm.inc,**/*.*_default.inc,**/*.default_permission_sets.inc,**/*.tpl.php,*.js" \
	docroot/profiles/publisher/modules/custom

# phpcs as checkstyle for jenkins.
check-style-ci:
	./vendor/bin/phpcs --report=checkstyle \
	--report-file=results/checkstyle.xml \
	--extensions=module,php,inc,install \
	--standard=./vendor/drupal/coder/coder_sniffer/Drupal \
	--ignore="**/*.features.*,**/*.field_group.inc,**/*.strongarm.inc,**/*.*_default.inc,**/*.default_permission_sets.inc,**/*.tpl.php,*.js" \
	docroot/profiles/publisher/modules/custom

#phpmd for developers.
check-pmd:
	./vendor/bin/phpmd docroot/profiles/publisher/modules/custom text codesize,unusedcode,design \
	--exclude *.views_default.inc,*.strongarm.inc,*.field_instance.inc,*.field_base.inc,*.features.*,*.field_group.inc,*default_permission_sets.inc,*ds.inc \
	--suffixes module,php,inc

#phpmd for jenkins.
check-pmd-ci:
	./vendor/bin/phpmd docroot/profiles/publisher/modules/custom xml codesize,unusedcode,design \
	--exclude *.views_default.inc,*.strongarm.inc,*.field_instance.inc,*.field_base.inc,*.features.*,*.field_group.inc,*default_permission_sets.inc,*ds.inc \
	--suffixes module,php,inc \
	--reportfile results/phpmd.xml

#phpcopy-paste-detection for developers
check-cpd:
	./vendor/bin/phpcpd --min-lines 3 --min-tokens 25 \
	--names *.module,*.php,*.inc \
	--names-exclude *.views_default.inc,*.strongarm.inc,*.field_instance.inc,*.field_base.inc,*.features.*,*.field_group.inc,*default_permission_sets.inc,*ds.inc \
	docroot/profiles/publisher/modules/custom

#phpcopy-paste-detection for jenkins.
check-cpd-ci:
	./vendor/bin/phpcpd --min-lines 3 --min-tokens 25 \
	--log-pmd results/pmd.xml \
	--names *.module,*.php,*.inc \
	--names-exclude *.views_default.inc,*.strongarm.inc,*.field_instance.inc,*.field_base.inc,*.features.*,*.field_group.inc,*default_permission_sets.inc,*ds.inc \
	docroot/profiles/publisher/modules/custom

# pdepend for jenkins.
check-pdepend-ci:
	./vendor/bin/pdepend \
	--jdepend-xml=results/pdepend.xml \
	--overview-pyramid=results/overview-pyramid.svg \
	--jdepend-chart=results/jdepend-chart.svg \
	--ignore="**/*.features.*,**/*.field_group.inc,**/*.strongarm.inc,**/*.views_default.inc,**/*.default_permission_sets.inc,**/*.tpl.php,*.js" \
	--suffix="module,php,inc" \
	docroot/profiles/publisher/modules/custom

#phpunit for developers.
check-phpunit:
	./vendor/bin/phpunit

#phpunit for jenkins.
check-phpunit-ci:
	./vendor/bin/phpunit --log-junit=results/junit.xml --coverage-clover=results/clover.xml --coverage-html=results/clover-html

check-all-ci: check-php check-style-ci check-cpd-ci check-pdepend-ci check-pmd-ci check-phpunit-ci
