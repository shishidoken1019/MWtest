<?php

/**
 * config�ˤޤĤ��桼�ƥ���ƥ�
 *
 * util�ϤʤΤǴ���Ū��static�ʥ᥽�åɤΤ�
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('load_manager.inc');

class config_util {

/**
 * config�񼰤��饤�󥹥�������
 *
 * include�ե�����̾:���饹̾ �ν񼰤��顢include����new���ƤޤǤ�쵤
 *
 * @access static public
 * @param string $s "include�ե�����̾:���饹̾"�񼰤�ʸ����
 * @return object ���Ԥ������null
 */
static public function create_instance($s)
{
  // ���饹̾��include�ե�����̾���ڤ�ʬ����
  $awk = preg_split("/:/", $s);
  $include_filename = trim($awk[0]);
  $classname = trim($awk[1]);
//print "include is " . $include_filename . "<BR>\n";
//print "class is " . $classname . "<BR>\n";

  // include����
  if (false === load_manager::load_file($include_filename)) {
    return null;
  }

  // class¸�ߥ����å�
  // XXX �����
  if (false === class_exists($classname, false) ) {
    return null;
  }

  // ���֥������Ⱥ���
  return new $classname;
}

} // end of class
