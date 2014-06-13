<?php

/**
 * �Х�ǡ���
 *
 * ����������������ڡפ�Ԥ�
 * ���ܤϥ��󥹥���������������
 * chk �᥽�åɤ�����static���Ѥ�����
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('is.inc');

/*
 �����å��Ǥ��륿���פϤȤꤢ�����ʲ�������
any		������鷺
alphanum	�ѿ���
numeric		���͡�min��max�ΰ�̣�礤���Ѥ��
number          ������min��max��ʸ�����ˤʤ뤢���꤬numeric�Ȥκ���
email
url
digit		����
dir		�ǥ��쥯�ȥ�
date		����

�ʲ���̤����
alpha		�ѻ�
alpha_lower	�Ѿ�ʸ��
alpha_upper	����ʸ��
xdigit		16�ʿ��ο���
tel
jzip		���ܤ�͹���ֹ�

XXX ���ѤȤ��ϻȤ��ͤ��������Ƥ���(��

 */

class validator {

public function __construct()
{
  //
  $this->init();
}

//
public function init()
{
  $this->set_type("");
  $this->must_off();
  $this->set_min(-1);
  $this->set_max(-1);
  $this->clear_method();

  // �б����Ƥ���ơ��Υ᥽�åɤ����
  // XXX �������餳�����ɲá�
  // �ѿ���
  $this->push_method("alphanum", "is_alphanum");
  // ����
  $this->push_method("numeric", "is_digit");
  // ����
  $this->push_method("number", "is_digit");
  // ����
  $this->push_method("digit", "is_digit");
  // email
  $this->push_method("email", "is_email");
  // url
  $this->push_method("url", "is_url");
  // dir
  $this->push_method("dir", "is_dir");
  // dir
  $this->push_method("date", "is_date");

  //
  $this->set_error_must(false);
  $this->set_error_type(false);
  $this->set_error_min(false);
  $this->set_error_max(false);

  //
  return;
}

////////////////////////
// �������å�
////////////////////////
//
public function set_type($s) { $this->type_ = $s; }
public function get_type() { return $this->type_; }
//
protected function set_must_flg($b) { $this->must_flg_ = $b; }
protected function get_must_flg() { return $this->must_flg_; }
//
public function must_on() { $this->set_must_flg(true); }
public function must_off() { $this->set_must_flg(false); }
public function is_must_flg() { return $this->get_must_flg(); }

//
public function set_min($i) { $this->min_ = $i; }
public function get_min() { return $this->min_; }

//
public function set_max($i) { $this->max_ = $i; }
public function get_max() { return $this->max_; }

//
public function push_method($n, $v) { $this->method_[$n] = $v; }
public function get_method($n)
{
  if (isset($this->method_[$n])) {
    return $this->method_[$n];
  } else {
    return "";
  }
}

public function clear_method() { $this->method_ = array(); }


//
protected function set_error($b) { $this->error_ = $b; }
protected function get_error() { return $this->error_; }
public function is_error() { return $this->error_; }
//
protected function set_error_must($b) { $this->error_must_ = $b; }
protected function get_error_must() { return $this->error_must_; }
public function is_error_must() { return $this->error_must_; }
//
protected function set_error_type($b) { $this->error_type_ = $b; }
protected function get_error_type() { return $this->error_type_; }
public function is_error_type() { return $this->error_type_; }
//
protected function set_error_min($b) { $this->error_min_ = $b; }
protected function get_error_min() { return $this->error_min_; }
public function is_error_min() { return $this->error_min_; }
//
protected function set_error_max($b) { $this->error_max_ = $b; }
protected function get_error_max() { return $this->error_max_; }
public function is_error_max() { return $this->error_max_; }


// -------------
// set_type�Υ�åѡ��Ƽ�
// -------------
public function set_type_alphanum() { $this->set_type('alphanum'); }
public function set_type_numeric() { $this->set_type('numeric'); }
public function set_type_email() { $this->set_type('email'); }
// ʸ�����̤����ʤ����
public function set_type_any() { $this->set_type(''); }

////////////////////////
// �ᥤ������å�
////////////////////////

// �����å��᥽�å�
// XXX static�ʥ��饹
// OK �ʤ�true������ʤ�false
// bool chk($value, type, must_flg, min, max);
static public function chk($value, $type, $mflg = false, $min = -1, $max = -1)
{
  //
  $obj = new validator;
  $obj->set_type($type);
  if ($mflg) {
    $obj->must_on();
  } else {
    $obj->must_off();
  }
  $obj->set_min($min);
  $obj->set_max($max);

  //
  return $obj->check($value);
}

// �����å��᥽�å�
// OK �ʤ�true������ʤ�false
public function check($value)
{
//print "validator value is $value \n";
  //
  $length = strlen($value);

  // �ޤ�ɬ�ܥ����å�
  if (0 == $length) {
//print "length 0\n";
    // ɬ�ܹ��ܤʤ饨�顼���ͤ��֤�
    if ($this->is_must_flg()) {
      $this->set_error(true);
      $this->set_error_must(true);
//print "Trap 0.1\n";
//print "return false\n";
      return false;
    }
    // ɬ�ܤ���ʤ��ʤ顢�ʲ��Υ����å���̣�ʤ�����OK���ͤ��֤�
//print "Trap 0.2\n";
//print "return true\n";
    return true;
  }
//print "Trap 1\n";

  // �ʹߤΤ���ˤ��Σ�
  $ret = true;

  // ���������ץ����å�
  $type = $this->get_type();
//print "type is $type \n";
  if ('any' !== $type) {
    if ("" !== $type) {
      $wk = $this->get_method($type);
      if ("" == $wk) {
        // XXX ���꤬�ؤ󡣤ɤ��衩
        $this->set_error(true);
//print "invalid type\n";
//print "return false\n";
        return false;
      }

      // �����å�
      if (false === is::$wk($value)) {
        // �����
        $this->set_error(true);
        $this->set_error_type(true);
//print "type check ng. \n";
//print "return false\n";
        $ret = false;
      }
    }
  }

  // ��ǡ�length�����å�
  if ("numeric" === $type) {
//print "into numeric \n";
    if (false === $this->get_error_type()) {
      if (-1 != $this->get_min()) {
        $value = $value + 0;
        if ($value < $this->get_min()) {
          // �����
          $this->set_error(true);
          $this->set_error_min(true);
          $ret = false;
        }
      }
      if (-1 < $this->get_max()) {
        if ($value > $this->get_max()) {
          // �����
          $this->set_error(true);
          $this->set_error_max(true);
          $ret = false;
        }
      }
    }
  } else {
//print "into no numeric\n";
//print "length = $length\n";
    // XXX
    if (-1 < $this->get_min()) {
//print "min check " . $this->get_min() . "\n";
      if ($length < $this->get_min()) {
//print "min check ng.\n";
        // �����
        $this->set_error(true);
        $this->set_error_min(true);
        $ret = false;
      }
    }
    // XXX
    if (-1 < $this->get_max()) {
//print "max check " . $this->get_max() . "\n";
      if ($length > $this->get_max()) {
//print "min check ng.\n";
        // �����
        $this->set_error(true);
        $this->set_error_max(true);
        $ret = false;
      }
    }
  }

  //
//var_dump($ret);
  return $ret;
}



//private:
private $type_;		// �����å�������
private $must_flg_;	// ɬ�ܥե饰��true��ɬ��
private $min_;		// �Ǿ��͡����ܤ�byte������������numeric�ξ�����
private $max_;		// �����͡����ܤ�byte������������numeric�ξ�����
private $method_;	// �᥽�å�̾�б�ɽ
//
private $error_;	// �Ȥˤ���error�ʤ�true
private $error_must_;	// must�����å��ǥ��顼�ʤ�true
private $error_type_;	// type�����å��ǥ��顼�ʤ�true
private $error_min_;	// min�����å��ǥ��顼�ʤ�true
private $error_max_;	// max�����å��ǥ��顼�ʤ�true


} // end of class
