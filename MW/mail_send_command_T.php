<?php

require_once('internet_message_format.inc');
require_once('mail_send_command.inc');

$mobj = new internet_message_format;

$email = 'm.furusho@gmail.com';
$mobj->set_from('furu@m-fr.net', "�ž�");
$mobj->push_to($email);
$mobj->set_subject('�ƥ���');
$mobj->set_body('�ۤ���ल��');
$mobj->set_envelope_from( mail_util::make_verp('werror@m-fr.net', $email) );

$sobj = new mail_send_command;
$sobj->send($mobj);
