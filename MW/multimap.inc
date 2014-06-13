<?php

/**
 *
 * multimap���饹
 *
 * �����ν�ʣ�����map(�褦�ϥϥå��������)
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Kohei Yamada <hecomark@gmail.com>
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

// 2005/2/24 ���ƥ졼����ñ�������ź���ʤΤǡ�
//           ��Ȥ򻲾Ȥ������$ob->real($itr)�Τ褦��
//           ���Ѥ��Ƥ���������
//           ���Ǥϴ���Ū��Pair���֥������ȤʤΤǡ�
//           $key = $ob->real($itr)->get_first();
//           $value = $ob->real($itr)->get_second();
//           �Τ褦�˻��Ȥ��ޤ���
//
 
require_once("pair.inc");
 
class multimap
{

public function __construct()
{
  $this->init();
}

public function init()
{
  $this->data_ = array();
}

/**
 * begin
 *
 * �ǽ�����Ǥ�ؤ����ƥ졼�����֤�
 *
 * @param ������������
 * @return  ����ͤ�����
 * @access public
 * @since 1.0
 */
public function begin()
{
  // ���ΤȤ����������ź�����֤�
  // �����������ƥ졼������
  return 0;
}

/**
 * end
 *
 * �Ǹ�����Ǥμ���ؤ����ƥ졼�����֤�
 * XXX �Ǹ�����ǤΡּ��פǤ�����������
 *
 */
public function end()
{
  return $this->size();
}

/**
 * rbegin
 *
 * ��Ƭ�����Ǥ�ؤ��ե��ƥ졼�����֤���
 *
 */
public function rbegin()
{
  // �����ź���ˤʤ�Τ�+1
  return abs(-($this->size()) + 1);
}

/**
 * rend
 *
 * �Ǹ�����Ǥ�ؤ����ƥ졼�����֤�
 *
 */
public function rend()
{
  // �Ǹ�μ������Ǥ�ؤ��褦��+1
  return 0 + 1;
}

/**
 * insert
 *
 * �ʺ��ν���Ƭ�ˡ�$key, $value��Pair���֥������Ȥ��ɲä���
 * ����ͤ������������Ǥ�ؤ����ƥ졼��
 *
 * @param $key=����, $value=��
 * @return  �������줿���֤򼨤����ƥ졼�����֤�
 * @access public
 * @since 1.0
 */
public function insert($key, $value)
{
  // �Ȥꤢ��������¤�ư��

  $obj = new pair();
  $obj->set($key, $value);
  $this->data_[] = $obj;

  // ��˺Ǹ���������Ϥ��ʤΤ�
  return $this->size() - 1;  
}

/**
 * find
 *
 * $key�򥭡��˻��ĺǽ�����Ǥ�õ���ơ�
 * �������Ǥ�ؤ����ƥ졼�����֤���
 * iterator���ΤϿ��͡ĤäƤΤ�PHP��������
 * ���������Ĥ���ʤ�����null(��˲������äƤ뤫�狼��ʤ�����
 *
 */
public function find($key)
{
  $ret = $this->find_array($key);

  // ��̯��ˡ�٤ʴؿ��������������ʤΤ�
  if (empty($ret)) {
    return null; 
  }
  //
  return $ret[0];
}

/**
 * find_array
 *
 * $key�򥭡��˻��ĺǽ�����Ǥ�õ���ơ�
 * �������Ǥ�ؤ����ƥ졼�����֤���
 * ���������Ĥ���ʤ����϶�������֤�
 *
 */
public function find_array($key)
{
  $ret = array();
  //
  for($itr = $this->begin(); $itr != $this->end(); $itr++){
    if(strcmp($this->real($itr)->get_first(), $key)==0){
      $ret[] = $itr;
    }
  }

  //
  return $ret; 
}

//*******************************//

/**
 * isempty
 *
 * ������true
 *
 * @param ������������
 * @return  ����ͤ�����
 * @access public
 * @since 1.0
 */
public function isempty()
{
  return empty($this->data_); 
}

/**
 * size
 *
 * ���Ƥ����Ǥο����֤�
 *
 * @param ������������
 * @return  ����ͤ�����
 * @access public
 * @since 1.0
 */
public function size()
{
  return count($this->data_);
}

/**
 * erase
 *
 * first�����Ǥ������롣
 * ���뤤�ϡ�first����last�ޤǤ����Ǥ�������
 *
 * @param first=����������Ǥκǽ��ؤ����ƥ졼��
 *        last =����������ǤκǸ�μ���ؤ����ƥ졼��
 * @return  ����������Ǥμ���ؤ����ƥ졼��
 * @access public
 * @since 1.0
 */
public function erase($first, $last = false)
{
  if(false !== $last){
    // last���꤬����С�first,last�δ֤����Ǥ���
    array_splice($this->data_, $first, $last-$first);
  }else{
    array_splice($this->data_, $first, 1);
  }
  
  return $first;
}

/**
 * clear
 *
 * ���Ƥ����Ǥ���
 *
 */
public function clear()
{
  $this->data_ = array();
}

/**
 * real
 *
 * ���ƥ졼���λؤ����ǤΥ��֥������Ȥ��֤��ʥݥ��󥿤�ɤ���
 * $itr������ͤξ��ϥ��顼�������Ȥꤢ������ʸ����������
 *
 * @param ������������
 * @return  ����ͤ�����
 * @access public
 * @since 1.0
 */
public function real($itr)
{
  if($itr < 0){
    return "";
  }

  return $this->data_[$itr];
}

/*
 * ���Ǥ�­������
 *
 */
public function add(multimap $o)
{
  for($itr = $o->begin(); $itr != $o->end(); $itr ++) {
    $this->insert($o->real($itr)->get_first(), $o->real($itr)->get_second());
  }
  return true;
}

/**
 * ������������
 */
public function get_all_keys()
{
  // �Ȥꤢ�������ˤ���
  $names = array();
  for($itr = $this->begin(); $itr != $this->end(); $itr ++) {
    // ʸ�������
    $names[$this->real($itr)->get_first()] = 1;
  }

  $keys = array_keys($names);
  return $keys;
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
  //
  if ("" === $key) {
    return 0;
  }

  // �оݤ򸡺� & ���
  $ret = 0;
  while(false === is_null($itr = $this->find($key))) {
    // ����оݿ�����
    $ret ++;
    $this->erase($itr);
  }
//var_dump($this->data_);

  //
  return $ret;
}


//
private $data_;
} // end of class

