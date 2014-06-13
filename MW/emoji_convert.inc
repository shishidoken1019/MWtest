<?php

/**
 * ��ʸ���Ѵ����饹
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('mobile_info.inc');
require_once('emoji_factory.inc');

class emoji_convert {

public function __construct()
{
  //
  //parent::__construct();
  $this->init();
}

//
public function init()
{
}

/**
 * �᥽�åɤ�����(���)������Ū�˥᥽�å�̾
 *
 * �᥽�åɤ�����(ʣ����)���ܺ٤���������¾
 *
 * @access public��private��protected��
 * @param �� ̾�� ����
 * @return ����ͤη� ��ñ������
 */
public function convert($base_string, $type="")
{
  // user_agent����Ŭ������̾�������
  $obj = new mobile_info;
  if ("" === $type) {
    if ($obj->is_docomo()) {
      $type = 'docomo';
    } else
    if ($obj->is_ez()) {
      $type = 'ez';
    } else
    if ($obj->is_softbank()) {
      $type = 'softbank';
    } else {
      // XXX ������PC�Υ��󥹥��󥹡�
      $type = 'docomo';
    }
  }
//var_dump($type);

  // ���󥹥��󥹼���
  $eobj = emoji_factory::get_instance($type);
  
  // �ִ�
  // XXX ��ǲ��Ѥ�
  $prefix = '[emoji:';
  $suffix = ']';

  $prefix_len = strlen($prefix);
  $suffix_len = strlen($suffix);

  $s = $base_string;

  $ret = "";
  while(1) {
    // ��Ƭ
    $pos = strpos($s, $prefix);
    if (false === $pos) { break; }
    $ret .= substr($s, 0, $pos);
    $s = substr($s, $pos + $prefix_len);

    // �ִ���³��
    $pos = strpos($s, $suffix);
    if (false === $pos) { break; }
    $no = substr($s, 0, $pos);
    $ret .= $eobj->encode($no);
    $s = substr($s, $pos + $suffix_len);
  }
  if ("" != $s) {
    $ret .= $s;
  }


  //
  return $ret;
}


//private:
//prefix
//suffix

} // end of class
