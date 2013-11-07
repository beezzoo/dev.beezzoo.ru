<?php
/**
 * @file
 * MailhandlerSubjectIdentifier class.
 */

$plugin = array(
  'name' => 'Sample processor',
  'description' => 'Extracts Case ID from subject line.',
  'handler' => array(
    'class' => 'MailhandlerSubjectIdentifier',
    'parent' => 'MailhandlerCommands',
  ),
  'file' => 'MailhandlerSubjectIdentifier.class.php',
  'weight' => 30,
);
?>
