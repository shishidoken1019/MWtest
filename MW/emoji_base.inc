<?php

/**
 * ��ʸ�������Ѵ��쥯�饹
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

class emoji_base {

public function __construct()
{
  //
  //parent::__construct();
  $this->init();
}

//
public function init()
{
  $this->emoji_ = array();
}

//
protected function set_emoji(array $a) { $this->emoji_ = $a; }
//protected function get_emoji() { return $this->emoji_; }

/**
 * ��ʸ���μ���
 *
 * [e]{0,1}[0-9]{1,3} ��ʸ�����ɬ�פ�ʸ������Ѵ�
 *
 * @access public
 * @param string $s [e]{0,1}[0-9]{1,3} ��ʸ����
 * @return string �Ѵ���γ�ʸ�����б����ʤ����϶�ʸ��
 */
public function encode($s)
{
  // XXX ��������ͤ����Ȥˤ��롩
  if (true === isset($this->emoji_[$s])) {
    return $this->emoji_[$s];
  }
  // else
  return "";
}

// XXX
//abstract public function decode($s);


//private:
private $emoji_;

} // end of class
