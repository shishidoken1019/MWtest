<?php

require_once('internet_message_format.inc');

$mobj = new internet_message_format;

$mobj->set_from('furu@m-fr.net', "�ž�");
$mobj->push_to('m.furusho@gmail.com');
$mobj->set_subject('�ƥ���');
$mobj->set_body('�ۤ���ल��');

$s = $mobj->get_mail_string();

var_dump($s);
