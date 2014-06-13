<?php

/**
 * �ޥ���Х��ȥ��饹
 *
 * ʸ���������Ѵ��Υ�åѡ�
 * XXX �������ܸ쥪��꡼��Ŭ�����ɲä���¾�����б����Ƥ�������
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

/*
 * ��­
 * �����Ĥ��δ������顢������type��ޥ��å��ʥ�С�����ͭ����
 * 
 * 0 : shift-jis
 * 1 : euc-jp
 * 2 : jis ( ISO-2022-JP )
 * 3 : utf-8
 * 
 */
 

class multibyte {

//public:

public function __construct()
{
  // XXX ��ü���ܸ�����
  mb_language("Japanese");
  // XXX ���ָ����
  //mb_detect_order('eucjp-win,sjis-win,SJIS,EUC-JP,JIS,UTF-8,ASCII');
  //mb_detect_order('sjis-win,eucjp-win,SJIS,EUC-JP,JIS,UTF-8,ASCII');

  //
  $this->init();
}

//
public function init()
{
  // �Ȥꤢ����
  $this->set_to_encoding_type(-1);
  $this->set_from_encoding_type(-1);
}

// ������á�����뵤�ʤ�����protected
protected function set_from_encoding_type($i){$this->from_encoding_type_ = $i;}
protected function get_from_encoding_type(){return $this->from_encoding_type_;}
protected function set_to_encoding_type($i){$this->to_encoding_type_ = $i;}
protected function get_to_encoding_type(){return $this->to_encoding_type_;}

// XXX �������Ȥθߴ����򤫤ͤ���äѡ�
public function set_sjis() { $this->set_to_encoding_sjis(); }
public function set_euc() { $this->set_to_encoding_euc(); }
public function set_jis() { $this->set_to_encoding_jis(); }
public function set_utf8() { $this->set_to_encoding_utf8(); }

//
public function set_from_encoding_unknown() { $this->set_from_encoding_type(-1); }
public function set_from_encoding_sjis() { $this->set_from_encoding_type(0); }
public function set_from_encoding_euc() { $this->set_from_encoding_type(1); }
public function set_from_encoding_jis() { $this->set_from_encoding_type(2); }
public function set_from_encoding_utf8() { $this->set_from_encoding_type(3); }

//
public function set_to_encoding_sjis() { $this->set_to_encoding_type(0); }
public function set_to_encoding_euc() { $this->set_to_encoding_type(1); }
public function set_to_encoding_jis() { $this->set_to_encoding_type(2); }
public function set_to_encoding_utf8() { $this->set_to_encoding_type(3); }

// XXX ����Τ���
protected function _is($i)
{
  if ($this->get_to_encoding_type() == $i) {
    return true;
  }
  return false;
}

public function is_sjis() { return $this->_is(0); }
public function is_euc() { return $this->_is(1); }
public function is_jis() { return $this->_is(2); }
public function is_utf8() { return $this->_is(3); }

//
//public function convert($s, $ddd)
public function convert($s)
{
  // XXX
  if ("" === $s) {
    return "";
  }

  // to
  if (-1 === $this->get_to_encoding_type()) {
    return "";
  } else {
    $to_encoding_type = $this->encode_type_string_[$this->get_to_encoding_type()];
  }

  // from
  if (-1 === $this->get_from_encoding_type()) {
    $from_encoding_type = 'sjis-win,eucjp-win,SJIS,EUC-JP,JIS,UTF-8,ASCII';
  } else {
    $from_encoding_type = $this->encode_type_string_[$this->get_from_encoding_type()];
  }
//print "type is " . $to_encoding_type . "<br>\n";
//print "$from_encoding_type, to $to_encoding_type\n";

  // �����ɤ��ִ������Ĥ�����
  return mb_convert_encoding($s, $to_encoding_type, $from_encoding_type);
}

// ʸ�������¬����ʸ�������פ����ꤹ��
public function set_guess_string($s) { return $this->set_guess_to_string($s); }

//
public function set_guess_to_string($s) 
  { return $this->set_to_encoding_type($this->_set_guess_string($s)); }
public function set_guess_from_string($s)
  { return $this->set_from_encoding_type($this->_set_guess_string($s)); }

/**
 *
 *
 * @return int -1 : unknown
 *              0 : shift-jis
 *              1 : euc-jp
 *              2 : jis ( ISO-2022-JP )
 *              3 : utf-8
 */
public function _set_guess_string($s)
{
//print "in $s \n";
  $ret = -1;
  if (preg_match("/euc/i", $s)) {
    $ret = 1;
  } else
  if (preg_match("/sjis/i", $s)) {
    $ret = 0;
  } else
  if (preg_match("/shift[-_]jis/i", $s)) {
    $ret = 0;
  } else
  if (preg_match("/iso-2022-jp/i", $s)) {
    $ret = 2;
  } else
  if (preg_match("/jis/i", $s)) {
    $ret = 2;
  } else
  if (preg_match("/utf[-_]*8/i", $s)) {
    $ret = 3;
  }

  //
  return $ret;
}

/*
//
public function get_charset_string()
{
  // XXX ���顼�����å���ɬ�פ˱�����(���
  $charset_string = $this->charset_string_[$this->get_type()];
//print "charset is " . $charset_string . "\n";

  return $charset_string;
}
*/

//private:
private $from_encoding_type_; // ��ʸ����Υ��󥳡��ɥ�����
private $to_encoding_type_; // convert��˴��Ԥ��륨�󥳡��ɥ�����

// PHP�δؿ��Ѥ�����
//private $encode_type_string_ = array("SJIS", "EUC-JP","JIS", "UTF-8");
//private $encode_type_string_ = array("SJIS-win", "eucJP-win","JIS", "UTF-8");
private $encode_type_string_ = array("SJIS-win", "eucJP-win","ISO-2022-JP", "UTF-8");

// content-type�Ȥ���charset��ʸ����
private $charset_string_ = array("shift_jis", "euc-jp","iso-2022-jp", "utf-8");

} // end of class
