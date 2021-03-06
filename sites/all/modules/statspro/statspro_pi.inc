<?php
// $Id: statspro_pi.inc,v 1.1.2.3 2010/06/21 20:57:15 rsevero Exp $

/**
 * @file
 *   Page impressions report.
 *
 */
require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'statspro') . '/statspro_settings.inc';

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function statspro_pi() {
  if (module_exists('statistics')) {
    if (variable_get('statistics_enable_access_log', 0) == 0) {
      // Statistics module enabled but access log disabled.
      $message = t(
          "The core %statistics_module module is enabled but the %access_log_setting
  setting in the !access_log page isn't. You can't have page visualization
  statistics without it. Please consider enabling it to enable page visualization
  reports.",
          array(
        '%statistics_module' => t('Statistics'),
        '%access_log_setting' => t('Enable access log'),
        '!access_log' => l(t('Access log settings'), 'admin/config/system/statistics'),
      )
      );
      drupal_set_message($message, 'error');
      return "\n<p>" . t('Dependencies not met.') . "</p>\n";
    }
  }
  else {
    // Statistics module disabled.
    $message = t(
        "The core %statistics_module module is not enabled. You can't have page
  visualization statistics without it. Please consider enabling it and the
  %access_log_setting setting in the %access_log page.",
        array(
      '%statistics_module' => t('Statistics'),
      '%access_log_setting' => t('Enable access log'),
      '%access_log' => t('Access log settings'),
    )
    );
    drupal_set_message($message, 'error');
    return "\n<p>" . t('Dependencies not met.') . "</p>\n";
  }

  $view = views_new_view();

  $view->name = 'statspro_pi';
  $view->description = 'Page impressions';
  $view->tag = 'Statistics Pro';
  $view->view_php = '';
  $view->base_table = 'statspro';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'day' => array(
      'label' => 'Date',
      'date_format' => 'custom',
      'custom_date_format' => 'd. F Y',
      'exclude' => 0,
      'id' => 'day',
      'table' => 'statspro',
      'field' => 'day',
      'relationship' => 'none',
    ),
    'pi' => array(
      'label' => 'Page impressions',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'pi',
      'table' => 'statspro',
      'field' => 'pi',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
      'display_mode' => 'graph',
      'graph_size' => '350',
    ),
    'pi_1' => array(
      'label' => 'Trend',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => '.',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'pi_1',
      'table' => 'statspro',
      'field' => 'pi',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
      'display_mode' => 'trend',
      'graph_size' => '',
    ),
    'pi_2' => array(
      'label' => 'Amount',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => '.',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'pi_2',
      'table' => 'statspro',
      'field' => 'pi',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
      'display_mode' => 'text',
      'graph_size' => '',
    ),
  ));
  $handler->override_option('sorts', array(
    'day' => array(
      'order' => 'DESC',
      'id' => 'day',
      'table' => 'statspro',
      'field' => 'day',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'pi' => array(
      'operator' => '>',
      'value' => array(
        'value' => '0',
        'min' => '',
        'max' => '',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'pi',
      'table' => 'statspro',
      'field' => 'pi',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'access statistics pro reports',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Statistics Pro');
  $handler->override_option('header', 'Page impressions for guests and registered users.');
  $handler->override_option('header_format', '1');
  $handler->override_option('header_empty', 0);
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 20);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'day' => 'day',
      'pi' => 'pi',
      'pi_1' => 'pi_1',
      'pi_2' => 'pi_2',
    ),
    'info' => array(
      'day' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'pi' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'pi_1' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'pi_2' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => 'day',
  ));

  $handler = $view->new_display('page', 'All page impressions', 'page_1');
  $handler->override_option('filters', array());
  $handler->override_option('header', 'All page impressions');
  $handler->override_option('path', 'admin/reports/statspro/pi');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'PIs',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler = $view->new_display('attachment', 'Page impressions for authenticated users', 'attachment_1');
  $handler->override_option('fields', array(
    'day' => array(
      'label' => 'Date',
      'date_format' => 'custom',
      'custom_date_format' => 'd. F Y',
      'exclude' => 0,
      'id' => 'day',
      'table' => 'statspro',
      'field' => 'day',
      'relationship' => 'none',
    ),
    'upi' => array(
      'label' => 'Page impressions, users',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => '.',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'upi',
      'table' => 'statspro',
      'field' => 'upi',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'display_mode' => 'graph',
      'graph_size' => '350',
    ),
    'upi_2' => array(
      'label' => 'Trend',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'upi_2',
      'table' => 'statspro',
      'field' => 'upi',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'display_mode' => 'trend',
      'graph_size' => '',
    ),
    'upi_1' => array(
      'label' => 'Amount',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => '.',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'upi_1',
      'table' => 'statspro',
      'field' => 'upi',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
      'display_mode' => 'text',
      'graph_size' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'upi' => array(
      'operator' => '>',
      'value' => array(
        'value' => '0',
        'min' => '',
        'max' => '',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'upi',
      'table' => 'statspro',
      'field' => 'upi',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('header', 'Page impressions for authenticated users');
  $handler->override_option('attachment_position', 'after');
  $handler->override_option('inherit_arguments', TRUE);
  $handler->override_option('inherit_exposed_filters', FALSE);
  $handler->override_option('inherit_pager', FALSE);
  $handler->override_option('render_pager', TRUE);
  $handler->override_option('displays', array(
    'page_1' => 'page_1',
    'default' => 0,
  ));

  if (module_exists('views_charts')) {
    $handler = $view->new_display('attachment', 'Page impressions chart', 'attachment_2');
    $handler->override_option('fields', array(
      'day' => array(
        'label' => 'Date',
        'date_format' => 'custom',
        'custom_date_format' => 'd. F Y',
        'exclude' => 0,
        'id' => 'day',
        'table' => 'statspro',
        'field' => 'day',
        'relationship' => 'none',
      ),
      'pi' => array(
        'label' => 'Page impressions',
        'set_precision' => FALSE,
        'precision' => 0,
        'decimal' => '.',
        'separator' => ',',
        'prefix' => '',
        'suffix' => '',
        'exclude' => 0,
        'id' => 'pi',
        'table' => 'statspro',
        'field' => 'pi',
        'override' => array(
          'button' => 'Override',
        ),
        'relationship' => 'none',
        'display_mode' => 'graph',
        'graph_size' => '350',
      ),
      'upi' => array(
        'label' => 'Page impressions for authenticated users',
        'alter' => array(
          'alter_text' => 0,
          'text' => '',
          'make_link' => 0,
          'path' => '',
          'link_class' => '',
          'alt' => '',
          'prefix' => '',
          'suffix' => '',
          'target' => '',
          'help' => '',
          'trim' => 0,
          'max_length' => '',
          'word_boundary' => 1,
          'ellipsis' => 1,
          'html' => 0,
          'strip_tags' => 0,
        ),
        'empty' => '',
        'hide_empty' => 0,
        'empty_zero' => 0,
        'set_precision' => FALSE,
        'precision' => 0,
        'decimal' => '.',
        'separator' => '.',
        'prefix' => '',
        'suffix' => '',
        'exclude' => 0,
        'id' => 'upi',
        'table' => 'statspro',
        'field' => 'upi',
        'override' => array(
          'button' => 'Use default',
        ),
        'relationship' => 'none',
        'display_mode' => 'text',
        'graph_size' => '',
      ),
    ));
    $handler->override_option('filters', array());
    $handler->override_option('header', 'Page impressions chart');
    $handler->override_option('style_plugin', 'charts');
    $handler->override_option('style_options', array(
      'views_charts_series_fields' => array(
        'pi' => 'pi',
        'upi' => 'upi',
      ),
      'views_charts_x_labels' => 'day',
      'width' => '700',
      'height' => '200',
      'engine' => statspro_get_current_charting_option(),
      'type' => array(
        'amcharts' => 'line',
        'bluff' => 'line',
        'open-flash' => 'line',
      ),
      'wmode' => 'window',
      'y_min' => '0',
      'y_legend' => '',
    ));
    $handler->override_option('attachment_position', 'after');
    $handler->override_option('inherit_arguments', TRUE);
    $handler->override_option('inherit_exposed_filters', FALSE);
    $handler->override_option('inherit_pager', FALSE);
    $handler->override_option('render_pager', TRUE);
    $handler->override_option('displays', array(
      'page_1' => 'page_1',
      'default' => 0,
    ));
  }

  return $view->preview('page_1', array());
}
