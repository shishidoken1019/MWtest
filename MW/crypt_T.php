<?php

require_once('/opt/www/mw.conf');
require_once("crypt_factory.inc");
$config = './crypt.conf';

$plain_text = "�Ź沽������ʸ��";


/*
 * �Ź沽����
 */
$en_o = crypt_factory::get_instance($config);

// �Ź沽������ʸ���󥻥å�
$en_o->set_plain_text($plain_text);

// �Ź沽���롣
$en_o->encrypt();

// �Ź�ʸ�����������
$encrypted_unit = $en_o->get_encrypted_unit();


/*
 * ʣ�粽����
 */
$de_o = crypt_factory::get_instance($config);
$de_o->set_encrypted_unit($encrypted_unit);
$de_o->decrypt();
$decrypted_text = $de_o->get_plain_text();


?>
ʿʸ��<?= $plain_text ?><br />
�Ź沽ʸ����<?= $encrypted_unit ?><br />
ʣ�粽ʸ����<?= $decrypted_text ?><br />

<?php
if ($plain_text === $decrypted_text) {
  print "test OK\n";
} else {
  print "test NG...\n";
}
