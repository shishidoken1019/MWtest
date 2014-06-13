<?php

/**
 * ���������򿶤륯�饹
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

class dice {

public function __construct()
{
  //
  //parent::__construct();
  $this->init();
}

//
public function init()
{
  $this->set("");
}

/**
 * �������Ѥ�string���å�
 *
 * TRPG�Ǥ��ʤ��ߤΡ��㤨�� 1d4+2d6+1d8+3 �Ȥ��ä���
 * XXX �Ѥ�ʸ����Ȥ��Υ����å��Ϥ��Ƥʤ������!!
 *
 * @access public
 * @param string $s ������ʸ����
 */
public function set($s) {
  // �Ȥꤢ�������å�
  $awk = explode('+', $s);

  // trim���Ĥ�D��d�ˤ��Ĥĳ�Ǽ
  $this->ds_ = array();
  if (false === empty($awk)) {
    foreach($awk as $wk) {
      $this->ds_[] = strtolower(trim($wk));
    }
  }
}

/**
 * ���������򿶤�
 *
 * @access public
 * @return int ���������򿶤ä����
 */
public function get()
{
  // ��ˤϤ������Ϥ���
  if (true === empty($this->ds_)) {
    return 0;
  }
  // ���������դ뤾��
  $ret = 0;
  foreach($this->ds_ as $d) {
    // d��̵���Ȥ��ν�����
    if (false === strstr($d, 'd')) {
      $ret += $d;
      continue;
    }
    // d������Ȥ��ϥ������դ�ˤ��
//print "$d \n";
    $wk = explode('d', $d);
    for($i = 0; $i < $wk[0]; $i ++) {
//print 'dice roll 1 to ' . $wk[1] . "\n";
      $ret += mt_rand(1, $wk[1]);
    }
  }

  return $ret;
}


//private:
private $ds_;

} // end of class
