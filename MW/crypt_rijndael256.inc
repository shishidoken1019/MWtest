<?php
require_once('crypt_base.inc');
require_once('block_cipher_mode_util.inc');

/*
 * ���
 * �ѿ�̾�λȤ�ʬ��
 * encrypted_unit = �Ź沽���줿ʸ�����IV�ޤ��
 * encrypted_text = �Ź沽���줿ʸ�����IV�ޤޤʤ���
 */

class crypt_rijndael256 extends crypt_base {

/*
 * ���󥹥ȥ饯��
 */
public function __construct() {
  $this->init();
}

/*
 * �����
 */
public function init() {
  parent::init();
  $this->set_plain_text("");
  $this->set_encrypted_unit("");
  $this->set_key("");
  $this->set_block_mode("");
}


/*
 * ���å��������å���
 */
// ʿʸ
public function set_plain_text($s){
  $this->plain_text_ = $s;
}
public function get_plain_text(){
  return $this->plain_text_;
}
// �Ź沽���줿ʸ����(IV�ޤ�)
public function set_encrypted_unit($s){
  $this->encrypted_unit_ = $s;
}
public function get_encrypted_unit(){
  return $this->encrypted_unit_;
}
// �Ź業��
public function set_key($s){
  $this->key_ = $s;
}
public function get_key(){
  return $this->key_;
}
// �֥��å��⡼��
public function set_block_mode($s){
  $this->block_mode_ = $s;
}
public function get_block_mode(){
  return $this->block_mode_;
}

/*
 * �Ź沽
 */
public function encrypt() {
  $this->crypt("en");
}

/*
 * ʣ�粽
 */
public function decrypt() {
  $this->crypt("de");
}

// �½���
private function crypt($type) {
//print "crypt Trap 1\n";
  // IV ���ղä���ʸ����������饹����
  $eu_o = new block_cipher_mode_util;

  // �Ź渰�����
//print "crypt Trap 2\n";
  $key = $this->get_key();
  // �Ź�����Υ⡼�ɤ����
  $block_mode = $this->get_block_mode();

//print "crypt Trap 3\n";
  if($type == "en") {
//print "crypt Trap 4\n";
    $plain_text = $this->get_plain_text();
  }
  else {
    $encrypted_unit = $this->get_encrypted_unit();
    $eu_o->set_encrypted_unit($encrypted_unit);
    $eu_o->split();
    $encrypted_text = $eu_o->get_encrypted_text();
    $iv = $eu_o->get_iv();
  }

//print "crypt Trap 5\n";
  $td = mcrypt_module_open('rijndael-256', '', $block_mode, '');

  // IV����
  if($type == "en") {
//print "crypt Trap 6\n";
    $iv_size = mcrypt_enc_get_iv_size($td);
//print "crypt Trap 6-1\n";
    // XXX
    //$iv = mcrypt_create_iv($iv_size, MCRYPT_DEV_RANDOM);
    //srand();
    //$iv = mcrypt_create_iv($iv_size, MCRYPT_RAND);
    $iv = mcrypt_create_iv($iv_size, MCRYPT_DEV_URANDOM);
//print "crypt Trap 6-2\n";
  }
  else{
    $iv = $eu_o->get_iv();
  }

  // �Ź業���Υ����������
//print "crypt Trap 7\n";
  $ks = mcrypt_enc_get_key_size($td);

  // �Ź業������
//print "crypt Trap 8\n";
  $md5_key = substr(md5($key), 0, $ks);

  // �����
//print "crypt Trap 9\n";
  $ret = @mcrypt_generic_init($td, $md5_key, $iv);
//var_dump($ret);
  if (false === $ret) {
    return false;
  }

  /* �Ź沽�������������ޤ� */
  if($type == "en") {
    $encrypted = mcrypt_generic($td, $plain_text);
  }
  else {
    $decrypted_text = rtrim(@mdecrypt_generic($td, $encrypted_text));  // �ǡ����ѥǥ��󥰤����Τ�
  }

  /* �Ź沽�ϥ�ɥ��λ���ޤ� */
  mcrypt_generic_deinit($td);
  mcrypt_module_close($td);

  if($type == "en") {
    // IV ���ղä���ʸ�������
    $eu_o->set_encrypted_text($encrypted);
    $eu_o->set_iv($iv);
    $eu_o->set_iv_size($iv_size);
    $eu_o->combine();
    $unit = $eu_o->get_encrypted_unit();
  
    $this->set_encrypted_unit($unit);
  }
  else {
    $this->set_plain_text($decrypted_text);
  }
  //
  return true;
}

// private:
// �Ź沽������ʸ����
private $plain_text_;

// �Ź業��
private $key_;

// �Ź沽����ʸ����(IV�ޤ�)
private $encrypted_unit_;

// �֥��å��⡼��
private $block_mode_;

}
