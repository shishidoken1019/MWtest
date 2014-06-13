<?php
/**
 * �֥��å��Ź�⡼���ѤΥ桼�ƥ���ƥ�
 *
 * �Ź沽���줿ʸ�����IV�򲼵��Τ褦�ʥե����ޥåȤ����륯�饹
 * [IV_SIZE(4��)][IV][ENC_STR]
 * IV_SIZE = IV�Υ������򣴷�ο����Ǽ����� ��:0032 (IV��32�Х���)
 * IV = IV_SIZE�ǻ��ꤵ�줿Ĺ����IV�����
 * ENC_STR = �Ź沽���줿ʸ����
 * �����ν����Ϥǥ١��������ν�����Ԥ�
 * XXX ��Ƭ��8�Х��ȡ��������ʸ�����Ĥ���
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('crypt_util.inc');

class block_cipher_mode_util {

public function __construct() {
  $this->init();
}

public function init() {
  $this->set_encrypted_text("");
  $this->set_iv("");
  $this->set_iv_size("");
  $this->set_encrypted_unit("");
}

//
public function set_encrypted_text($s) { $this->encrypted_text_ = $s; }
public function get_encrypted_text() { return $this->encrypted_text_; }

public function set_iv($s) { $this->iv_ = $s; }
public function get_iv() { return $this->iv_; }

public function set_iv_size($i) { $this->iv_size_ = $i; }
public function get_iv_size() { return $this->iv_size_; }

public function set_encrypted_unit($s) { $this->encrypted_unit_ = $s; }
public function get_encrypted_unit() { return $this->encrypted_unit_; }

/*
 * ������
 */
// ���
public function combine() {
  $iv_size = $this->get_iv_size();
  $iv = $this->get_iv();
  $encrypted_text = $this->get_encrypted_text();

  // �ե����ޥåȤ�������
  $iv_size = sprintf("%04d", $iv_size);

  // base64������
  $encrypted_unit = base64_encode(crypt_util::rand_string(8) . $iv_size. $iv. $encrypted_text);
//print "encrypt u \n $encrypted_unit \n";

  // ��礵�줿�ǡ����򥻥å�
  $this->set_encrypted_unit($encrypted_unit);
}
// ʬ��
public function split() {
  $encrypted_unit = $this->get_encrypted_unit();

  // base64�򸵤��᤹
  $encrypted_unit = base64_decode($encrypted_unit);

  // iv�Υ����������
  $length = strlen($encrypted_unit);
  //$iv_size = (int) substr($encrypted_unit, 0, 4);
  $iv_size = (int) substr($encrypted_unit, 8, 4);

  // IV�����
  $iv = substr($encrypted_unit, 8+4, $iv_size);

  // �Ź�ʸ��������
  $encrypted_text = substr($encrypted_unit, (8+4+$iv_size));

  // ʬ�䤷���ǡ����򥻥å�
  $this->set_encrypted_text($encrypted_text);
  $this->set_iv($iv);
  $this->set_iv_size($iv_size);
}


// �����ѿ�
private $iv_;
private $iv_size_;
private $encrypted_text_;
private $encrypted_unit_;
}

