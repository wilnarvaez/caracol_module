<?php
/**
 * @file
 * Caracol_Module administrative section.
 */

 /**
 * Implements hook_menu().
 */
 function caracol_menu(){
   $items['admin/config/content/caracol'] = array(
     'title' => t('Caracol Module Configuration'),
     'description' => t('Configuring the display of content types in the "Caracol Module" block'),
     'page callback' => 'drupal_get_form',
     'page arguments' => array('form_caracol'),
     'access arguments' => array('administer caracol'),
     'type' => MENU_CALLBACK,
     'file' => 'caracol.admin.inc',
   );
   return $items;
 }

 /**
 * Implements hook_permission().
 */
 function caracol_permission(){
   return array(
     'administer caracol' => array(
       'title' => t('Administer Caracol'),
       'description' => t('Manages the access rights to user roles'),
     ),
   );
 }

 // form is designed
 function form_caracol(){
   $form = array();

   $form['frm1'] = array(
     '#type' => 'fieldset',
     '#title' => t('Caracol Module Configuration'),
     '#collapsible' => TRUE,
     '#collapsed' => FALSE,
   );

   foreach (node_type_get_types() as $tipos) {
     $note_types[] = $tipos->type;
   }

   //select for content type
   $form['frm1'] ['caracol_content_type'] = array(
     '#type' => 'select',
     '#options' => drupal_map_assoc(($note_types)),
     '#title' => t('Choose the type of content to display'),
     '#default_value' => variable_get('caracol_content_type', 'article'),
   );

   //select for filter
   $form['frm1'] ['caracol_filter'] = array(
     '#type' => 'select',
     '#options' => array('collapsed'=>t('Collapsed'), 'dots'=>t('Dots'), 'ordered'=>t('Ordered List')),
     '#title' => t('Choose how to display the list of contents.'),
     '#default_value' => variable_get('caracol_filter', 'collapsed'),
   );

   //textfield for limit
   $form['frm1'] ['caracol_quantity_content'] = array(
     '#type' => 'textfield',
     '#title' => t('Limit number of contents to show'),
     '#default_value' => variable_get('caracol_quantity_content', 5),//!empty($form_state['values']['cantidad']) ? $form_state['values']['cantidad'] : '',
     '#required' => TRUE,
   );

   $form['frm1'] ['submit'] = array(
     '#type' => 'submit',
     '#value' => t('Submit'),
   );
   return $form;
 }

 /**
 * Implements hook_validate().
 */
 function form_caracol_validate($form, &$form_state){
   $cantidad = check_plain($form_state['values']['caracol_quantity_content']);
   if($cantidad==""){
     form_set_error('caracol_quantity_content', t('Content limit field to show can not be empty.'));
   }else if(!is_numeric($cantidad)){
     form_set_error('caracol_quantity_content', t('The content limit field must be numeric.'));
   }
 }

 /**
 * Implements hook_submit().
 */
 function form_caracol_submit($form, &$form_state){
     variable_set('caracol_content_type', $form_state['values']['caracol_content_type']);
     variable_set('caracol_quantity_content', intval($form_state['values']['caracol_quantity_content']));
     variable_set('caracol_filter', $form_state['values']['caracol_filter']);

   return drupal_set_message(t('Configuration has been saved'));
 }
