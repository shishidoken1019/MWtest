<?php

/**
 * CGI �ѥ�᥿���饹
 *
 * ������ "name=value&name=value&"�η������갷��
 * XXX �̤�CGI�˸¤��ΤǤ�����
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

require_once('multimap.inc');

class cgi_param
{

//
public function __construct()
{
  $this->init();
}

/**
 * init
 *
 */
public function init()
{
  $this->data_ = new multimap;
}

// ǰ�Τ���
protected function encode($s) { return urlencode($s); }
protected function decode($s) { return urldecode($s); }

/**
 * �ɲ�
 *
 * @access public
 * @param string $name ����̾
 * @param string $value ��
 */
public function add($name, $value)
{
  // XXX
  if ("" === $name) {
    return true;
  }
  $this->data_->insert($name, $value);
//print "add $name <= $value \n";
  return true;
}

/**
 * ñ���ɲ�
 *
 * add�Ȼ��Ƥ��뤬����ʣ�����������������񤭤򤹤�
 *
 * @access public
 * @param string $name ����̾
 * @param string $value ��
 */
public function add_once($name, $value)
{
  // XXX
  if ("" === $name) {
    return true;
  }
//print "add_once $name <= $value \n";
  // �������ܤ��Ƥߤ�
  $itr = $this->data_->find($name);
//var_dump($itr);
  //if (empty($itr)) {
  if (is_null($itr)) {
    // �ʤ����insert
    $this->data_->insert($name, $value);
//print "add_once insert\n";
  } else {
    // ����о��
    $this->data_->real($itr)->set_second($value);
//print "add_once update\n";
  }
  return true;
}

 /**
 * ñ�θ���
 *
 * ��õ�������б��ǡ������ʤ����϶�ʸ��������
 *
 * @access public
 * @param string $key õ�������ǡ�����key
 * @return string �͡�key���ʤ����϶�ʸ���򵢤�
 */
public function find($key)
{
  //
  $buf = $this->finds($key);

  // XXX empty�ؿ����ʤ����ɡ�����������only�äƤ狼�äƤ�Τ�
  if (empty($buf)) {
    return "";
  }

  // else
  return $buf[0];
}

 /**
 * ʣ��������åѡ�
 *
 * finds�����֤����ɡĤĤŤ�ְ㤨��������
 *
 * @access public
 * @param string $key õ�������ǡ�����key
 * @return string �͡�key���ʤ����϶�ʸ���򵢤�
 */
public function find_array($key) { return $this->finds($key); }

 /**
 * ʣ������
 *
 * ��õ�������б��ǡ������ʤ����϶�ʸ��������
 *
 * @access public
 * @param string $key õ�������ǡ�����key
 * @return string �͡�key���ʤ����϶�ʸ���򵢤�
 */
public function finds($key)
{

  //
  $ret = array();

  // �ޤ����ƥ졼���Ǽ���
  $itrs = $this->data_->find_array($key);

  // �������ǧ
  // ��̯�����ʴؿ�����������ͤ��������ʤΤ�
  if (empty($itrs)) {
    return $ret;
  }

  // ��ɤäƤ������ƥ졼�����󤫤�value���������Ф�
  foreach($itrs as $itr) {
    // ���֤μ���
    $ret[] = $this->data_->real($itr)->get_second();
  }

  //
  return $ret;
}

 /**
 * �ǡ�������
 *
 * ʸ����������ä�������Ÿ������
 *
 * @access public
 * @param string $s name=value&������ʸ����
 */
public function set($s)
{
  // ���ǰ�Τ���
  $this->init();

  // �ڤ�ʬ��
  $datas = explode("&", $s);

  // �֤�󤷤Ĥ�����
  foreach ($datas as $data) {
    // �ޤ��ڤ�ʬ��
    $kv = explode("=", $data);

    // �ǥ�����
    $key = $this->decode($kv[0]);
    $value = $this->decode($kv[1]);

    // ����
    $this->add($key, $value);
  }

  //
  return true;
}

 /**
 * �ǡ�������
 *
 * name=value&������ʸ����Ȥ��������������Ф�
 *
 * @access public
 * @return string name=value&������ʸ����
 */
public function get()
{

$datas = array();

  // ���ƥ졼���Ǥ֤�ޤ路
  for($itr = $this->data_->begin(); $itr != $this->data_->end(); $itr ++) {
    // ʸ�������
    $wk = $this->encode($this->data_->real($itr)->get_first()) . "=" .
          $this->encode($this->data_->real($itr)->get_second());

    // �ͤù���
    $datas[] = $wk;
  }

  // �Ĥʤ��Ĥ�����
  return implode("&", $datas);
}

 /**
 * keylist����
 *
 * @access public
 * @return vector<string> key����
 */
public function get_all_keys()
{
  return $this->data_->get_all_keys();
}

/**
 * ���ꤵ�줿key��������Ǥ������롣
 *
 * key����ʸ���ξ��֤ʤˤ⤷�ʤ���
 * ������������ʤ�clear�᥽�åɤĤ��äơ�
 *
 * @access public
 * @param string $key ���������keyʸ����
 * @return integer ����������ǿ�
 */
public function erase_key($key)
{
  return $this->data_->erase_key($key);
}


//private:
private $data_;

} // end of class
