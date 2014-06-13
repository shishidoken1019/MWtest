<?php

/**
 * �Ź�ϤΥ桼�ƥ���ƥ�
 *
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

class crypt_util {


/**
 * ���ꤵ�줿ʸ����Ĺ�Υ������ʸ���������
 *
 * ���������Ĺ���������ˤʤ�
 *
 * @access static public
 * @param int $num ʸ�����length
 * @param boolean $flg ������true����$num��$num����ǥ�����ˤʤ�
 * @return string �������ʸ����
 */
static public function rand_string($num, $flg = false)
{
  //
  $data = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';

  // �������ʸ����Ĺ������
  if (true === $flg) {
    $num = mt_rand(1, $num);
  }

  $ret = "";
  $max = strlen($data);
  $max --; // 0 start�Τ���

  for($i=0; $i < $num; $i ++) {
    $j = mt_rand(0,$max);
    $ret .= $data[$j];
  }

  return $ret;
}

//private:


} // end of class
